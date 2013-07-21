#include <iostream>
#include <sstream>
#include <bitcoin/bitcoin.hpp>

using namespace bc;

void error_exit(const char* message, int status=1)
{
    std::cerr << "addr: " << message << std::endl;
    exit(status);
}

int address(const std::string raw_private_key)
{
    elliptic_curve_key ec;
    if (!ec.set_private_key(
            private_data(raw_private_key.begin(), raw_private_key.end())))
        error_exit("bad private key");
    payment_address address;
    if (!set_public_key(address, ec.public_key()))
        error_exit("set public key on address");
    std::cout << address.encoded() << std::endl;
    return 0;
}

std::string read_private_key()
{
    std::istreambuf_iterator<char> it(std::cin);
    std::istreambuf_iterator<char> end;
    return std::string(it, end);
}

int main()
{
    return address(read_private_key());
}

