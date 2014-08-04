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
#include <sx/command/addr-decode.hpp>
#include <sx/command/addr-embed.hpp>
#include <sx/command/addr-encode.hpp>
#include <sx/command/addr-validate.hpp>
#include <sx/command/balance.hpp>
#include <sx/command/base58-decode.hpp>
#include <sx/command/base58-encode.hpp>
#include <sx/command/base58check-decode.hpp>
#include <sx/command/base58check-encode.hpp>
#include <sx/command/bci-fetch-last-height.hpp>
#include <sx/command/bci-history.hpp>
#include <sx/command/bci-send-transaction.hpp>
#include <sx/command/be-fetch-transaction.hpp>
#include <sx/command/bitcoin160.hpp>
#include <sx/command/bitcoin256.hpp>
#include <sx/command/btc.hpp>
#include <sx/command/ec-add.hpp>
#include <sx/command/ec-add-secrets.hpp>
#include <sx/command/ec-lock.hpp>
#include <sx/command/ec-multiply.hpp>
#include <sx/command/ec-multiply-secrets.hpp>
#include <sx/command/ec-new.hpp>
#include <sx/command/ec-to-addr.hpp>
#include <sx/command/ec-to-pub.hpp>
#include <sx/command/ec-to-wif.hpp>
#include <sx/command/ec-unlock.hpp>
#include <sx/command/fetch-header.hpp>
#include <sx/command/fetch-last-height.hpp>
#include <sx/command/fetch-public-key.hpp>
#include <sx/command/fetch-stealth.hpp>
#include <sx/command/fetch-transaction.hpp>
#include <sx/command/fetch-transaction-index.hpp>
#include <sx/command/fetch-utxo.hpp>
#include <sx/command/genaddr.hpp>
#include <sx/command/genpriv.hpp>
#include <sx/command/genpub.hpp>
#include <sx/command/hd-new.hpp>
#include <sx/command/hd-priv.hpp>
#include <sx/command/hd-pub.hpp>
#include <sx/command/hd-to-addr.hpp>
#include <sx/command/hd-to-ec.hpp>
#include <sx/command/hd-to-pub.hpp>
#include <sx/command/hd-to-wif.hpp>
#include <sx/command/help.hpp>
#include <sx/command/history.hpp>
#include <sx/command/initchain.hpp>
#include <sx/command/mnemonic-decode.hpp>
#include <sx/command/mnemonic-encode.hpp>
#include <sx/command/monitor.hpp>
#include <sx/command/mpk.hpp>
#include <sx/command/newseed.hpp>
#include <sx/command/qrcode.hpp>
#include <sx/command/rawscript.hpp>
#include <sx/command/ripemd160.hpp>
#include <sx/command/satoshi.hpp>
#include <sx/command/scripthash.hpp>
#include <sx/command/seed.hpp>
#include <sx/command/sendtx-node.hpp>
#include <sx/command/sendtx-obelisk.hpp>
#include <sx/command/sendtx-p2p.hpp>
#include <sx/command/sha160.hpp>
#include <sx/command/sha256.hpp>
#include <sx/command/sha512.hpp>
#include <sx/command/showscript.hpp>
#include <sx/command/signtx.hpp>
#include <sx/command/stealth-addr.hpp>
#include <sx/command/unwrap.hpp>
#include <sx/command/validtx.hpp>
#include <sx/command/wallet.hpp>
#include <sx/command/watchtx.hpp>
#include <sx/command/wif-to-ec.hpp>
#include <sx/command/wif-to-pub.hpp>
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
