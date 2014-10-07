/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef _MSC_VER
// Suppressing msvc warnings from boost that are heard to deal with
// because boost/algorithm carelessly defines _SCL_SECURE_NO_WARNINGS
// without first testing it.
#pragma warning(push) 
#pragma warning(disable : 4996)
#endif
#include <bitcoin/explorer/utility/utility.hpp>
#include <iomanip>
#include <iostream>
#include <random>
#include <signal.h>
#include <cstdint>
#include <string>
#include <vector>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <bitcoin/bitcoin.hpp>
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/utility/compat.hpp>

using namespace boost::posix_time;

namespace libbitcoin {
namespace explorer {

void join(const std::vector<std::string>& words, std::string& sentence,
    const std::string& delimiter)
{
    sentence = boost::join(words, delimiter);
}

// The key may be invalid, caller must test for null secret.
// Note that random fill of ec_secret could also generate an invalid key,
// but that would be less easily tested than this result.
ec_secret new_key(const bc::data_chunk& seed)
{
    // The testnet value is not relevant to the secret.
    constexpr bool testnet = false;

    // Using HD key generation because we don't yet have one for EC.
    const hd_private_key hd_key(seed, testnet);
    return hd_key.private_key();
}

// Not testable due to lack of random engine injection.
data_chunk new_seed(size_t bitlength)
{
    size_t fill_seed_size = bitlength / byte_bits;
    data_chunk seed(fill_seed_size);
    random_fill(seed);
    return seed;
}

ptime now()
{
    using namespace boost::posix_time;
    ptime local_time_in_seconds(second_clock::local_time());
    return local_time_in_seconds;
}

// Not testable due to lack of random engine injection.
void random_fill(data_chunk& chunk)
{
    std::random_device random;
    std::default_random_engine engine(random());

    for (uint8_t& byte: chunk)
        byte = engine() % std::numeric_limits<uint8_t>::max();
}

std::string read_stream(std::istream& stream)
{
    SET_BINARY_FILE_MODE(true);
    std::istreambuf_iterator<char> first(stream), last;
    std::string result(first, last);
    SET_BINARY_FILE_MODE(false);
    return result;
}

script_type script_to_raw_data_script(const script_type& script)
{
    return raw_data_script(save_script(script));
}

bool sign_transaction(data_chunk& signature, const tx_type& transaction,
    size_t index, const script_type& script, const ec_secret& secret,
    const data_chunk& nonce, uint32_t hash_type)
{
    // This always produces a valid signature hash. See libbitcoin comments.
    const auto signature_hash = script_type::generate_signature_hash(
        transaction, index, script, hash_type);

    signature = sign(secret, signature_hash, new_key(nonce));
    return !signature.empty();
}

// Not unit testable (sleep).
void sleep_ms(uint32_t milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

std::vector<std::string> split(const std::string& sentence,
    const std::string& delimiter)
{
    std::vector<std::string> words;
    boost::split(words, sentence, boost::is_any_of(delimiter),
        boost::token_compress_on);
    return words;
}

void trim(std::string& value)
{
    boost::trim(value);
}

void trim_left(std::string& value, const std::string& chars)
{
    boost::trim_left_if(value, boost::is_any_of(chars));
}

bool unwrap(wrapped_data& data, const data_chunk& wrapped)
{
    return unwrap(data.version, data.payload, data.checksum, wrapped);
}

// TODO: move to libbitcoin
bool unwrap(uint8_t& version, data_chunk& payload, uint32_t& checksum,
    const data_chunk& wrapped)
{
    constexpr size_t version_length = sizeof(version);
    constexpr size_t checksum_length = sizeof(checksum);

    // guard against insufficient buffer length
    if (wrapped.size() < version_length + checksum_length)
        return false;

    if (!verify_checksum(wrapped))
        return false;

    // set return values
    version = wrapped.front();
    payload = data_chunk(wrapped.begin() + version_length,
        wrapped.end() - checksum_length);
    const auto checksum_start = wrapped.end() - checksum_length;
    auto deserial = make_deserializer(checksum_start, wrapped.end());
    checksum = deserial.read_4_bytes();

    return true;
}

bool valid_signature(const tx_type& tx, uint32_t index, const ec_point& pubkey,
    const script_type& script, const data_chunk& signature,
    uint32_t hash_type)
{
    // This always produces a valid signature hash. See libbitcoin comments.
    const auto signature_hash = script_type::generate_signature_hash(tx, index,
        script, hash_type);

    return verify_signature(pubkey, signature_hash, signature);
}

data_chunk wrap(const wrapped_data& data)
{
    return wrap(data.version, data.payload);
}

// TODO: move to libbitcoin
data_chunk wrap(uint8_t version, const data_chunk& payload)
{
    data_chunk wrapped;
    wrapped.push_back(version);
    extend_data(wrapped, payload);
    append_checksum(wrapped);
    return wrapped;
}

// We aren't yet using a reader, although it is possible using ptree.
std::ostream& write_stream(std::ostream& output, const pt::ptree& tree,
    encoding_engine engine)
{
    switch (engine)
    {
        case encoding_engine::json:
            pt::write_json(output, tree);
            break;
        case encoding_engine::xml:
            pt::write_xml(output, tree);
            break;
        default:
            pt::write_info(output, tree);
            break;
    }

    return output;
}

} // namespace explorer
} // namespace libbitcoin
