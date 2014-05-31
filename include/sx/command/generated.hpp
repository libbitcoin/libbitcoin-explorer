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
#ifndef SX_GENERATED_HPP
#define SX_GENERATED_HPP

#include <functional>
#include <memory>
#include <string>
#include <sx/command.hpp>

#include <sx/command/addr.hpp>
#include <sx/command/balance.hpp>
#include <sx/command/base58_decode.hpp>
#include <sx/command/base58_encode.hpp>
#include <sx/command/base58check_decode.hpp>
#include <sx/command/base58check_encode.hpp>
#include <sx/command/bci_fetch_last_height.hpp>
#include <sx/command/bci_history.hpp>
#include <sx/command/blke_fetch_transaction.hpp>
#include <sx/command/brainwallet.hpp>
#include <sx/command/btc.hpp>
#include <sx/command/decode_addr.hpp>
#include <sx/command/ec_add_modp.hpp>
#include <sx/command/ec_multiply.hpp>
#include <sx/command/ec_tweak_add.hpp>
#include <sx/command/ec_add.hpp>
#include <sx/command/embed_addr.hpp>
#include <sx/command/encode_addr.hpp>
#include <sx/command/fetch_block_header.hpp>
#include <sx/command/fetch_last_height.hpp>
#include <sx/command/fetch_stealth.hpp>
#include <sx/command/fetch_transaction.hpp>
#include <sx/command/fetch_transaction_index.hpp>
#include <sx/command/genaddr.hpp>
#include <sx/command/genpriv.hpp>
#include <sx/command/genpub.hpp>
#include <sx/command/get_pubkey.hpp>
#include <sx/command/get_utxo.hpp>
#include <sx/command/hd_priv.hpp>
#include <sx/command/hd_pub.hpp>
#include <sx/command/hd_seed.hpp>
#include <sx/command/hd_to_address.hpp>
#include <sx/command/hd_to_wif.hpp>
#include <sx/command/history.hpp>
#include <sx/command/initchain.hpp>
#include <sx/command/mktx.hpp>
#include <sx/command/mnemonic.hpp>
#include <sx/command/monitor.hpp>
#include <sx/command/mpk.hpp>
#include <sx/command/newkey.hpp>
#include <sx/command/newseed.hpp>
#include <sx/command/pubkey.hpp>
#include <sx/command/qrcode.hpp>
#include <sx/command/rawscript.hpp>
#include <sx/command/ripemd_hash.hpp>
#include <sx/command/satoshi.hpp>
#include <sx/command/scripthash.hpp>
#include <sx/command/secret_to_wif.hpp>
#include <sx/command/sendtx_bci.hpp>
#include <sx/command/sendtx_node.hpp>
#include <sx/command/sendtx_obelisk.hpp>
#include <sx/command/sendtx_p2p.hpp>
#include <sx/command/set_input.hpp>
#include <sx/command/sha256.hpp>
#include <sx/command/showblkhead.hpp>
#include <sx/command/showscript.hpp>
#include <sx/command/showtx.hpp>
#include <sx/command/sign_input.hpp>
#include <sx/command/stealth_addr.hpp>
#include <sx/command/stealth_initiate.hpp>
#include <sx/command/stealth_newkey.hpp>
#include <sx/command/stealth_show_addr.hpp>
#include <sx/command/stealth_uncover.hpp>
#include <sx/command/stealth_uncover_secret.hpp>
#include <sx/command/unwrap.hpp>
#include <sx/command/validaddr.hpp>
#include <sx/command/validsig.hpp>
#include <sx/command/validtx.hpp>
#include <sx/command/wallet.hpp>
#include <sx/command/watchtx.hpp>
#include <sx/command/wif_to_secret.hpp>
#include <sx/command/wrap.hpp>

/********** WARNING: This file is generated, do not edit directly. **********/

namespace sx {
namespace extensions {

/**
 * Find the command identified by the specified symbolic command name.
 *
 * @param[in]  symbol  The symbolic command name.
 * @return             An instance of the command or nullptr if not found.
 */
std::shared_ptr<command> find(const char* symbol);

/**
 * Invoke a specified function on all commands.
 *
 * @param[in]  func  The function to invoke on all commands.
 * @return           True if invoked successfully.
 */
bool broadcast(const std::function<void(std::shared_ptr<command>)> func);

} // extensions
} // sx

#endif
