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
    const auto symbolic = std::string(symbol);

    if (symbolic == addr::symbol())
        return std::make_shared<addr>();
    if (symbolic == balance::symbol())
        return std::make_shared<balance>();
    if (symbolic == base58_decode::symbol())
        return std::make_shared<base58_decode>();
    if (symbolic == base58_encode::symbol())
        return std::make_shared<base58_encode>();
    if (symbolic == base58check_decode::symbol())
        return std::make_shared<base58check_decode>();
    if (symbolic == base58check_encode::symbol())
        return std::make_shared<base58check_encode>();
    if (symbolic == bci_fetch_last_height::symbol())
        return std::make_shared<bci_fetch_last_height>();
    if (symbolic == bci_history::symbol())
        return std::make_shared<bci_history>();
    if (symbolic == blke_fetch_transaction::symbol())
        return std::make_shared<blke_fetch_transaction>();
    if (symbolic == brainwallet::symbol())
        return std::make_shared<brainwallet>();
    if (symbolic == btc::symbol())
        return std::make_shared<btc>();
    if (symbolic == decode_addr::symbol())
        return std::make_shared<decode_addr>();
    if (symbolic == ec_add_modp::symbol())
        return std::make_shared<ec_add_modp>();
    if (symbolic == ec_multiply::symbol())
        return std::make_shared<ec_multiply>();
    if (symbolic == ec_tweak_add::symbol())
        return std::make_shared<ec_tweak_add>();
    if (symbolic == ec_add::symbol())
        return std::make_shared<ec_add>();
    if (symbolic == embed_addr::symbol())
        return std::make_shared<embed_addr>();
    if (symbolic == encode_addr::symbol())
        return std::make_shared<encode_addr>();
    if (symbolic == fetch_block_header::symbol())
        return std::make_shared<fetch_block_header>();
    if (symbolic == fetch_last_height::symbol())
        return std::make_shared<fetch_last_height>();
    if (symbolic == fetch_stealth::symbol())
        return std::make_shared<fetch_stealth>();
    if (symbolic == fetch_transaction::symbol())
        return std::make_shared<fetch_transaction>();
    if (symbolic == fetch_transaction_index::symbol())
        return std::make_shared<fetch_transaction_index>();
    if (symbolic == genaddr::symbol())
        return std::make_shared<genaddr>();
    if (symbolic == genpriv::symbol())
        return std::make_shared<genpriv>();
    if (symbolic == genpub::symbol())
        return std::make_shared<genpub>();
    if (symbolic == get_pubkey::symbol())
        return std::make_shared<get_pubkey>();
    if (symbolic == get_utxo::symbol())
        return std::make_shared<get_utxo>();
    if (symbolic == hd_priv::symbol())
        return std::make_shared<hd_priv>();
    if (symbolic == hd_pub::symbol())
        return std::make_shared<hd_pub>();
    if (symbolic == hd_seed::symbol())
        return std::make_shared<hd_seed>();
    if (symbolic == hd_to_address::symbol())
        return std::make_shared<hd_to_address>();
    if (symbolic == hd_to_wif::symbol())
        return std::make_shared<hd_to_wif>();
    if (symbolic == history::symbol())
        return std::make_shared<history>();
    if (symbolic == initchain::symbol())
        return std::make_shared<initchain>();
    if (symbolic == mktx::symbol())
        return std::make_shared<mktx>();
    if (symbolic == mnemonic::symbol())
        return std::make_shared<mnemonic>();
    if (symbolic == monitor::symbol())
        return std::make_shared<monitor>();
    if (symbolic == mpk::symbol())
        return std::make_shared<mpk>();
    if (symbolic == newkey::symbol())
        return std::make_shared<newkey>();
    if (symbolic == newseed::symbol())
        return std::make_shared<newseed>();
    if (symbolic == pubkey::symbol())
        return std::make_shared<pubkey>();
    if (symbolic == qrcode::symbol())
        return std::make_shared<qrcode>();
    if (symbolic == rawscript::symbol())
        return std::make_shared<rawscript>();
    if (symbolic == ripemd_hash::symbol())
        return std::make_shared<ripemd_hash>();
    if (symbolic == satoshi::symbol())
        return std::make_shared<satoshi>();
    if (symbolic == scripthash::symbol())
        return std::make_shared<scripthash>();
    if (symbolic == secret_to_wif::symbol())
        return std::make_shared<secret_to_wif>();
    if (symbolic == sendtx_bci::symbol())
        return std::make_shared<sendtx_bci>();
    if (symbolic == sendtx_node::symbol())
        return std::make_shared<sendtx_node>();
    if (symbolic == sendtx_obelisk::symbol())
        return std::make_shared<sendtx_obelisk>();
    if (symbolic == sendtx_p2p::symbol())
        return std::make_shared<sendtx_p2p>();
    if (symbolic == set_input::symbol())
        return std::make_shared<set_input>();
    if (symbolic == sha256::symbol())
        return std::make_shared<sha256>();
    if (symbolic == showblkhead::symbol())
        return std::make_shared<showblkhead>();
    if (symbolic == showscript::symbol())
        return std::make_shared<showscript>();
    if (symbolic == showtx::symbol())
        return std::make_shared<showtx>();
    if (symbolic == sign_input::symbol())
        return std::make_shared<sign_input>();
    if (symbolic == stealth_addr::symbol())
        return std::make_shared<stealth_addr>();
    if (symbolic == stealth_initiate::symbol())
        return std::make_shared<stealth_initiate>();
    if (symbolic == stealth_newkey::symbol())
        return std::make_shared<stealth_newkey>();
    if (symbolic == stealth_show_addr::symbol())
        return std::make_shared<stealth_show_addr>();
    if (symbolic == stealth_uncover::symbol())
        return std::make_shared<stealth_uncover>();
    if (symbolic == stealth_uncover_secret::symbol())
        return std::make_shared<stealth_uncover_secret>();
    if (symbolic == unwrap::symbol())
        return std::make_shared<unwrap>();
    if (symbolic == validaddr::symbol())
        return std::make_shared<validaddr>();
    if (symbolic == validsig::symbol())
        return std::make_shared<validsig>();
    if (symbolic == validtx::symbol())
        return std::make_shared<validtx>();
    if (symbolic == wallet::symbol())
        return std::make_shared<wallet>();
    if (symbolic == watchtx::symbol())
        return std::make_shared<watchtx>();
    if (symbolic == wif_to_secret::symbol())
        return std::make_shared<wif_to_secret>();
    if (symbolic == wrap::symbol())
        return std::make_shared<wrap>();

    return nullptr;
}

