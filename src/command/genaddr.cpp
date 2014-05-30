#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>

using namespace bc;
using namespace libwallet;

std::string read_data()
{
    std::istreambuf_iterator<char> it(std::cin);
    std::istreambuf_iterator<char> end;
    return std::string(it, end);
}

bool invoke(const int argc, const char* argv[])
{
    if (argc != 2 && argc != 3)
    {
        std::cerr << "Usage: genaddr N [CHANGE]" << std::endl;
        return -1;
    }
    size_t n;
    try
    {
        n = boost::lexical_cast<size_t>(argv[1]);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "genaddr: Bad N provided" << std::endl;
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
    libwallet::deterministic_wallet wallet;
    std::string user_data = read_data();
    if (!wallet.set_seed(user_data))
    {
        data_chunk mpk = decode_hex(user_data);
        if (!wallet.set_master_public_key(mpk))
        {
            std::cerr << "genaddr: No valid master public key, or "
                << "private secret key was passed in." << std::endl;
            return -1;
        }
    }
    data_chunk pubkey = wallet.generate_public_key(n, for_change);
    payment_address addr;
    set_public_key(addr, pubkey);
    std::cout << addr.encoded() << std::endl;
    return 0;
}

