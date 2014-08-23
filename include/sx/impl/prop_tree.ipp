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
#ifndef SX_PROPERTY_TREE_IPP
#define SX_PROPERTY_TREE_IPP

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <sx/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

template <typename Values>
pt::ptree prop_tree_list(const std::string& name, Values& values)
{
    ptree list;
    ptree element;
    for (const auto& value: values)
    {
        list.push_back(std::make_pair(name, prop_tree(value)));
    }

    return list;
}

template <typename Values>
pt::ptree prop_value_list(const std::string& name, Values& values)
{
    ptree list;
    ptree element;
    for (const auto& value: values)
    {
        element.put_value(value);
        list.push_back(std::make_pair(name, element));
    }

    return list;
}

} // serializer
} // sx

#endif