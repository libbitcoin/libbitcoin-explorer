#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include "config.hpp"
#include "util.hpp"

using namespace bc;
using std::placeholders::_1;
using std::placeholders::_2;

typedef std::vector<payment_address> payaddr_list;

std::atomic_uint remaining_count;
bool json_output = false;

void history_fetched(const payment_address& payaddr,
    const std::error_code& ec, const blockchain::history_list& history)
{
    if (ec)
    {
        std::cerr << "balance: Failed to fetch history: "
            << ec.message() << std::endl;
        return;
    }
    uint64_t total_recv = 0, balance = 0, pending_balance = 0;
    for (const auto& row: history)
    {
        uint64_t value = row.value;
        BITCOIN_ASSERT(value >= 0);
        total_recv += value;
        // Unconfirmed balance.
        if (row.spend.hash == null_hash)
        {
            pending_balance += value;
        }
        // Confirmed balance.
        if (row.output_height &&
            (row.spend.hash == null_hash || !row.spend_height))
        {
            balance += value;
        }
        BITCOIN_ASSERT(total_recv >= balance);
        BITCOIN_ASSERT(total_recv >= pending_balance);
    }
    std::cout << "Address: " << payaddr.encoded() << std::endl;
    std::cout << "  Paid balance:    " << balance << std::endl;
    std::cout << "  Pending balance: " << pending_balance << std::endl;
    std::cout << "  Total received:  " << total_recv << std::endl;
    std::cout << std::endl;
    --remaining_count;
}

void json_history_fetched(const payment_address& payaddr,
    const std::error_code& ec, const blockchain::history_list& history)
{
    if (ec)
    {
        std::cerr << "balance: Failed to fetch history: "
            << ec.message() << std::endl;
        return;
    }
    bool is_first = true;
    uint64_t total_recv = 0, balance = 0, pending_balance = 0;
    for (const auto& row: history)
    {
        uint64_t value = row.value;
        BITCOIN_ASSERT(value >= 0);
        total_recv += value;
        // Unconfirmed balance.
        if (row.spend.hash == null_hash)
        {
            pending_balance += value;
        }
        // Confirmed balance.
        if (row.output_height &&
            (row.spend.hash == null_hash || !row.spend_height))
        {
            balance += value;
        }
        BITCOIN_ASSERT(total_recv >= balance);
        BITCOIN_ASSERT(total_recv >= pending_balance);
    }

    // Put commas between each array item in json output.
    if (is_first)
        is_first = false;
    else
        std::cout << "," << std::endl;
    // Actual row data.
    std::cout << "{" << std::endl;
    std::cout << "  \"address\": \"" << payaddr.encoded()
        << "\"," << std::endl;
    std::cout << "  \"paid\":  \"" << balance << "\"," << std::endl;
    std::cout << "  \"pending\":  \"" << pending_balance << "\"," << std::endl;
    std::cout << "  \"received\":  \"" << total_recv << "\"" << std::endl;
    std::cout << "}";
    if (--remaining_count > 0)
        std::cout << ",";
    std::cout << std::endl;
}

bool payaddr_from_stdin(payment_address& payaddr)
{
    if (!payaddr.set_encoded(read_stdin()))
    {
        std::cerr << "balance: Invalid address." << std::endl;
        return false;
    }
    return true;
}

bool payaddr_from_argv(payaddr_list& payaddrs, int argc, char** argv)
{
    for (int i = 1; i < argc; ++i)
    {
        const std::string arg = argv[i];
        if (arg == "-j" || arg == "--json")
        {
            json_output = true;
            continue;
        }
        payment_address payaddr;
        if (!payaddr.set_encoded(arg))
            return false;
        payaddrs.push_back(payaddr);
    }
    return true;
}

int main(int argc, char** argv)
{
    config_map_type config;
    load_config(config);
    payaddr_list payaddrs;
    if (argc == 1)
    {
        payment_address payaddr;
        if (!payaddr_from_stdin(payaddr))
            return -1;
        payaddrs.push_back(payaddr);
    }
    else
    {
        if (!payaddr_from_argv(payaddrs, argc, argv))
            return -1;
    }
    remaining_count = payaddrs.size();
    threadpool pool(1);
    obelisk::fullnode_interface fullnode(pool, config["service"]);
    if (json_output)
        std::cout << "[" << std::endl;
    for (const payment_address& payaddr: payaddrs)
    {
        if (json_output)
            fullnode.address.fetch_history(payaddr,
                std::bind(json_history_fetched, payaddr, _1, _2));
        else
            fullnode.address.fetch_history(payaddr,
                std::bind(history_fetched, payaddr, _1, _2));
    }
    while (remaining_count > 0)
    {
        fullnode.update();
        std::this_thread::sleep_for(std::chrono::seconds(100));
    }
    if (json_output)
        std::cout << "]" << std::endl;
    pool.stop();
    pool.join();
    return 0;
}

