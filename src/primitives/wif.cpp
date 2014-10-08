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

#include <bitcoin/explorer/primitives/wif.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

wif::wif()
    : compressed_(true), value_()
{
}

wif::wif(const std::string& base58)
{
    std::stringstream(base58) >> *this;
}

wif::wif(const ec_secret& value)
    : compressed_(true), value_(value)
{
}

wif::wif(const hd_private_key& value)
    : wif(value.private_key())
{
}

wif::wif(const wif& other)
    : wif(other.value_)
{
}

ec_secret& wif::data()
{
    return value_;
}

bool wif::get_compressed() const
{
    return compressed_;
}

void wif::set_compressed(bool value)
{
    compressed_ = value;
}

wif::operator const ec_secret&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& input, wif& argument)
{
    std::string base58;
    input >> base58;

    auto value = wif_to_secret(base58);
    if (!verify_private_key(value))
        throw invalid_option_value(base58);

    argument.compressed_ = is_wif_compressed(base58);
    std::copy(value.begin(), value.end(), argument.value_.begin());
    return input;
}

std::ostream& operator<<(std::ostream& output, const wif& argument)
{
    // secret_to_public_key(secret, compressed);
    output << secret_to_wif(argument.value_, argument.compressed_);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
