#include <iostream>
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

int main()
{
    std::string secret_str = dump_file(std::cin);
    secret_parameter secret = decode_hex_digest<hash_digest>(secret_str);
    std::cout << secret_to_wif(secret) << std::endl;
    return 0;
}

