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
#include <sx/generated.hpp>

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <sx/command.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace po;
using namespace std;
using namespace boost::filesystem;
    
namespace sx {
using namespace extension;

bool broadcast(const function<void(shared_ptr<command>)> func)
{
    func(make_shared<addr_decode>());
    func(make_shared<addr_embed>());
    func(make_shared<addr_encode>());
    func(make_shared<addr_validate>());
    func(make_shared<balance>());
    func(make_shared<base58_decode>());
    func(make_shared<base58_encode>());
    func(make_shared<base58check_decode>());
    func(make_shared<base58check_encode>());
    func(make_shared<bci_fetch_last_height>());
    func(make_shared<bci_history>());
    func(make_shared<bci_send_transaction>());
    func(make_shared<be_fetch_transaction>());
    func(make_shared<bitcoin160>());
    func(make_shared<bitcoin256>());
    func(make_shared<btc>());
    func(make_shared<ec_add>());
    func(make_shared<ec_add_secrets>());
    func(make_shared<ec_lock>());
    func(make_shared<ec_multiply>());
    func(make_shared<ec_multiply_secrets>());
    func(make_shared<ec_new>());
    func(make_shared<ec_to_addr>());
    func(make_shared<ec_to_pub>());
    func(make_shared<ec_to_wif>());
    func(make_shared<ec_unlock>());
    func(make_shared<fetch_header>());
    func(make_shared<fetch_last_height>());
    func(make_shared<fetch_public_key>());
    func(make_shared<fetch_stealth>());
    func(make_shared<fetch_transaction>());
    func(make_shared<fetch_transaction_index>());
    func(make_shared<fetch_utxo>());
    func(make_shared<genaddr>());
    func(make_shared<genpriv>());
    func(make_shared<genpub>());
    func(make_shared<hd_new>());
    func(make_shared<hd_priv>());
    func(make_shared<hd_pub>());
    func(make_shared<hd_to_addr>());
    func(make_shared<hd_to_ec>());
    func(make_shared<hd_to_pub>());
    func(make_shared<hd_to_wif>());
    func(make_shared<help>());
    func(make_shared<history>());
    func(make_shared<initchain>());
    func(make_shared<mnemonic_decode>());
    func(make_shared<mnemonic_encode>());
    func(make_shared<monitor>());
    func(make_shared<mpk>());
    func(make_shared<newseed>());
    func(make_shared<qrcode>());
    func(make_shared<ripemd160>());
    func(make_shared<satoshi>());
    func(make_shared<seed>());
    func(make_shared<sendtx_node>());
    func(make_shared<sendtx_obelisk>());
    func(make_shared<sha160>());
    func(make_shared<sha256>());
    func(make_shared<sha512>());
    func(make_shared<signtx>());
    func(make_shared<stealth_addr>());
    func(make_shared<unwrap>());
    func(make_shared<wallet>());
    func(make_shared<watchtx>());
    func(make_shared<wif_to_ec>());
    func(make_shared<wif_to_pub>());
    func(make_shared<wrap>());

    return true;
}

shared_ptr<command> find(const string& symbol)
{
    if (symbol == addr_decode::symbol())
        return make_shared<addr_decode>();
    if (symbol == addr_embed::symbol())
        return make_shared<addr_embed>();
    if (symbol == addr_encode::symbol())
        return make_shared<addr_encode>();
    if (symbol == addr_validate::symbol())
        return make_shared<addr_validate>();
    if (symbol == balance::symbol())
        return make_shared<balance>();
    if (symbol == base58_decode::symbol())
        return make_shared<base58_decode>();
    if (symbol == base58_encode::symbol())
        return make_shared<base58_encode>();
    if (symbol == base58check_decode::symbol())
        return make_shared<base58check_decode>();
    if (symbol == base58check_encode::symbol())
        return make_shared<base58check_encode>();
    if (symbol == bci_fetch_last_height::symbol())
        return make_shared<bci_fetch_last_height>();
    if (symbol == bci_history::symbol())
        return make_shared<bci_history>();
    if (symbol == bci_send_transaction::symbol())
        return make_shared<bci_send_transaction>();
    if (symbol == be_fetch_transaction::symbol())
        return make_shared<be_fetch_transaction>();
    if (symbol == bitcoin160::symbol())
        return make_shared<bitcoin160>();
    if (symbol == bitcoin256::symbol())
        return make_shared<bitcoin256>();
    if (symbol == btc::symbol())
        return make_shared<btc>();
    if (symbol == ec_add::symbol())
        return make_shared<ec_add>();
    if (symbol == ec_add_secrets::symbol())
        return make_shared<ec_add_secrets>();
    if (symbol == ec_lock::symbol())
        return make_shared<ec_lock>();
    if (symbol == ec_multiply::symbol())
        return make_shared<ec_multiply>();
    if (symbol == ec_multiply_secrets::symbol())
        return make_shared<ec_multiply_secrets>();
    if (symbol == ec_new::symbol())
        return make_shared<ec_new>();
    if (symbol == ec_to_addr::symbol())
        return make_shared<ec_to_addr>();
    if (symbol == ec_to_pub::symbol())
        return make_shared<ec_to_pub>();
    if (symbol == ec_to_wif::symbol())
        return make_shared<ec_to_wif>();
    if (symbol == ec_unlock::symbol())
        return make_shared<ec_unlock>();
    if (symbol == fetch_header::symbol())
        return make_shared<fetch_header>();
    if (symbol == fetch_last_height::symbol())
        return make_shared<fetch_last_height>();
    if (symbol == fetch_public_key::symbol())
        return make_shared<fetch_public_key>();
    if (symbol == fetch_stealth::symbol())
        return make_shared<fetch_stealth>();
    if (symbol == fetch_transaction::symbol())
        return make_shared<fetch_transaction>();
    if (symbol == fetch_transaction_index::symbol())
        return make_shared<fetch_transaction_index>();
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
    if (symbol == hd_priv::symbol())
        return make_shared<hd_priv>();
    if (symbol == hd_pub::symbol())
        return make_shared<hd_pub>();
    if (symbol == hd_to_addr::symbol())
        return make_shared<hd_to_addr>();
    if (symbol == hd_to_ec::symbol())
        return make_shared<hd_to_ec>();
    if (symbol == hd_to_pub::symbol())
        return make_shared<hd_to_pub>();
    if (symbol == hd_to_wif::symbol())
        return make_shared<hd_to_wif>();
    if (symbol == help::symbol())
        return make_shared<help>();
    if (symbol == history::symbol())
        return make_shared<history>();
    if (symbol == initchain::symbol())
        return make_shared<initchain>();
    if (symbol == mnemonic_decode::symbol())
        return make_shared<mnemonic_decode>();
    if (symbol == mnemonic_encode::symbol())
        return make_shared<mnemonic_encode>();
    if (symbol == monitor::symbol())
        return make_shared<monitor>();
    if (symbol == mpk::symbol())
        return make_shared<mpk>();
    if (symbol == newseed::symbol())
        return make_shared<newseed>();
    if (symbol == qrcode::symbol())
        return make_shared<qrcode>();
    if (symbol == ripemd160::symbol())
        return make_shared<ripemd160>();
    if (symbol == satoshi::symbol())
        return make_shared<satoshi>();
    if (symbol == seed::symbol())
        return make_shared<seed>();
    if (symbol == sendtx_node::symbol())
        return make_shared<sendtx_node>();
    if (symbol == sendtx_obelisk::symbol())
        return make_shared<sendtx_obelisk>();
    if (symbol == sha160::symbol())
        return make_shared<sha160>();
    if (symbol == sha256::symbol())
        return make_shared<sha256>();
    if (symbol == sha512::symbol())
        return make_shared<sha512>();
    if (symbol == signtx::symbol())
        return make_shared<signtx>();
    if (symbol == stealth_addr::symbol())
        return make_shared<stealth_addr>();
    if (symbol == unwrap::symbol())
        return make_shared<unwrap>();
    if (symbol == wallet::symbol())
        return make_shared<wallet>();
    if (symbol == watchtx::symbol())
        return make_shared<watchtx>();
    if (symbol == wif_to_ec::symbol())
        return make_shared<wif_to_ec>();
    if (symbol == wif_to_pub::symbol())
        return make_shared<wif_to_pub>();
    if (symbol == wrap::symbol())
        return make_shared<wrap>();

    return nullptr;
}

} // sx
