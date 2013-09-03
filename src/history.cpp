#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include "config.hpp"
#include "util.hpp"

using namespace bc;
using std::placeholders::_1;
using std::placeholders::_2;

typedef std::vector<payment_address> payaddr_list;

std::atomic_uint fetch_count(0);

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
    ++fetch_count;
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
        payment_address payaddr;
        if (!payaddr.set_encoded(argv[i]))
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
    threadpool pool(1);
    obelisk::fullnode_interface fullnode(pool, config["service"]);
    for (const payment_address& payaddr: payaddrs)
        fullnode.address.fetch_history(payaddr,
            std::bind(history_fetched, payaddr, _1, _2));
    while (fetch_count < payaddrs.size())
    {
        fullnode.update();
        sleep(0.1);
    }
    BITCOIN_ASSERT(fetch_count == payaddrs.size());
    pool.stop();
    pool.join();
    return 0;
}

