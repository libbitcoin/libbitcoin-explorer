#include <bitcoin/bitcoin.hpp>
#include <obelisk/client/interface.hpp>
#include "config.hpp"
#include "util.hpp"

using namespace bc;
using std::placeholders::_1;
using std::placeholders::_2;

void history_fetched(const std::error_code& ec,
    const blockchain::history_list& history)
{
    if (ec)
    {
        std::cerr << "history: Failed to fetch history: "
            << ec.message() << std::endl;
        return;
    }
    for (const auto& row: history)
    {
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
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: sx monitor ADDRESS" << std::endl;
        return -1;
    }
    std::cerr << std::endl;
    std::cerr << "**************************************" << std::endl;
    std::cerr << "Warning: this command is experimental." << std::endl;
    std::cerr << "**************************************" << std::endl;
    std::cerr << std::endl;
    config_map_type config;
    load_config(config);
    fullnode_interface fullnode(config["service"]);
    payment_address payaddr;
    if (!payaddr.set_encoded(argv[1]))
    {
        std::cerr << "history: Invalid address." << std::endl;
        return -1;
    }
    fullnode.address.fetch_history(payaddr,
        std::bind(history_fetched, _1, _2));
    while (true)
    {
        fullnode.update();
        sleep(0.1);
    }
    return 0;
}

