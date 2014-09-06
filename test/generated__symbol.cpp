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
#include "precompile.hpp"
#include <boost/test/unit_test.hpp>

#include <explorer/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace explorer;
using namespace explorer::commands;

BOOST_AUTO_TEST_SUITE(generated__symbol)

BOOST_AUTO_TEST_CASE(generated__symbol__address_decode__returns_expected_value)
{
    BOOST_REQUIRE(address_decode::symbol() == std::string("address-decode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__address_embed__returns_expected_value)
{
    BOOST_REQUIRE(address_embed::symbol() == std::string("address-embed"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__address_encode__returns_expected_value)
{
    BOOST_REQUIRE(address_encode::symbol() == std::string("address-encode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__address_validate__returns_expected_value)
{
    BOOST_REQUIRE(address_validate::symbol() == std::string("address-validate"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__base58_decode__returns_expected_value)
{
    BOOST_REQUIRE(base58_decode::symbol() == std::string("base58-decode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__base58_encode__returns_expected_value)
{
    BOOST_REQUIRE(base58_encode::symbol() == std::string("base58-encode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__base58check_decode__returns_expected_value)
{
    BOOST_REQUIRE(base58check_decode::symbol() == std::string("base58check-decode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__base58check_encode__returns_expected_value)
{
    BOOST_REQUIRE(base58check_encode::symbol() == std::string("base58check-encode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__bci_fetch_last_height__returns_expected_value)
{
    BOOST_REQUIRE(bci_fetch_last_height::symbol() == std::string("bci-fetch-last-height"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__bci_history__returns_expected_value)
{
    BOOST_REQUIRE(bci_history::symbol() == std::string("bci-history"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__bitcoin160__returns_expected_value)
{
    BOOST_REQUIRE(bitcoin160::symbol() == std::string("bitcoin160"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__bitcoin256__returns_expected_value)
{
    BOOST_REQUIRE(bitcoin256::symbol() == std::string("bitcoin256"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__blke_fetch_transaction__returns_expected_value)
{
    BOOST_REQUIRE(blke_fetch_transaction::symbol() == std::string("blke-fetch-transaction"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__btc_to_satoshi__returns_expected_value)
{
    BOOST_REQUIRE(btc_to_satoshi::symbol() == std::string("btc-to-satoshi"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_add__returns_expected_value)
{
    BOOST_REQUIRE(ec_add::symbol() == std::string("ec-add"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_add_secrets__returns_expected_value)
{
    BOOST_REQUIRE(ec_add_secrets::symbol() == std::string("ec-add-secrets"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_lock__returns_expected_value)
{
    BOOST_REQUIRE(ec_lock::symbol() == std::string("ec-lock"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_multiply__returns_expected_value)
{
    BOOST_REQUIRE(ec_multiply::symbol() == std::string("ec-multiply"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_multiply_secrets__returns_expected_value)
{
    BOOST_REQUIRE(ec_multiply_secrets::symbol() == std::string("ec-multiply-secrets"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_new__returns_expected_value)
{
    BOOST_REQUIRE(ec_new::symbol() == std::string("ec-new"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_to_address__returns_expected_value)
{
    BOOST_REQUIRE(ec_to_address::symbol() == std::string("ec-to-address"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_to_public__returns_expected_value)
{
    BOOST_REQUIRE(ec_to_public::symbol() == std::string("ec-to-public"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_to_wif__returns_expected_value)
{
    BOOST_REQUIRE(ec_to_wif::symbol() == std::string("ec-to-wif"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_unlock__returns_expected_value)
{
    BOOST_REQUIRE(ec_unlock::symbol() == std::string("ec-unlock"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_balance__returns_expected_value)
{
    BOOST_REQUIRE(fetch_balance::symbol() == std::string("fetch-balance"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_confirmations__returns_expected_value)
{
    BOOST_REQUIRE(fetch_confirmations::symbol() == std::string("fetch-confirmations"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_header__returns_expected_value)
{
    BOOST_REQUIRE(fetch_header::symbol() == std::string("fetch-header"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_height__returns_expected_value)
{
    BOOST_REQUIRE(fetch_height::symbol() == std::string("fetch-height"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_history__returns_expected_value)
{
    BOOST_REQUIRE(fetch_history::symbol() == std::string("fetch-history"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_public_key__returns_expected_value)
{
    BOOST_REQUIRE(fetch_public_key::symbol() == std::string("fetch-public-key"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_stealth__returns_expected_value)
{
    BOOST_REQUIRE(fetch_stealth::symbol() == std::string("fetch-stealth"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_tx__returns_expected_value)
{
    BOOST_REQUIRE(fetch_tx::symbol() == std::string("fetch-tx"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_tx_index__returns_expected_value)
{
    BOOST_REQUIRE(fetch_tx_index::symbol() == std::string("fetch-tx-index"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_utxo__returns_expected_value)
{
    BOOST_REQUIRE(fetch_utxo::symbol() == std::string("fetch-utxo"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__genaddr__returns_expected_value)
{
    BOOST_REQUIRE(genaddr::symbol() == std::string("genaddr"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__genpriv__returns_expected_value)
{
    BOOST_REQUIRE(genpriv::symbol() == std::string("genpriv"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__genpub__returns_expected_value)
{
    BOOST_REQUIRE(genpub::symbol() == std::string("genpub"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_new__returns_expected_value)
{
    BOOST_REQUIRE(hd_new::symbol() == std::string("hd-new"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_private__returns_expected_value)
{
    BOOST_REQUIRE(hd_private::symbol() == std::string("hd-private"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_public__returns_expected_value)
{
    BOOST_REQUIRE(hd_public::symbol() == std::string("hd-public"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_to_address__returns_expected_value)
{
    BOOST_REQUIRE(hd_to_address::symbol() == std::string("hd-to-address"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_to_ec__returns_expected_value)
{
    BOOST_REQUIRE(hd_to_ec::symbol() == std::string("hd-to-ec"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_to_public__returns_expected_value)
{
    BOOST_REQUIRE(hd_to_public::symbol() == std::string("hd-to-public"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_to_wif__returns_expected_value)
{
    BOOST_REQUIRE(hd_to_wif::symbol() == std::string("hd-to-wif"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__help__returns_expected_value)
{
    BOOST_REQUIRE(help::symbol() == std::string("help"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__initchain__returns_expected_value)
{
    BOOST_REQUIRE(initchain::symbol() == std::string("initchain"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__input_set__returns_expected_value)
{
    BOOST_REQUIRE(input_set::symbol() == std::string("input-set"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__input_sign__returns_expected_value)
{
    BOOST_REQUIRE(input_sign::symbol() == std::string("input-sign"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__input_validate__returns_expected_value)
{
    BOOST_REQUIRE(input_validate::symbol() == std::string("input-validate"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__mnemonic_decode__returns_expected_value)
{
    BOOST_REQUIRE(mnemonic_decode::symbol() == std::string("mnemonic-decode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__mnemonic_encode__returns_expected_value)
{
    BOOST_REQUIRE(mnemonic_encode::symbol() == std::string("mnemonic-encode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__mpk__returns_expected_value)
{
    BOOST_REQUIRE(mpk::symbol() == std::string("mpk"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__newseed__returns_expected_value)
{
    BOOST_REQUIRE(newseed::symbol() == std::string("newseed"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__qrcode__returns_expected_value)
{
    BOOST_REQUIRE(qrcode::symbol() == std::string("qrcode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ripemd160__returns_expected_value)
{
    BOOST_REQUIRE(ripemd160::symbol() == std::string("ripemd160"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__satoshi_to_btc__returns_expected_value)
{
    BOOST_REQUIRE(satoshi_to_btc::symbol() == std::string("satoshi-to-btc"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__script_decode__returns_expected_value)
{
    BOOST_REQUIRE(script_decode::symbol() == std::string("script-decode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__script_encode__returns_expected_value)
{
    BOOST_REQUIRE(script_encode::symbol() == std::string("script-encode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__script_to_address__returns_expected_value)
{
    BOOST_REQUIRE(script_to_address::symbol() == std::string("script-to-address"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__seed__returns_expected_value)
{
    BOOST_REQUIRE(seed::symbol() == std::string("seed"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__send_tx__returns_expected_value)
{
    BOOST_REQUIRE(send_tx::symbol() == std::string("send-tx"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__send_tx_node__returns_expected_value)
{
    BOOST_REQUIRE(send_tx_node::symbol() == std::string("send-tx-node"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__send_tx_p2p__returns_expected_value)
{
    BOOST_REQUIRE(send_tx_p2p::symbol() == std::string("send-tx-p2p"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__sendtx_bci__returns_expected_value)
{
    BOOST_REQUIRE(sendtx_bci::symbol() == std::string("sendtx-bci"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__sha160__returns_expected_value)
{
    BOOST_REQUIRE(sha160::symbol() == std::string("sha160"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__sha256__returns_expected_value)
{
    BOOST_REQUIRE(sha256::symbol() == std::string("sha256"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__sha512__returns_expected_value)
{
    BOOST_REQUIRE(sha512::symbol() == std::string("sha512"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__showblkhead__returns_expected_value)
{
    BOOST_REQUIRE(showblkhead::symbol() == std::string("showblkhead"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_address_decode__returns_expected_value)
{
    BOOST_REQUIRE(stealth_address_decode::symbol() == std::string("stealth-address-decode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_address_encode__returns_expected_value)
{
    BOOST_REQUIRE(stealth_address_encode::symbol() == std::string("stealth-address-encode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_new__returns_expected_value)
{
    BOOST_REQUIRE(stealth_new::symbol() == std::string("stealth-new"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_newkey__returns_expected_value)
{
    BOOST_REQUIRE(stealth_newkey::symbol() == std::string("stealth-newkey"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_shared_secret__returns_expected_value)
{
    BOOST_REQUIRE(stealth_shared_secret::symbol() == std::string("stealth-shared-secret"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_uncover_public__returns_expected_value)
{
    BOOST_REQUIRE(stealth_uncover_public::symbol() == std::string("stealth-uncover-public"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_uncover_secret__returns_expected_value)
{
    BOOST_REQUIRE(stealth_uncover_secret::symbol() == std::string("stealth-uncover-secret"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__tx_decode__returns_expected_value)
{
    BOOST_REQUIRE(tx_decode::symbol() == std::string("tx-decode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__tx_encode__returns_expected_value)
{
    BOOST_REQUIRE(tx_encode::symbol() == std::string("tx-encode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__tx_sign__returns_expected_value)
{
    BOOST_REQUIRE(tx_sign::symbol() == std::string("tx-sign"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__wallet__returns_expected_value)
{
    BOOST_REQUIRE(wallet::symbol() == std::string("wallet"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__watch_stealth__returns_expected_value)
{
    BOOST_REQUIRE(watch_stealth::symbol() == std::string("watch-stealth"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__watch_tx__returns_expected_value)
{
    BOOST_REQUIRE(watch_tx::symbol() == std::string("watch-tx"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__wif_to_ec__returns_expected_value)
{
    BOOST_REQUIRE(wif_to_ec::symbol() == std::string("wif-to-ec"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__wif_to_public__returns_expected_value)
{
    BOOST_REQUIRE(wif_to_public::symbol() == std::string("wif-to-public"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__wrap_decode__returns_expected_value)
{
    BOOST_REQUIRE(wrap_decode::symbol() == std::string("wrap-decode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__wrap_encode__returns_expected_value)
{
    BOOST_REQUIRE(wrap_encode::symbol() == std::string("wrap-encode"));
}

BOOST_AUTO_TEST_SUITE_END()
