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
#include <vector>
#include <sx/command.hpp>
#include <sx/generated.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace po;
using namespace std;
using namespace boost::filesystem;
    
namespace sx {
using namespace extension;

bool broadcast(const function<void(shared_ptr<command>)> func)
{
    func(make_shared<addr>());
    func(make_shared<balance>());
    func(make_shared<base58_decode>());
    func(make_shared<base58_encode>());
    func(make_shared<base58check_decode>());
    func(make_shared<base58check_encode>());
    func(make_shared<bci_fetch_last_height>());
    func(make_shared<bci_history>());
    func(make_shared<blke_fetch_transaction>());
    func(make_shared<brainwallet>());
    func(make_shared<btc>());
    func(make_shared<decode_addr>());
    func(make_shared<ec_add>());
    func(make_shared<ec_add_secrets>());
    func(make_shared<ec_multiply>());
    func(make_shared<ec_multiply_secrets>());
    func(make_shared<encode_addr>());
    func(make_shared<help>());
    func(make_shared<satoshi>());
    func(make_shared<stealth_addr>());
    func(make_shared<unwrap>());
    func(make_shared<wrap>());

    return true;
}

shared_ptr<command> find(const string& symbol)
{
    if (symbol == addr::symbol())
        return make_shared<addr>();
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
    if (symbol == blke_fetch_transaction::symbol())
        return make_shared<blke_fetch_transaction>();
    if (symbol == brainwallet::symbol())
        return make_shared<brainwallet>();
    if (symbol == btc::symbol())
        return make_shared<btc>();
    if (symbol == decode_addr::symbol())
        return make_shared<decode_addr>();
    if (symbol == ec_add::symbol())
        return make_shared<ec_add>();
    if (symbol == ec_add_secrets::symbol())
        return make_shared<ec_add_secrets>();
    if (symbol == ec_multiply::symbol())
        return make_shared<ec_multiply>();
    if (symbol == ec_multiply_secrets::symbol())
        return make_shared<ec_multiply_secrets>();
    if (symbol == encode_addr::symbol())
        return make_shared<encode_addr>();
    if (symbol == help::symbol())
        return make_shared<help>();
    if (symbol == satoshi::symbol())
        return make_shared<satoshi>();
    if (symbol == stealth_addr::symbol())
        return make_shared<stealth_addr>();
    if (symbol == unwrap::symbol())
        return make_shared<unwrap>();
    if (symbol == wrap::symbol())
        return make_shared<wrap>();

    return nullptr;
}

} // sx
