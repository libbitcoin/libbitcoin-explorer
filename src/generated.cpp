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
#include <sx/generated.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace sx {
namespace extensions {

std::shared_ptr<command> find(const std::string& symbol)
{
    if (symbol == addr::symbol())
        return std::make_shared<addr>();
    if (symbol == balance::symbol())
        return std::make_shared<balance>();
    if (symbol == base58_decode::symbol())
        return std::make_shared<base58_decode>();
    if (symbol == base58_encode::symbol())
        return std::make_shared<base58_encode>();
    if (symbol == base58check_decode::symbol())
        return std::make_shared<base58check_decode>();
    if (symbol == base58check_encode::symbol())
        return std::make_shared<base58check_encode>();
    if (symbol == bci_fetch_last_height::symbol())
        return std::make_shared<bci_fetch_last_height>();
    if (symbol == bci_history::symbol())
        return std::make_shared<bci_history>();
    if (symbol == blke_fetch_transaction::symbol())
        return std::make_shared<blke_fetch_transaction>();
    if (symbol == brainwallet::symbol())
        return std::make_shared<brainwallet>();
    if (symbol == btc::symbol())
        return std::make_shared<btc>();
    if (symbol == decode_addr::symbol())
        return std::make_shared<decode_addr>();
    if (symbol == ec_add::symbol())
        return std::make_shared<ec_add>();
    if (symbol == ec_add_modp::symbol())
        return std::make_shared<ec_add_modp>();
    if (symbol == ec_multiply::symbol())
        return std::make_shared<ec_multiply>();
    if (symbol == ec_tweak_add::symbol())
        return std::make_shared<ec_tweak_add>();
    if (symbol == embed_addr::symbol())
        return std::make_shared<embed_addr>();
    if (symbol == encode_addr::symbol())
        return std::make_shared<encode_addr>();
    if (symbol == fetch_block_header::symbol())
        return std::make_shared<fetch_block_header>();
    if (symbol == fetch_last_height::symbol())
        return std::make_shared<fetch_last_height>();
    if (symbol == fetch_stealth::symbol())
        return std::make_shared<fetch_stealth>();
    if (symbol == fetch_transaction::symbol())
        return std::make_shared<fetch_transaction>();
    if (symbol == fetch_transaction_index::symbol())
        return std::make_shared<fetch_transaction_index>();
    if (symbol == genaddr::symbol())
        return std::make_shared<genaddr>();
    if (symbol == genpriv::symbol())
        return std::make_shared<genpriv>();
    if (symbol == genpub::symbol())
        return std::make_shared<genpub>();
    if (symbol == get_pubkey::symbol())
        return std::make_shared<get_pubkey>();
    if (symbol == get_utxo::symbol())
        return std::make_shared<get_utxo>();
    if (symbol == hd_priv::symbol())
        return std::make_shared<hd_priv>();
    if (symbol == hd_pub::symbol())
        return std::make_shared<hd_pub>();
    if (symbol == hd_seed::symbol())
        return std::make_shared<hd_seed>();
    if (symbol == hd_to_address::symbol())
        return std::make_shared<hd_to_address>();
    if (symbol == hd_to_wif::symbol())
        return std::make_shared<hd_to_wif>();
    if (symbol == history::symbol())
        return std::make_shared<history>();
    if (symbol == initchain::symbol())
        return std::make_shared<initchain>();
    if (symbol == mktx::symbol())
        return std::make_shared<mktx>();
    if (symbol == mnemonic::symbol())
        return std::make_shared<mnemonic>();
    if (symbol == monitor::symbol())
        return std::make_shared<monitor>();
    if (symbol == mpk::symbol())
        return std::make_shared<mpk>();
    if (symbol == newkey::symbol())
        return std::make_shared<newkey>();
    if (symbol == newseed::symbol())
        return std::make_shared<newseed>();
    if (symbol == pubkey::symbol())
        return std::make_shared<pubkey>();
    if (symbol == qrcode::symbol())
        return std::make_shared<qrcode>();
    if (symbol == rawscript::symbol())
        return std::make_shared<rawscript>();
    if (symbol == ripemd_hash::symbol())
        return std::make_shared<ripemd_hash>();
    if (symbol == satoshi::symbol())
        return std::make_shared<satoshi>();
    if (symbol == scripthash::symbol())
        return std::make_shared<scripthash>();
    if (symbol == secret_to_wif::symbol())
        return std::make_shared<secret_to_wif>();
    if (symbol == sendtx_bci::symbol())
        return std::make_shared<sendtx_bci>();
    if (symbol == sendtx_node::symbol())
        return std::make_shared<sendtx_node>();
    if (symbol == sendtx_obelisk::symbol())
        return std::make_shared<sendtx_obelisk>();
    if (symbol == sendtx_p2p::symbol())
        return std::make_shared<sendtx_p2p>();
    if (symbol == set_input::symbol())
        return std::make_shared<set_input>();
    if (symbol == sha256::symbol())
        return std::make_shared<sha256>();
    if (symbol == showblkhead::symbol())
        return std::make_shared<showblkhead>();
    if (symbol == showscript::symbol())
        return std::make_shared<showscript>();
    if (symbol == showtx::symbol())
        return std::make_shared<showtx>();
    if (symbol == sign_input::symbol())
        return std::make_shared<sign_input>();
    if (symbol == stealth_addr::symbol())
        return std::make_shared<stealth_addr>();
    if (symbol == stealth_initiate::symbol())
        return std::make_shared<stealth_initiate>();
    if (symbol == stealth_newkey::symbol())
        return std::make_shared<stealth_newkey>();
    if (symbol == stealth_show_addr::symbol())
        return std::make_shared<stealth_show_addr>();
    if (symbol == stealth_uncover::symbol())
        return std::make_shared<stealth_uncover>();
    if (symbol == stealth_uncover_secret::symbol())
        return std::make_shared<stealth_uncover_secret>();
    if (symbol == unwrap::symbol())
        return std::make_shared<unwrap>();
    if (symbol == validaddr::symbol())
        return std::make_shared<validaddr>();
    if (symbol == validsig::symbol())
        return std::make_shared<validsig>();
    if (symbol == validtx::symbol())
        return std::make_shared<validtx>();
    if (symbol == wallet::symbol())
        return std::make_shared<wallet>();
    if (symbol == watchtx::symbol())
        return std::make_shared<watchtx>();
    if (symbol == wif_to_secret::symbol())
        return std::make_shared<wif_to_secret>();
    if (symbol == wrap::symbol())
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
    func(std::make_shared<ec_add>());
    func(std::make_shared<ec_add_modp>());
    func(std::make_shared<ec_multiply>());
    func(std::make_shared<ec_tweak_add>());
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