bool broadcast(const std::function<void(std::shared_ptr<command>)> func)
{
    func(std::make_shared<addr>());
    func(std::make_shared<balance>());
    func(std::make_shared<base58_decode>());
    func(std::make_shared<base58_encode>());
    func(std::make_shared<base58check_decode>());
    func(std::make_shared<base58check_encode>());
    func(std::make_shared<bci_fetch_last_height>());
    func(std::make_shared<bci_history>());
    func(std::make_shared<blke_fetch_transaction>());
    func(std::make_shared<brainwallet>());
    func(std::make_shared<btc>());
    func(std::make_shared<decode_addr>());
    func(std::make_shared<ec_add_modp>());
    func(std::make_shared<ec_multiply>());
    func(std::make_shared<ec_tweak_add>());
    func(std::make_shared<ec_add>());
    func(std::make_shared<embed_addr>());
    func(std::make_shared<encode_addr>());
    func(std::make_shared<fetch_block_header>());
    func(std::make_shared<fetch_last_height>());
    func(std::make_shared<fetch_stealth>());
    func(std::make_shared<fetch_transaction>());
    func(std::make_shared<fetch_transaction_index>());
    func(std::make_shared<genaddr>());
    func(std::make_shared<genpriv>());
    func(std::make_shared<genpub>());
    func(std::make_shared<get_pubkey>());
    func(std::make_shared<get_utxo>());
    func(std::make_shared<hd_priv>());
    func(std::make_shared<hd_pub>());
    func(std::make_shared<hd_seed>());
    func(std::make_shared<hd_to_address>());
    func(std::make_shared<hd_to_wif>());
    func(std::make_shared<history>());
    func(std::make_shared<initchain>());
    func(std::make_shared<mktx>());
    func(std::make_shared<mnemonic>());
    func(std::make_shared<monitor>());
    func(std::make_shared<mpk>());
    func(std::make_shared<newkey>());
    func(std::make_shared<newseed>());
    func(std::make_shared<pubkey>());
    func(std::make_shared<qrcode>());
    func(std::make_shared<rawscript>());
    func(std::make_shared<ripemd_hash>());
    func(std::make_shared<satoshi>());
    func(std::make_shared<scripthash>());
    func(std::make_shared<secret_to_wif>());
    func(std::make_shared<sendtx_bci>());
    func(std::make_shared<sendtx_node>());
    func(std::make_shared<sendtx_obelisk>());
    func(std::make_shared<sendtx_p2p>());
    func(std::make_shared<set_input>());
    func(std::make_shared<sha256>());
    func(std::make_shared<showblkhead>());
    func(std::make_shared<showscript>());
    func(std::make_shared<showtx>());
    func(std::make_shared<sign_input>());
    func(std::make_shared<stealth_addr>());
    func(std::make_shared<stealth_initiate>());
    func(std::make_shared<stealth_newkey>());
    func(std::make_shared<stealth_show_addr>());
    func(std::make_shared<stealth_uncover>());
    func(std::make_shared<stealth_uncover_secret>());
    func(std::make_shared<unwrap>());
    func(std::make_shared<validaddr>());
    func(std::make_shared<validsig>());
    func(std::make_shared<validtx>());
    func(std::make_shared<wallet>());
    func(std::make_shared<watchtx>());
    func(std::make_shared<wif_to_secret>());
    func(std::make_shared<wrap>());

    return true;
}

} // extensions
} // sx
