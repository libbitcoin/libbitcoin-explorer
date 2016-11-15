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
#ifndef BX_PROPERTY_TREE_IPP
#define BX_PROPERTY_TREE_IPP

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {
namespace config {

template <typename Values>
pt::ptree prop_tree_list(const std::string& name, const Values& values,
    bool json)
{
    pt::ptree list;
    if (json)
    {
        for (const auto& value: values)
            list.push_back({"", prop_list(value)});
    }
    else
    {
        for (const auto& value: values)
            list.add_child(name, prop_list(value));
    }

    return list;
}

template <typename Values>
pt::ptree prop_tree_list_of_lists(const std::string& name,
    const Values& values, bool json)
{
    pt::ptree list;
    if (json)
    {
        for (const auto& value: values)
            list.push_back({"", prop_list(value, json)});
    }
    else
    {
        for (const auto& value: values)
            list.add_child(name, prop_list(value, json));
    }

    return list;
}

template <typename Values>
pt::ptree prop_value_list(const std::string& name, const Values& values,
    bool json)
{
    pt::ptree list;
    pt::ptree element;
    if (json)
    {
        for (const auto& value: values)
        {
            element.put_value(value);
            list.push_back({"", element});
        }
    }
    else
    {
        for (const auto& value: values)
        {
            element.put_value(value);
            list.add_child(name, element);
        }
    }

    return list;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin

#endif
