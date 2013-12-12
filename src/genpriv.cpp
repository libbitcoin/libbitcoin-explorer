#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
using namespace bc;
using namespace libwallet;

std::string dump_file(std::istream& in_file)
{
    std::istreambuf_iterator<char> it(in_file);
    std::istreambuf_iterator<char> end;
    return std::string(it, end);
}

int main(int argc, char** argv)
{
    if (argc != 2 && argc != 3)
    {
        std::cerr << "Usage: genpriv N [CHANGE]" << std::endl;
        return -1;
    }
    size_t n;
    try
    {
        n = boost::lexical_cast<size_t>(argv[1]);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "genpriv: Bad N provided." << std::endl;
        return -1;
    }
    bool for_change = false;
    if (argc == 3)
    {
        std::string change_str = argv[2];
        boost::algorithm::to_lower(change_str);
        if (change_str == "true" || change_str == "1")
            for_change = true;
    }
    std::string seed = dump_file(std::cin);
    libwallet::deterministic_wallet wallet;
    if (!wallet.set_seed(seed))
    {
        std::cerr << "genpriv: This command wants a seed." << std::endl;
        return -1;
    }
    secret_parameter secret = wallet.generate_secret(n, for_change);
    std::cout << secret_to_wif(secret) << std::endl;
    return 0;
}

