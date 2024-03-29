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
#ifndef BX_PROPERTY_TREE_IPP
#define BX_PROPERTY_TREE_IPP

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

void inline add_child(pt::ptree& out_list, const std::string& name,
    const pt::ptree& element, bool json)
{
    if (json)
    {
        // HACK: work around invalid assertions in boost::property_tree.
        // It is sufficient to call push_back as long as the name is empty.
        out_list.push_back({ "", element });
        ////out_list.add_child("", element);
    }
    else
    {
        out_list.add_child(name, element);
    }
}

template <typename Values>
pt::ptree prop_tree_list(const std::string& name, const Values& values,
    bool json)
{
    pt::ptree list;
    for (const auto& value: values)
        add_child(list, name, prop_list(value), json);

    return list;
}

template <typename Values>
pt::ptree prop_tree_list_of_lists(const std::string& name,
    const Values& values, bool json)
{
    pt::ptree list;
    for (const auto& value: values)
        add_child(list, name, prop_list(value, json), json);

    return list;
}

template <typename Values>
pt::ptree prop_value_list(const std::string& name, const Values& values,
    bool json)
{
    pt::ptree list;
    pt::ptree element;
    for (const auto& value: values)
    {
        element.put_value(value);
        add_child(list, name, element, json);
    }

    return list;
}

template <typename Values>
pt::ptree prop_encoded_value_list(const std::string& name, const Values& values,
    bool json)
{
    pt::ptree list;
    pt::ptree element;
    for (const auto& value: values)
    {
        element.put_value(encode_base16(value));
        add_child(list, name, element, json);
    }

    return list;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin

#endif
