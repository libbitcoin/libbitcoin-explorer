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
#include "precompile.hpp"
#include <explorer/commands/wrap-decode.hpp>

#include <iostream>
#include <explorer/define.hpp>
#include <explorer/prop_tree.hpp>
#include <explorer/primitives/wrapper.hpp>
#include <explorer/utility/utility.hpp>

using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

// TODO: update tests for ptree output.
// 100% coverage by line, loc ready.
console_result wrap_decode::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& wrapped = get_wrapped_argument();
    const auto& encoding = get_format_option();

    const auto tree = prop_tree(wrapped);

    write_stream(output, tree, encoding);
    return console_result::okay;
}