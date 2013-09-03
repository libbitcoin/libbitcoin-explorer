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
        std::cerr << "history: Failed to fetch history: "
            << ec.message() << std::endl;
        return;
    }
    for (const auto& row: history)
    {
        std::cout << "Address: " << payaddr.encoded() << std::endl;
        std::cout << "  output: " << row.output << std::endl;
        std::cout << "  output_height: ";
        if (!row.output_height)
            std::cout << "Pending";
        else
            std::cout << row.output_height;
        std::cout << std::endl;
        std::cout << "  value:  " << row.value << std::endl;
        if (row.spend.hash == null_hash)
        {
            std::cout << "  spend: Unspent" << std::endl;
            std::cout << "  spend_height: Unspent" << std::endl;
        }
        else
        {
            std::cout << "  spend: " << row.spend << std::endl;
            std::cout << "  spend_height: ";
            if (!row.spend_height)
                std::cout << "Pending";
            else
                std::cout << row.spend_height;
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    --remaining_count;
}

void json_history_fetched(const payment_address& payaddr,
    const std::error_code& ec, const blockchain::history_list& history)
{
    if (ec)
    {
        std::cerr << "history: Failed to fetch history: "
            << ec.message() << std::endl;
        return;
    }
    bool is_first = true;
    for (const auto& row: history)
    {
        // Put commas between each array item in json output.
        if (is_first)
            is_first = false;
        else
            std::cout << "," << std::endl;
        // Actual row data.
        std::cout << "{" << std::endl;
        std::cout << "  \"address\": \"" << payaddr.encoded()
            << "\"," << std::endl;
        std::cout << "  \"output\": \"" << row.output
            << "\"," << std::endl;
        std::cout << "  \"output_height\": ";
        if (!row.output_height)
            std::cout << "\"Pending\"";
        else
            std::cout << row.output_height;
        std::cout << "," << std::endl;
        std::cout << "  \"value\":  \"" << row.value << "\"," << std::endl;
        if (row.spend.hash == null_hash)
        {
            std::cout << "  \"spend\": \"Unspent\"," << std::endl;
            std::cout << "  \"spend_height\": \"Unspent\"" << std::endl;
        }
        else
        {
            std::cout << "  \"spend\": \"" << row.spend << "\"," << std::endl;
            std::cout << "  \"spend_height\": ";
            if (!row.spend_height)
                std::cout << "\"Pending\"";
            else
                std::cout << "\"" << row.spend_height << "\"";
        }
        std::cout << "}";
    }
    if (--remaining_count > 0)
        std::cout << ",";
    std::cout << std::endl;
}

bool payaddr_from_stdin(payment_address& payaddr)
{
    if (!payaddr.set_encoded(read_stdin()))
    {
        std::cerr << "history: Invalid address." << std::endl;
        return false;
    }
    return true;
}

bool payaddr_from_argv(payaddr_list& payaddrs, int argc, char** argv)
{
    for (size_t i = 1; i < argc; ++i)
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
        sleep(0.1);
    }
    if (json_output)
        std::cout << "]" << std::endl;
    pool.stop();
    pool.join();
    return 0;
}

