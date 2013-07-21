#include <bitcoin/bitcoin.hpp>
#include <obelisk/client/interface.hpp>

using namespace bc;

bool stopped = false;

void history_fetched(const std::error_code& ec,
    const blockchain::history_list& history)
{
    if (ec)
    {
        std::cerr << "balance: Failed to fetch history: "
            << ec.message() << std::endl;
        return;
    }
    std::cout << "Output Hash:Index\t\t\t\t\t\t\tOutput Height\t"
        << "Value (Satoshis)\t\t\tSpend Hash:Index\t\t\t\t"
        << "Spend Height" << std::endl;
    for (const auto& row: history)
    {
        std::cout << row.output.hash << ":" << row.output.index << "\t";
        std::cout << row.output_height << "\t\t";
        std::cout << row.value << "\t\t";
        if (row.spend.hash == null_hash)
            std::cout << "Unspent\t\t\t\t\t\t\t\t\t";
        else
            std::cout << row.spend.hash << ":" << row.spend.index << "\t";
        std::cout << row.spend_height << std::endl;
    }
    stopped = true;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: balance ADDRESS" << std::endl;
        return -1;
    }
    std::string addr = argv[1];
    payment_address payaddr;
    if (!payaddr.set_encoded(addr))
    {
        std::cerr << "balance: Invalid address." << std::endl;
        return -1;
    }
    fullnode_interface fullnode;
    fullnode.blockchain.fetch_history(payaddr, history_fetched);
    while (!stopped)
    {
        fullnode.update();
        sleep(0.1);
    }
    return 0;
}

