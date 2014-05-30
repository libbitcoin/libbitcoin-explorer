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
#include <memory>
#include <string>
#include "command.hpp"

/* TODO: GSL Code generation */
#include "commands/wallet.hpp"
//#include "commands/wallet.hpp"
//#include "commands/wallet.hpp"

std::shared_ptr<command> find_command(std::string& symbol)
{
    /* TODO: GSL Code generation */
    if (symbol == wallet::symbol())
        return std::make_shared<wallet>();
    //if (symbol == wallet::symbol())
    //    return std::make_shared<wallet>();
    //if (symbol == wallet::symbol())
    //    return std::make_shared<wallet>();

    return nullptr;
}

bool broadcast_command(std::function<void(std::shared_ptr<command>)> func)
{
    /* TODO: GSL Code generation */
    func(std::make_shared<wallet>());
    //func(std::make_shared<wallet>());
    //func(std::make_shared<wallet>());

    return true;
}