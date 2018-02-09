/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/explorer/commands/electrum-new.hpp>

#include <sstream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/bitcoin/math/hash.hpp>
#include <bitcoin/explorer/define.hpp>
#include <boost/multiprecision/cpp_int.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::wallet;
using namespace boost::multiprecision;

console_result electrum_new::invoke(std::ostream& output,
    std::ostream& error)
{
#ifdef WITH_ICU
    // Bound parameters.
    const dictionary_list& language = get_language_option();
    const data_chunk& seed = get_seed_argument();
    const auto bit_length = get_bit_length_option();
    const auto prefix = get_prefix_option();

    const auto bits_per_word = std::log2(bc::wallet::dictionary_size);

    const auto number_of_entropy_bits = static_cast<uint32_t>(
        std::ceil(bit_length / bits_per_word) * bits_per_word);

    if ((bit_length < minimum_electrum_seed_bits) ||
        (seed.size() * byte_bits < number_of_entropy_bits))
    {
        error << BX_ELECTRUM_NEW_BIT_LENGTH_UNSUPPORTED << std::endl;
        return console_result::failure;
    }

    // If 'any' default to first ('en'), otherwise the one specified.
    const auto dictionary = language.front();

    // convert the provided entropy to a large number and make sure it
    // does not exceed the required entropy bits
    const cpp_int entropy_number = cpp_int("0x" + encode_base16(seed)) %
        boost::multiprecision::pow(cpp_int(2), number_of_entropy_bits);

    // convert large number back into a base16 decode-able string
    std::stringstream sstream;
    sstream << std::hex << entropy_number;

    // pre-pend zero if the string conversion length is not even
    const auto entropy_prefix = ((sstream.str().size() % 2 == 0) ? "" : "0");
    const auto entropy_string = entropy_prefix + sstream.str();

    data_chunk electrum_seed;
    decode_base16(electrum_seed, entropy_string);

    const auto words = electrum::create_mnemonic(
        electrum_seed, *dictionary, prefix);

    output << join(words) << std::endl;
    return console_result::okay;
#else
    error << BX_ELECTRUM_NEW_UNSUPPORTED << std::endl;
    return console_result::failure;
#endif
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
