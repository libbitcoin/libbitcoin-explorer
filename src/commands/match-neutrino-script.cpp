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

// Sponsored in part by Digital Contract Design, LLC

#include <bitcoin/explorer/commands/match-neutrino-script.hpp>

#include <iostream>
#include <cstdint>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/config/signature.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::explorer::config;
using namespace bc::system;
using namespace bc::system::wallet;

console_result match_neutrino_script::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const message::compact_filter& filter = get_compact_filter_argument();
    const auto& script = get_script_argument();

    if (filter.filter_type() != neutrino_filter_type)
    {
        output << BX_FILTER_TYPE_UNRECOGNIZED << std::endl;
        return console_result::failure;
    }

    if (!neutrino::match_filter(filter, script))
    {
        output << BX_FILTER_MATCH_SCRIPT_FAILURE << std::endl;
        return console_result::invalid;
    }

    output << BX_FILTER_MATCH_SCRIPT_SUCCESS << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
