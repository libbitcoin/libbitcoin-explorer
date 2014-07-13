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
#ifndef SX_GENERATED_HPP
#define SX_GENERATED_HPP

#include <functional>
#include <memory>
#include <string>
#include <sx/command.hpp>
#include <sx/command/addr.hpp>
#include <sx/command/addr-decode.hpp>
#include <sx/command/addr-encode.hpp>
#include <sx/command/balance.hpp>
#include <sx/command/base58-decode.hpp>
#include <sx/command/base58-encode.hpp>
#include <sx/command/base58check-decode.hpp>
#include <sx/command/base58check-encode.hpp>
#include <sx/command/bci-fetch-last-height.hpp>
#include <sx/command/bci-history.hpp>
#include <sx/command/blke-fetch-transaction.hpp>
#include <sx/command/brainwallet.hpp>
#include <sx/command/btc.hpp>
#include <sx/command/ec-add.hpp>
#include <sx/command/ec-add-secrets.hpp>
#include <sx/command/ec-multiply.hpp>
#include <sx/command/ec-multiply-secrets.hpp>
#include <sx/command/embed-addr.hpp>
#include <sx/command/fetch-header-hash.hpp>
#include <sx/command/fetch-header-height.hpp>
#include <sx/command/fetch-last-height.hpp>
#include <sx/command/fetch-stealth.hpp>
#include <sx/command/fetch-transaction.hpp>
#include <sx/command/fetch-transaction-index.hpp>
#include <sx/command/help.hpp>
#include <sx/command/history.hpp>
#include <sx/command/satoshi.hpp>
#include <sx/command/stealth-addr.hpp>
#include <sx/command/unwrap.hpp>
#include <sx/command/wrap.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

#define SX_VARIABLE_CONFIG "config"

namespace sx {

/**
 * Invoke a specified function on all commands.
 *
 * @param[in]  func  The function to invoke on all commands.
 * @return           True if invoked successfully.
 */
bool broadcast(const std::function<void(std::shared_ptr<command>)> func);

/**
 * Find the command identified by the specified symbolic command name.
 *
 * @param[in]  symbol  The symbolic command name.
 * @return             An instance of the command or nullptr if not found.
 */
std::shared_ptr<command> find(const std::string& symbol);

} // sx

#endif
