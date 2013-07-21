#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
using namespace bc;

std::string dump_file(std::istream& in_file)
{
    std::istreambuf_iterator<char> it(in_file);
    std::istreambuf_iterator<char> end;
    return std::string(it, end);
}

data_chunk read_mpk_data()
{
    std::string raw_mpk = dump_file(std::cin);
    return data_chunk(raw_mpk.begin(), raw_mpk.end());
}

int main(int argc, char** argv)
{
    if (argc != 2 && argc != 3)
    {
        std::cerr << "Usage: genpub N [CHANGE]" << std::endl;
        return -1;
    }
    size_t n;
    try
    {
        n = boost::lexical_cast<size_t>(argv[1]);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "genpub: Bad N provided" << std::endl;
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
    const data_chunk mpk = read_mpk_data();
    if (mpk.empty())
    {
        std::cerr << "genpub: Empty master public key" << std::endl;
        return -1;
    }
    deterministic_wallet wallet;
    if (!wallet.set_master_public_key(mpk))
    {
        std::cerr << "genpub: Error setting master public key" << std::endl;
        return -1;
    }
    data_chunk pubkey = wallet.generate_public_key(n, for_change);
    payment_address addr;
    if (!set_public_key(addr, pubkey))
    {
        std::cerr << "genpub: Internal error setting pubkey" << std::endl;
        return -1;
    }
    std::cout << addr.encoded() << std::endl;
    return 0;
}

