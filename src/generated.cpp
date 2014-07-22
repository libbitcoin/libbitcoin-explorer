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
    func(make_shared<addr>());
    func(make_shared<addr_decode>());
    func(make_shared<addr_encode>());
    func(make_shared<balance>());
    func(make_shared<base58_decode>());
    func(make_shared<base58_encode>());
    func(make_shared<base58check_decode>());
    func(make_shared<base58check_encode>());
    func(make_shared<bci_fetch_last_height>());
    func(make_shared<bci_history>());
    func(make_shared<bci_send_transaction>());
    func(make_shared<be_fetch_transaction>());
    func(make_shared<brainwallet>());
    func(make_shared<btc>());
    func(make_shared<ec_add>());
    func(make_shared<ec_add_secrets>());
    func(make_shared<ec_multiply>());
    func(make_shared<ec_multiply_secrets>());
    func(make_shared<embed_addr>());
    func(make_shared<fetch_header_hash>());
    func(make_shared<fetch_header_height>());
    func(make_shared<fetch_last_height>());
    func(make_shared<fetch_stealth>());
    func(make_shared<fetch_transaction>());
    func(make_shared<fetch_transaction_index>());
    func(make_shared<genaddr>());
    func(make_shared<genpriv>());
    func(make_shared<genpub>());
    func(make_shared<get_pubkey>());
    func(make_shared<get_utxo>());
    func(make_shared<hd_priv>());
    func(make_shared<hd_pub>());
    func(make_shared<hd_seed>());
    func(make_shared<hd_to_address>());
    func(make_shared<hd_to_wif>());
    func(make_shared<help>());
    func(make_shared<history>());
    func(make_shared<qrcode>());
    func(make_shared<satoshi>());
    func(make_shared<stealth_addr>());
    func(make_shared<unwrap>());
    func(make_shared<watchtx>());
    func(make_shared<wrap>());

    return true;
}

shared_ptr<command> find(const string& symbol)
{
    if (symbol == addr::symbol())
        return make_shared<addr>();
    if (symbol == addr_decode::symbol())
        return make_shared<addr_decode>();
    if (symbol == addr_encode::symbol())
        return make_shared<addr_encode>();
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
    if (symbol == brainwallet::symbol())
        return make_shared<brainwallet>();
    if (symbol == btc::symbol())
        return make_shared<btc>();
    if (symbol == ec_add::symbol())
        return make_shared<ec_add>();
    if (symbol == ec_add_secrets::symbol())
        return make_shared<ec_add_secrets>();
    if (symbol == ec_multiply::symbol())
        return make_shared<ec_multiply>();
    if (symbol == ec_multiply_secrets::symbol())
        return make_shared<ec_multiply_secrets>();
    if (symbol == embed_addr::symbol())
        return make_shared<embed_addr>();
    if (symbol == fetch_header_hash::symbol())
        return make_shared<fetch_header_hash>();
    if (symbol == fetch_header_height::symbol())
        return make_shared<fetch_header_height>();
    if (symbol == fetch_last_height::symbol())
        return make_shared<fetch_last_height>();
    if (symbol == fetch_stealth::symbol())
        return make_shared<fetch_stealth>();
    if (symbol == fetch_transaction::symbol())
        return make_shared<fetch_transaction>();
    if (symbol == fetch_transaction_index::symbol())
        return make_shared<fetch_transaction_index>();
    if (symbol == genaddr::symbol())
        return make_shared<genaddr>();
    if (symbol == genpriv::symbol())
        return make_shared<genpriv>();
    if (symbol == genpub::symbol())
        return make_shared<genpub>();
    if (symbol == get_pubkey::symbol())
        return make_shared<get_pubkey>();
    if (symbol == get_utxo::symbol())
        return make_shared<get_utxo>();
    if (symbol == hd_priv::symbol())
        return make_shared<hd_priv>();
    if (symbol == hd_pub::symbol())
        return make_shared<hd_pub>();
    if (symbol == hd_seed::symbol())
        return make_shared<hd_seed>();
    if (symbol == hd_to_address::symbol())
        return make_shared<hd_to_address>();
    if (symbol == hd_to_wif::symbol())
        return make_shared<hd_to_wif>();
    if (symbol == help::symbol())
        return make_shared<help>();
    if (symbol == history::symbol())
        return make_shared<history>();
    if (symbol == qrcode::symbol())
        return make_shared<qrcode>();
    if (symbol == satoshi::symbol())
        return make_shared<satoshi>();
    if (symbol == stealth_addr::symbol())
        return make_shared<stealth_addr>();
    if (symbol == unwrap::symbol())
        return make_shared<unwrap>();
    if (symbol == watchtx::symbol())
        return make_shared<watchtx>();
    if (symbol == wrap::symbol())
        return make_shared<wrap>();

    return nullptr;
}

} // sx
