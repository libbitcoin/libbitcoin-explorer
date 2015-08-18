/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
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
#include <bitcoin/explorer/generated.hpp>

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <bitcoin/explorer/command.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace po;
using namespace std;
using namespace boost::filesystem;
    
namespace libbitcoin {
namespace explorer {
using namespace commands;

void broadcast(const function<void(shared_ptr<command>)> func)
{
    func(make_shared<address_decode>());
    func(make_shared<address_embed>());
    func(make_shared<address_encode>());
    func(make_shared<address_validate>());
    func(make_shared<base16_decode>());
    func(make_shared<base16_encode>());
    func(make_shared<base58_decode>());
    func(make_shared<base58_encode>());
    func(make_shared<base58check_decode>());
    func(make_shared<base58check_encode>());
    func(make_shared<base64_decode>());
    func(make_shared<base64_encode>());
    func(make_shared<bci_fetch_last_height>());
    func(make_shared<bci_history>());
    func(make_shared<bitcoin160>());
    func(make_shared<bitcoin256>());
    func(make_shared<blke_fetch_transaction>());
    func(make_shared<btc_to_satoshi>());
    func(make_shared<cert_new>());
    func(make_shared<cert_public>());
    func(make_shared<ec_add>());
    func(make_shared<ec_add_secrets>());
    func(make_shared<ec_lock>());
    func(make_shared<ec_lock_verify>());
    func(make_shared<ec_multiply>());
    func(make_shared<ec_multiply_secrets>());
    func(make_shared<ec_new>());
    func(make_shared<ec_to_address>());
    func(make_shared<ec_to_public>());
    func(make_shared<ec_to_wif>());
    func(make_shared<ec_unlock>());
    func(make_shared<fetch_balance>());
    func(make_shared<fetch_header>());
    func(make_shared<fetch_height>());
    func(make_shared<fetch_history>());
    func(make_shared<fetch_public_key>());
    func(make_shared<fetch_stealth>());
    func(make_shared<fetch_tx>());
    func(make_shared<fetch_tx_index>());
    func(make_shared<fetch_utxo>());
    func(make_shared<genaddr>());
    func(make_shared<genpriv>());
    func(make_shared<genpub>());
    func(make_shared<hd_new>());
    func(make_shared<hd_private>());
    func(make_shared<hd_public>());
    func(make_shared<hd_to_address>());
    func(make_shared<hd_to_ec>());
    func(make_shared<hd_to_public>());
    func(make_shared<hd_to_wif>());
    func(make_shared<help>());
    func(make_shared<initchain>());
    func(make_shared<input_set>());
    func(make_shared<input_sign>());
    func(make_shared<input_validate>());
    func(make_shared<message_sign>());
    func(make_shared<message_validate>());
    func(make_shared<mnemonic_decode>());
    func(make_shared<mnemonic_encode>());
    func(make_shared<mnemonic_new>());
    func(make_shared<mnemonic_to_seed>());
    func(make_shared<mpk>());
    func(make_shared<newseed>());
    func(make_shared<qrcode>());
    func(make_shared<ripemd160>());
    func(make_shared<satoshi_to_btc>());
    func(make_shared<script_decode>());
    func(make_shared<script_encode>());
    func(make_shared<script_to_address>());
    func(make_shared<seed>());
    func(make_shared<send_tx>());
    func(make_shared<send_tx_node>());
    func(make_shared<send_tx_p2p>());
    func(make_shared<sendtx_bci>());
    func(make_shared<settings>());
    func(make_shared<sha160>());
    func(make_shared<sha256>());
    func(make_shared<sha512>());
    func(make_shared<showblkhead>());
    func(make_shared<stealth_decode>());
    func(make_shared<stealth_encode>());
    func(make_shared<stealth_initiate>());
    func(make_shared<stealth_newkey>());
    func(make_shared<stealth_public>());
    func(make_shared<stealth_secret>());
    func(make_shared<stealth_shared>());
    func(make_shared<tx_decode>());
    func(make_shared<tx_encode>());
    func(make_shared<tx_sign>());
    func(make_shared<uri_decode>());
    func(make_shared<uri_encode>());
    func(make_shared<validate_tx>());
    func(make_shared<wallet>());
    func(make_shared<watch_address>());
    func(make_shared<watch_tx>());
    func(make_shared<wif_to_ec>());
    func(make_shared<wif_to_public>());
    func(make_shared<wrap_decode>());
    func(make_shared<wrap_encode>());
}

shared_ptr<command> find(const string& symbol)
{
    if (symbol == address_decode::symbol())
        return make_shared<address_decode>();
    if (symbol == address_embed::symbol())
        return make_shared<address_embed>();
    if (symbol == address_encode::symbol())
        return make_shared<address_encode>();
    if (symbol == address_validate::symbol())
        return make_shared<address_validate>();
    if (symbol == base16_decode::symbol())
        return make_shared<base16_decode>();
    if (symbol == base16_encode::symbol())
        return make_shared<base16_encode>();
    if (symbol == base58_decode::symbol())
        return make_shared<base58_decode>();
    if (symbol == base58_encode::symbol())
        return make_shared<base58_encode>();
    if (symbol == base58check_decode::symbol())
        return make_shared<base58check_decode>();
    if (symbol == base58check_encode::symbol())
        return make_shared<base58check_encode>();
    if (symbol == base64_decode::symbol())
        return make_shared<base64_decode>();
    if (symbol == base64_encode::symbol())
        return make_shared<base64_encode>();
    if (symbol == bci_fetch_last_height::symbol())
        return make_shared<bci_fetch_last_height>();
    if (symbol == bci_history::symbol())
        return make_shared<bci_history>();
    if (symbol == bitcoin160::symbol())
        return make_shared<bitcoin160>();
    if (symbol == bitcoin256::symbol())
        return make_shared<bitcoin256>();
    if (symbol == blke_fetch_transaction::symbol())
        return make_shared<blke_fetch_transaction>();
    if (symbol == btc_to_satoshi::symbol())
        return make_shared<btc_to_satoshi>();
    if (symbol == cert_new::symbol())
        return make_shared<cert_new>();
    if (symbol == cert_public::symbol())
        return make_shared<cert_public>();
    if (symbol == ec_add::symbol())
        return make_shared<ec_add>();
    if (symbol == ec_add_secrets::symbol())
        return make_shared<ec_add_secrets>();
    if (symbol == ec_lock::symbol())
        return make_shared<ec_lock>();
    if (symbol == ec_lock_verify::symbol())
        return make_shared<ec_lock_verify>();
    if (symbol == ec_multiply::symbol())
        return make_shared<ec_multiply>();
    if (symbol == ec_multiply_secrets::symbol())
        return make_shared<ec_multiply_secrets>();
    if (symbol == ec_new::symbol())
        return make_shared<ec_new>();
    if (symbol == ec_to_address::symbol())
        return make_shared<ec_to_address>();
    if (symbol == ec_to_public::symbol())
        return make_shared<ec_to_public>();
    if (symbol == ec_to_wif::symbol())
        return make_shared<ec_to_wif>();
    if (symbol == ec_unlock::symbol())
        return make_shared<ec_unlock>();
    if (symbol == fetch_balance::symbol())
        return make_shared<fetch_balance>();
    if (symbol == fetch_header::symbol())
        return make_shared<fetch_header>();
    if (symbol == fetch_height::symbol())
        return make_shared<fetch_height>();
    if (symbol == fetch_history::symbol())
        return make_shared<fetch_history>();
    if (symbol == fetch_public_key::symbol())
        return make_shared<fetch_public_key>();
    if (symbol == fetch_stealth::symbol())
        return make_shared<fetch_stealth>();
    if (symbol == fetch_tx::symbol())
        return make_shared<fetch_tx>();
    if (symbol == fetch_tx_index::symbol())
        return make_shared<fetch_tx_index>();
    if (symbol == fetch_utxo::symbol())
        return make_shared<fetch_utxo>();
    if (symbol == genaddr::symbol())
        return make_shared<genaddr>();
    if (symbol == genpriv::symbol())
        return make_shared<genpriv>();
    if (symbol == genpub::symbol())
        return make_shared<genpub>();
    if (symbol == hd_new::symbol())
        return make_shared<hd_new>();
    if (symbol == hd_private::symbol())
        return make_shared<hd_private>();
    if (symbol == hd_public::symbol())
        return make_shared<hd_public>();
    if (symbol == hd_to_address::symbol())
        return make_shared<hd_to_address>();
    if (symbol == hd_to_ec::symbol())
        return make_shared<hd_to_ec>();
    if (symbol == hd_to_public::symbol())
        return make_shared<hd_to_public>();
    if (symbol == hd_to_wif::symbol())
        return make_shared<hd_to_wif>();
    if (symbol == help::symbol())
        return make_shared<help>();
    if (symbol == initchain::symbol())
        return make_shared<initchain>();
    if (symbol == input_set::symbol())
        return make_shared<input_set>();
    if (symbol == input_sign::symbol())
        return make_shared<input_sign>();
    if (symbol == input_validate::symbol())
        return make_shared<input_validate>();
    if (symbol == message_sign::symbol())
        return make_shared<message_sign>();
    if (symbol == message_validate::symbol())
        return make_shared<message_validate>();
    if (symbol == mnemonic_decode::symbol())
        return make_shared<mnemonic_decode>();
    if (symbol == mnemonic_encode::symbol())
        return make_shared<mnemonic_encode>();
    if (symbol == mnemonic_new::symbol())
        return make_shared<mnemonic_new>();
    if (symbol == mnemonic_to_seed::symbol())
        return make_shared<mnemonic_to_seed>();
    if (symbol == mpk::symbol())
        return make_shared<mpk>();
    if (symbol == newseed::symbol())
        return make_shared<newseed>();
    if (symbol == qrcode::symbol())
        return make_shared<qrcode>();
    if (symbol == ripemd160::symbol())
        return make_shared<ripemd160>();
    if (symbol == satoshi_to_btc::symbol())
        return make_shared<satoshi_to_btc>();
    if (symbol == script_decode::symbol())
        return make_shared<script_decode>();
    if (symbol == script_encode::symbol())
        return make_shared<script_encode>();
    if (symbol == script_to_address::symbol())
        return make_shared<script_to_address>();
    if (symbol == seed::symbol())
        return make_shared<seed>();
    if (symbol == send_tx::symbol())
        return make_shared<send_tx>();
    if (symbol == send_tx_node::symbol())
        return make_shared<send_tx_node>();
    if (symbol == send_tx_p2p::symbol())
        return make_shared<send_tx_p2p>();
    if (symbol == sendtx_bci::symbol())
        return make_shared<sendtx_bci>();
    if (symbol == settings::symbol())
        return make_shared<settings>();
    if (symbol == sha160::symbol())
        return make_shared<sha160>();
    if (symbol == sha256::symbol())
        return make_shared<sha256>();
    if (symbol == sha512::symbol())
        return make_shared<sha512>();
    if (symbol == showblkhead::symbol())
        return make_shared<showblkhead>();
    if (symbol == stealth_decode::symbol())
        return make_shared<stealth_decode>();
    if (symbol == stealth_encode::symbol())
        return make_shared<stealth_encode>();
    if (symbol == stealth_initiate::symbol())
        return make_shared<stealth_initiate>();
    if (symbol == stealth_newkey::symbol())
        return make_shared<stealth_newkey>();
    if (symbol == stealth_public::symbol())
        return make_shared<stealth_public>();
    if (symbol == stealth_secret::symbol())
        return make_shared<stealth_secret>();
    if (symbol == stealth_shared::symbol())
        return make_shared<stealth_shared>();
    if (symbol == tx_decode::symbol())
        return make_shared<tx_decode>();
    if (symbol == tx_encode::symbol())
        return make_shared<tx_encode>();
    if (symbol == tx_sign::symbol())
        return make_shared<tx_sign>();
    if (symbol == uri_decode::symbol())
        return make_shared<uri_decode>();
    if (symbol == uri_encode::symbol())
        return make_shared<uri_encode>();
    if (symbol == validate_tx::symbol())
        return make_shared<validate_tx>();
    if (symbol == wallet::symbol())
        return make_shared<wallet>();
    if (symbol == watch_address::symbol())
        return make_shared<watch_address>();
    if (symbol == watch_tx::symbol())
        return make_shared<watch_tx>();
    if (symbol == wif_to_ec::symbol())
        return make_shared<wif_to_ec>();
    if (symbol == wif_to_public::symbol())
        return make_shared<wif_to_public>();
    if (symbol == wrap_decode::symbol())
        return make_shared<wrap_decode>();
    if (symbol == wrap_encode::symbol())
        return make_shared<wrap_encode>();

    return nullptr;
}

std::string formerly(const string& former)
{
    if (former == address_decode::formerly())
        return address_decode::symbol();
    if (former == address_embed::formerly())
        return address_embed::symbol();
    if (former == address_encode::formerly())
        return address_encode::symbol();
    if (former == address_validate::formerly())
        return address_validate::symbol();
    if (former == btc_to_satoshi::formerly())
        return btc_to_satoshi::symbol();
    if (former == ec_add_secrets::formerly())
        return ec_add_secrets::symbol();
    if (former == ec_lock::formerly())
        return ec_lock::symbol();
    if (former == ec_multiply_secrets::formerly())
        return ec_multiply_secrets::symbol();
    if (former == ec_new::formerly())
        return ec_new::symbol();
    if (former == ec_to_address::formerly())
        return ec_to_address::symbol();
    if (former == ec_to_public::formerly())
        return ec_to_public::symbol();
    if (former == fetch_height::formerly())
        return fetch_height::symbol();
    if (former == fetch_public_key::formerly())
        return fetch_public_key::symbol();
    if (former == fetch_tx::formerly())
        return fetch_tx::symbol();
    if (former == fetch_tx_index::formerly())
        return fetch_tx_index::symbol();
    if (former == fetch_utxo::formerly())
        return fetch_utxo::symbol();
    if (former == hd_new::formerly())
        return hd_new::symbol();
    if (former == input_set::formerly())
        return input_set::symbol();
    if (former == input_sign::formerly())
        return input_sign::symbol();
    if (former == input_validate::formerly())
        return input_validate::symbol();
    if (former == mnemonic_encode::formerly())
        return mnemonic_encode::symbol();
    if (former == ripemd160::formerly())
        return ripemd160::symbol();
    if (former == satoshi_to_btc::formerly())
        return satoshi_to_btc::symbol();
    if (former == script_decode::formerly())
        return script_decode::symbol();
    if (former == script_encode::formerly())
        return script_encode::symbol();
    if (former == script_to_address::formerly())
        return script_to_address::symbol();
    if (former == send_tx::formerly())
        return send_tx::symbol();
    if (former == send_tx_node::formerly())
        return send_tx_node::symbol();
    if (former == send_tx_p2p::formerly())
        return send_tx_p2p::symbol();
    if (former == stealth_decode::formerly())
        return stealth_decode::symbol();
    if (former == stealth_public::formerly())
        return stealth_public::symbol();
    if (former == stealth_secret::formerly())
        return stealth_secret::symbol();
    if (former == tx_sign::formerly())
        return tx_sign::symbol();
    if (former == validate_tx::formerly())
        return validate_tx::symbol();
    if (former == watch_address::formerly())
        return watch_address::symbol();
    if (former == watch_tx::formerly())
        return watch_tx::symbol();
    if (former == wrap_decode::formerly())
        return wrap_decode::symbol();
    if (former == wrap_encode::formerly())
        return wrap_encode::symbol();

    return "";
}

} // namespace explorer
} // namespace libbitcoin
