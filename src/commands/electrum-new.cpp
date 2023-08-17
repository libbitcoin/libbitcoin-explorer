/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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

#include <cmath>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

////<define name="BX_ELECTRUM_NEW_INVALID_ENTROPY_SIZE" value="The entropy size is not 17 to 64 bytes." />
////<define name="BX_ELECTRUM_NEW_INVALID_VERSION1_LANGUAGE" value="Version1 langauges are limited to 'en' and 'pt'." />

console_result electrum_new::invoke(std::ostream& output, std::ostream& error)
{
    ////// Bound parameters.
    ////const language lingo = get_language_option();
    ////const electrum::seed_prefix prefix = get_prefix_option();
    ////const data_chunk& entropy = get_entropy_argument();

    ////if (!electrum::is_valid_entropy_size(entropy.size()))
    ////{
    ////    error << BX_ELECTRUM_NEW_INVALID_ENTROPY_SIZE << std::endl;
    ////    return console_result::failure;
    ////}

    ////// Langauge is ensured for v2 but not v1.
    ////if (prefix == electrum::seed_prefix::old)
    ////{
    ////    if (!electrum_v1::is_valid_dictionary(lingo))
    ////    {
    ////        error << BX_ELECTRUM_NEW_INVALID_VERSION1_LANGUAGE << std::endl;
    ////        return console_result::failure;
    ////    }

    ////    const auto seed = electrum_v1(entropy);
    ////}

    ////else if (!electrum::is_valid_dictionary(lingo))
    ////{
    ////    error << BX_ELECTRUM_NEW_INVALID_VERSION1_LANGUAGE << std::endl;
    ////    return console_result::failure;
    ////}

    ////// If 'any' default to first ('en'), otherwise the one specified.
    ////const auto dictionary = language.front();

    ////auto mnemonic = electrum::create_mnemonic(seed, *dictionary, prefix);

    ////output << join(mnemonic) << std::endl;
    ////return console_result::okay;

    ////error << BX_ELECTRUM_REQUIRES_ICU << std::endl;
    return console_result::failure;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
