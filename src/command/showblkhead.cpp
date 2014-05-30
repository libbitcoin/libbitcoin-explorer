#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include "util.hpp"

using namespace bc;

bool load_blk_header(block_header_type& blk_header, const std::string& filename)
{
    std::ostringstream contents;
    if (filename == "-")
    {
        std::istreambuf_iterator<char> first(std::cin);
        std::istreambuf_iterator<char> last;
        contents << std::string(first, last);
    }
    else
    {
        std::ifstream infile(filename, std::ifstream::binary);
        if (!infile)
        {
            std::cerr << "showblkhead: Bad file." << std::endl;
            return false;
        }
        contents << infile.rdbuf();
    }
    data_chunk raw_blk_header = decode_hex(contents.str());
    try
    {
        satoshi_load(raw_blk_header.begin(), raw_blk_header.end(), blk_header);
    }
    catch (end_of_stream)
    {
        std::cerr << "showblkhead: Deserializing block header failed."
            << std::endl;
        return false;
    }
    return true;
}

bool invoke(const int argc, const char* argv[])
{
    std::string filename = "-";
    if (argc == 2)
        filename = argv[1];
    block_header_type blk_header;
    if (!load_blk_header(blk_header, filename))
        return -1;
    // Show details.
    std::cout << "hash: " << hash_block_header(blk_header) << std::endl;
    std::cout << "version: " << blk_header.version << std::endl;
    std::cout << "previous_block_hash: "
        << blk_header.previous_block_hash << std::endl;
    std::cout << "merkle: " << blk_header.merkle << std::endl;
    std::cout << "timestamp: " << blk_header.timestamp << std::endl;
    std::cout << "bits: " << blk_header.bits << std::endl;
    std::cout << "nonce: " << blk_header.nonce << std::endl;
    return 0;
}

