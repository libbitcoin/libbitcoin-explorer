/**
 * Copyright (c)2011-2014 libbitcoin developers (see AUTHORS)
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
#ifndef BX_PROPERTY_TREE_IPP
#define BX_PROPERTY_TREE_IPP

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace explorer {
namespace primitives {

template <typename Values>
pt::ptree prop_tree_list(const std::string& name, const Values& values)
{
    pt::ptree list;
    pt::ptree element;
    for (const auto& value: values)
    {
        list.push_back(std::make_pair(name, prop_tree(value)));
    }

    return list;
}

template <typename Values>
pt::ptree prop_value_list(const std::string& name, const Values& values)
{
    pt::ptree list;
    pt::ptree element;
    for (const auto& value: values)
    {
        element.put_value(value);
        list.push_back(std::make_pair(name, element));
    }

    return list;
}

} // primitives
} // explorer

#endif