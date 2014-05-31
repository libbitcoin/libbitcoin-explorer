/*
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
#include <functional>
#include <memory>
#include <string>
#include <sx/command.hpp>
#include <sx/command/generated.hpp>

/********** WARNING: This file is generated, do not edit directly. **********/

namespace sx {
namespace extensions {

std::shared_ptr<command> find(const char* symbol)
{
    auto symbolic = std::string(symbol);

    if (symbolic == addr::symbol())
        return std::make_shared<addr>();
    if (symbolic == wallet::symbol())
        return std::make_shared<wallet>();

    return nullptr;
}

bool broadcast(const std::function<void(std::shared_ptr<command>)> func)
{
    func(std::make_shared<addr>());
    func(std::make_shared<wallet>());

    return true;
}

} // extensions
} // sx
