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

#include <bitcoin/explorer/commands/settings.hpp>

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

console_result commands::settings::invoke(std::ostream& output,
    std::ostream&)
{
    options_metadata definitions("settings");
    load_settings(definitions);

    system::options::printer print(definitions, get_variables(),
        BX_PROGRAM_NAME, BX_SETTINGS_MESSAGE);
    print.initialize();
    print.settings(output);
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
