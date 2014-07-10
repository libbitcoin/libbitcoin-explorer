/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include <sx/utility/parameter.hpp>

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <sx/define.hpp>
#include <sx/utility/console.hpp>

using namespace sx;

// 100% unit coverage, all three scenarios (long, short, both)
const std::string parameter::canonical(const option_metadata& option)
{
    return option.canonical_display_name(
        search_options::dashed_both_prefer_long);
}

// 100% component coverage, all three scenarios (long, short, both)
const std::string parameter::clean_canonical(const option_metadata& option)
{
    std::string prefix;
    prefix.push_back(option_prefix_char);
    std::string clean(canonical(option));
    trim_left(clean, prefix);
    return clean;
}

// 100% component coverage, all three scenarios (long, short, both)
bool parameter::has_short_name(const option_metadata& option)
{
    return short_name(option) != no_short_name;
}

// 100% component coverage, common scenarios.
void parameter::initialize(const option_metadata& option,
    const argument_list& arguments)
{
    // TODO: eliminate all properties except for option and arguments.
    set_position(position(option, arguments));
    set_args_limit(option.semantic()->max_tokens());
    set_required(option.semantic()->is_required());
    set_short_name(short_name(option));
    set_canonical_name(canonical(option));
    set_description(option.description());
    set_format_name(option.format_name());
    set_format_parameter(option.format_parameter());
 }

// 100% component coverage.
int parameter::position(const option_metadata& option,
    const argument_list& arguments)
{
    auto option_name = clean_canonical(option);
    return find_pair_position(arguments, option_name);
}

// 100% unit coverage, all three scenarios (long, short, both)
char parameter::short_name(const option_metadata& option)
{
    auto name = option.canonical_display_name(
        search_options::dashed_short_prefer_short);
    return if_else(name[0] == option_prefix_char, name[1], no_short_name);
}