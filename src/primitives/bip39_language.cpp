/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
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
#include <bitcoin/explorer/primitives/bip39_language.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

bip39_language::bip39_language()
    : value_()
{
}

bip39_language::bip39_language(const std::string& language)
{
    value_ = language;
}

bip39_language::bip39_language(const bip39_language& other)
    : bip39_language(other.value_)
{
}

bip39_language::operator const std::string&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, bip39_language& argument)
{
    input >> argument.value_;
    return input;
}

std::ostream& operator<<(std::ostream& output, const bip39_language& argument)
{
    output << argument.value_;
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
