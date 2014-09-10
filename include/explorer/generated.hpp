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
#ifndef BX_GENERATED_HPP
#define BX_GENERATED_HPP

#include <functional>
#include <memory>
#include <string>
#include <explorer/command.hpp>
#include <explorer/commands/address-decode.hpp>
#include <explorer/commands/address-embed.hpp>
#include <explorer/commands/address-encode.hpp>
#include <explorer/commands/address-validate.hpp>
#include <explorer/commands/base58-decode.hpp>
#include <explorer/commands/base58-encode.hpp>
#include <explorer/commands/base58check-decode.hpp>
#include <explorer/commands/base58check-encode.hpp>
#include <explorer/commands/bci-fetch-last-height.hpp>
#include <explorer/commands/bci-history.hpp>
#include <explorer/commands/bitcoin160.hpp>
#include <explorer/commands/bitcoin256.hpp>
#include <explorer/commands/blke-fetch-transaction.hpp>
#include <explorer/commands/btc-to-satoshi.hpp>
#include <explorer/commands/ec-add.hpp>
#include <explorer/commands/ec-add-secrets.hpp>
#include <explorer/commands/ec-lock.hpp>
#include <explorer/commands/ec-multiply.hpp>
#include <explorer/commands/ec-multiply-secrets.hpp>
#include <explorer/commands/ec-new.hpp>
#include <explorer/commands/ec-to-address.hpp>
#include <explorer/commands/ec-to-public.hpp>
#include <explorer/commands/ec-to-wif.hpp>
#include <explorer/commands/ec-unlock.hpp>
#include <explorer/commands/fetch-balance.hpp>
#include <explorer/commands/fetch-confirmations.hpp>
#include <explorer/commands/fetch-header.hpp>
#include <explorer/commands/fetch-height.hpp>
#include <explorer/commands/fetch-history.hpp>
#include <explorer/commands/fetch-public-key.hpp>
#include <explorer/commands/fetch-stealth.hpp>
#include <explorer/commands/fetch-tx.hpp>
#include <explorer/commands/fetch-tx-index.hpp>
#include <explorer/commands/fetch-utxo.hpp>
#include <explorer/commands/genaddr.hpp>
#include <explorer/commands/genpriv.hpp>
#include <explorer/commands/genpub.hpp>
#include <explorer/commands/hd-new.hpp>
#include <explorer/commands/hd-private.hpp>
#include <explorer/commands/hd-public.hpp>
#include <explorer/commands/hd-to-address.hpp>
#include <explorer/commands/hd-to-ec.hpp>
#include <explorer/commands/hd-to-public.hpp>
#include <explorer/commands/hd-to-wif.hpp>
#include <explorer/commands/help.hpp>
#include <explorer/commands/initchain.hpp>
#include <explorer/commands/input-set.hpp>
#include <explorer/commands/input-sign.hpp>
#include <explorer/commands/input-validate.hpp>
#include <explorer/commands/mnemonic-decode.hpp>
#include <explorer/commands/mnemonic-encode.hpp>
#include <explorer/commands/mpk.hpp>
#include <explorer/commands/newseed.hpp>
#include <explorer/commands/qrcode.hpp>
#include <explorer/commands/ripemd160.hpp>
#include <explorer/commands/satoshi-to-btc.hpp>
#include <explorer/commands/script-decode.hpp>
#include <explorer/commands/script-encode.hpp>
#include <explorer/commands/script-to-address.hpp>
#include <explorer/commands/seed.hpp>
#include <explorer/commands/send-tx.hpp>
#include <explorer/commands/send-tx-node.hpp>
#include <explorer/commands/send-tx-p2p.hpp>
#include <explorer/commands/sendtx-bci.hpp>
#include <explorer/commands/sha160.hpp>
#include <explorer/commands/sha256.hpp>
#include <explorer/commands/sha512.hpp>
#include <explorer/commands/showblkhead.hpp>
#include <explorer/commands/stealth-address-decode.hpp>
#include <explorer/commands/stealth-address-encode.hpp>
#include <explorer/commands/stealth-new.hpp>
#include <explorer/commands/stealth-newkey.hpp>
#include <explorer/commands/stealth-shared-secret.hpp>
#include <explorer/commands/stealth-uncover-public.hpp>
#include <explorer/commands/stealth-uncover-secret.hpp>
#include <explorer/commands/tx-decode.hpp>
#include <explorer/commands/tx-encode.hpp>
#include <explorer/commands/tx-sign.hpp>
#include <explorer/commands/wallet.hpp>
#include <explorer/commands/watch-stealth.hpp>
#include <explorer/commands/watch-tx.hpp>
#include <explorer/commands/wif-to-ec.hpp>
#include <explorer/commands/wif-to-public.hpp>
#include <explorer/commands/wrap-decode.hpp>
#include <explorer/commands/wrap-encode.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

#define BX_VARIABLE_CONFIG "config"

namespace libbitcoin {
namespace explorer {

/**
 * Invoke a specified function on all commands.
 * @param[in]  func  The function to invoke on all commands.
 * @return           True if invoked successfully.
 */
bool broadcast(const std::function<void(std::shared_ptr<command>)> func);

/**
 * Find the command identified by the specified symbolic command name.
 * @param[in]  symbol  The symbolic command name.
 * @return             An instance of the command or nullptr if not found.
 */
std::shared_ptr<command> find(const std::string& symbol);

} // namespace explorer
} // namespace libbitcoin

#endif
