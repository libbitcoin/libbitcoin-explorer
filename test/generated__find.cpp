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
// #include "precompile.hpp"
#include <boost/test/unit_test.hpp>

#include <bitcoin/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace bc::explorer;
using namespace bc::explorer::commands;

BOOST_AUTO_TEST_SUITE(generated)
BOOST_AUTO_TEST_SUITE(generated__find)

BOOST_AUTO_TEST_CASE(generated__find__address_decode__returns_object)
{
    BOOST_REQUIRE(find(address_decode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__address_embed__returns_object)
{
    BOOST_REQUIRE(find(address_embed::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__address_encode__returns_object)
{
    BOOST_REQUIRE(find(address_encode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__address_validate__returns_object)
{
    BOOST_REQUIRE(find(address_validate::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base16_decode__returns_object)
{
    BOOST_REQUIRE(find(base16_decode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base16_encode__returns_object)
{
    BOOST_REQUIRE(find(base16_encode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base58_decode__returns_object)
{
    BOOST_REQUIRE(find(base58_decode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base58_encode__returns_object)
{
    BOOST_REQUIRE(find(base58_encode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base58check_decode__returns_object)
{
    BOOST_REQUIRE(find(base58check_decode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base58check_encode__returns_object)
{
    BOOST_REQUIRE(find(base58check_encode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__bci_fetch_last_height__returns_object)
{
    BOOST_REQUIRE(find(bci_fetch_last_height::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__bci_history__returns_object)
{
    BOOST_REQUIRE(find(bci_history::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__bitcoin160__returns_object)
{
    BOOST_REQUIRE(find(bitcoin160::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__bitcoin256__returns_object)
{
    BOOST_REQUIRE(find(bitcoin256::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__blke_fetch_transaction__returns_object)
{
    BOOST_REQUIRE(find(blke_fetch_transaction::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__btc_to_satoshi__returns_object)
{
    BOOST_REQUIRE(find(btc_to_satoshi::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_add__returns_object)
{
    BOOST_REQUIRE(find(ec_add::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_add_secrets__returns_object)
{
    BOOST_REQUIRE(find(ec_add_secrets::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_lock__returns_object)
{
    BOOST_REQUIRE(find(ec_lock::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_multiply__returns_object)
{
    BOOST_REQUIRE(find(ec_multiply::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_multiply_secrets__returns_object)
{
    BOOST_REQUIRE(find(ec_multiply_secrets::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_new__returns_object)
{
    BOOST_REQUIRE(find(ec_new::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_to_address__returns_object)
{
    BOOST_REQUIRE(find(ec_to_address::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_to_public__returns_object)
{
    BOOST_REQUIRE(find(ec_to_public::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_to_wif__returns_object)
{
    BOOST_REQUIRE(find(ec_to_wif::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_unlock__returns_object)
{
    BOOST_REQUIRE(find(ec_unlock::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_balance__returns_object)
{
    BOOST_REQUIRE(find(fetch_balance::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_header__returns_object)
{
    BOOST_REQUIRE(find(fetch_header::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_height__returns_object)
{
    BOOST_REQUIRE(find(fetch_height::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_history__returns_object)
{
    BOOST_REQUIRE(find(fetch_history::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_public_key__returns_object)
{
    BOOST_REQUIRE(find(fetch_public_key::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_stealth__returns_object)
{
    BOOST_REQUIRE(find(fetch_stealth::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_tx__returns_object)
{
    BOOST_REQUIRE(find(fetch_tx::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_tx_index__returns_object)
{
    BOOST_REQUIRE(find(fetch_tx_index::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_utxo__returns_object)
{
    BOOST_REQUIRE(find(fetch_utxo::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__genaddr__returns_object)
{
    BOOST_REQUIRE(find(genaddr::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__genpriv__returns_object)
{
    BOOST_REQUIRE(find(genpriv::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__genpub__returns_object)
{
    BOOST_REQUIRE(find(genpub::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_new__returns_object)
{
    BOOST_REQUIRE(find(hd_new::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_private__returns_object)
{
    BOOST_REQUIRE(find(hd_private::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_public__returns_object)
{
    BOOST_REQUIRE(find(hd_public::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_to_address__returns_object)
{
    BOOST_REQUIRE(find(hd_to_address::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_to_ec__returns_object)
{
    BOOST_REQUIRE(find(hd_to_ec::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_to_public__returns_object)
{
    BOOST_REQUIRE(find(hd_to_public::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_to_wif__returns_object)
{
    BOOST_REQUIRE(find(hd_to_wif::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__help__returns_object)
{
    BOOST_REQUIRE(find(help::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__initchain__returns_object)
{
    BOOST_REQUIRE(find(initchain::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__input_set__returns_object)
{
    BOOST_REQUIRE(find(input_set::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__input_sign__returns_object)
{
    BOOST_REQUIRE(find(input_sign::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__input_validate__returns_object)
{
    BOOST_REQUIRE(find(input_validate::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__mnemonic_decode__returns_object)
{
    BOOST_REQUIRE(find(mnemonic_decode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__mnemonic_encode__returns_object)
{
    BOOST_REQUIRE(find(mnemonic_encode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__mpk__returns_object)
{
    BOOST_REQUIRE(find(mpk::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__newseed__returns_object)
{
    BOOST_REQUIRE(find(newseed::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__qrcode__returns_object)
{
    BOOST_REQUIRE(find(qrcode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ripemd160__returns_object)
{
    BOOST_REQUIRE(find(ripemd160::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__satoshi_to_btc__returns_object)
{
    BOOST_REQUIRE(find(satoshi_to_btc::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__script_decode__returns_object)
{
    BOOST_REQUIRE(find(script_decode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__script_encode__returns_object)
{
    BOOST_REQUIRE(find(script_encode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__script_to_address__returns_object)
{
    BOOST_REQUIRE(find(script_to_address::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__seed__returns_object)
{
    BOOST_REQUIRE(find(seed::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__send_tx__returns_object)
{
    BOOST_REQUIRE(find(send_tx::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__send_tx_node__returns_object)
{
    BOOST_REQUIRE(find(send_tx_node::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__send_tx_p2p__returns_object)
{
    BOOST_REQUIRE(find(send_tx_p2p::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__sendtx_bci__returns_object)
{
    BOOST_REQUIRE(find(sendtx_bci::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__sha160__returns_object)
{
    BOOST_REQUIRE(find(sha160::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__sha256__returns_object)
{
    BOOST_REQUIRE(find(sha256::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__sha512__returns_object)
{
    BOOST_REQUIRE(find(sha512::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__showblkhead__returns_object)
{
    BOOST_REQUIRE(find(showblkhead::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_address_decode__returns_object)
{
    BOOST_REQUIRE(find(stealth_address_decode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_address_encode__returns_object)
{
    BOOST_REQUIRE(find(stealth_address_encode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_new__returns_object)
{
    BOOST_REQUIRE(find(stealth_new::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_newkey__returns_object)
{
    BOOST_REQUIRE(find(stealth_newkey::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_shared_secret__returns_object)
{
    BOOST_REQUIRE(find(stealth_shared_secret::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_uncover_public__returns_object)
{
    BOOST_REQUIRE(find(stealth_uncover_public::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_uncover_secret__returns_object)
{
    BOOST_REQUIRE(find(stealth_uncover_secret::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__tx_decode__returns_object)
{
    BOOST_REQUIRE(find(tx_decode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__tx_encode__returns_object)
{
    BOOST_REQUIRE(find(tx_encode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__tx_sign__returns_object)
{
    BOOST_REQUIRE(find(tx_sign::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__validate_tx__returns_object)
{
    BOOST_REQUIRE(find(validate_tx::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__wallet__returns_object)
{
    BOOST_REQUIRE(find(wallet::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__watch_address__returns_object)
{
    BOOST_REQUIRE(find(watch_address::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__watch_tx__returns_object)
{
    BOOST_REQUIRE(find(watch_tx::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__wif_to_ec__returns_object)
{
    BOOST_REQUIRE(find(wif_to_ec::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__wif_to_public__returns_object)
{
    BOOST_REQUIRE(find(wif_to_public::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__wrap_decode__returns_object)
{
    BOOST_REQUIRE(find(wrap_decode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__wrap_encode__returns_object)
{
    BOOST_REQUIRE(find(wrap_encode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
