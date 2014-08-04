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
#include <boost/test/unit_test.hpp>
#include <sx/sx.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace sx;
using namespace sx::extension;

BOOST_AUTO_TEST_SUITE(generated__symbol)

BOOST_AUTO_TEST_CASE(generated__symbol__addr_decode__returns_expected_value)
{
    BOOST_REQUIRE(addr_decode::symbol() == std::string("addr-decode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__addr_embed__returns_expected_value)
{
    BOOST_REQUIRE(addr_embed::symbol() == std::string("addr-embed"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__addr_encode__returns_expected_value)
{
    BOOST_REQUIRE(addr_encode::symbol() == std::string("addr-encode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__addr_validate__returns_expected_value)
{
    BOOST_REQUIRE(addr_validate::symbol() == std::string("addr-validate"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__balance__returns_expected_value)
{
    BOOST_REQUIRE(balance::symbol() == std::string("balance"));
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

BOOST_AUTO_TEST_CASE(generated__symbol__bci_send_transaction__returns_expected_value)
{
    BOOST_REQUIRE(bci_send_transaction::symbol() == std::string("bci-send-transaction"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__be_fetch_transaction__returns_expected_value)
{
    BOOST_REQUIRE(be_fetch_transaction::symbol() == std::string("be-fetch-transaction"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__bitcoin160__returns_expected_value)
{
    BOOST_REQUIRE(bitcoin160::symbol() == std::string("bitcoin160"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__bitcoin256__returns_expected_value)
{
    BOOST_REQUIRE(bitcoin256::symbol() == std::string("bitcoin256"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__btc__returns_expected_value)
{
    BOOST_REQUIRE(btc::symbol() == std::string("btc"));
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

BOOST_AUTO_TEST_CASE(generated__symbol__ec_to_addr__returns_expected_value)
{
    BOOST_REQUIRE(ec_to_addr::symbol() == std::string("ec-to-addr"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_to_pub__returns_expected_value)
{
    BOOST_REQUIRE(ec_to_pub::symbol() == std::string("ec-to-pub"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_to_wif__returns_expected_value)
{
    BOOST_REQUIRE(ec_to_wif::symbol() == std::string("ec-to-wif"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_unlock__returns_expected_value)
{
    BOOST_REQUIRE(ec_unlock::symbol() == std::string("ec-unlock"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_header__returns_expected_value)
{
    BOOST_REQUIRE(fetch_header::symbol() == std::string("fetch-header"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_last_height__returns_expected_value)
{
    BOOST_REQUIRE(fetch_last_height::symbol() == std::string("fetch-last-height"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_public_key__returns_expected_value)
{
    BOOST_REQUIRE(fetch_public_key::symbol() == std::string("fetch-public-key"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_stealth__returns_expected_value)
{
    BOOST_REQUIRE(fetch_stealth::symbol() == std::string("fetch-stealth"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_transaction__returns_expected_value)
{
    BOOST_REQUIRE(fetch_transaction::symbol() == std::string("fetch-transaction"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_transaction_index__returns_expected_value)
{
    BOOST_REQUIRE(fetch_transaction_index::symbol() == std::string("fetch-transaction-index"));
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

BOOST_AUTO_TEST_CASE(generated__symbol__hd_priv__returns_expected_value)
{
    BOOST_REQUIRE(hd_priv::symbol() == std::string("hd-priv"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_pub__returns_expected_value)
{
    BOOST_REQUIRE(hd_pub::symbol() == std::string("hd-pub"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_to_addr__returns_expected_value)
{
    BOOST_REQUIRE(hd_to_addr::symbol() == std::string("hd-to-addr"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_to_ec__returns_expected_value)
{
    BOOST_REQUIRE(hd_to_ec::symbol() == std::string("hd-to-ec"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_to_pub__returns_expected_value)
{
    BOOST_REQUIRE(hd_to_pub::symbol() == std::string("hd-to-pub"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_to_wif__returns_expected_value)
{
    BOOST_REQUIRE(hd_to_wif::symbol() == std::string("hd-to-wif"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__help__returns_expected_value)
{
    BOOST_REQUIRE(help::symbol() == std::string("help"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__history__returns_expected_value)
{
    BOOST_REQUIRE(history::symbol() == std::string("history"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__initchain__returns_expected_value)
{
    BOOST_REQUIRE(initchain::symbol() == std::string("initchain"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__mnemonic_decode__returns_expected_value)
{
    BOOST_REQUIRE(mnemonic_decode::symbol() == std::string("mnemonic-decode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__mnemonic_encode__returns_expected_value)
{
    BOOST_REQUIRE(mnemonic_encode::symbol() == std::string("mnemonic-encode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__monitor__returns_expected_value)
{
    BOOST_REQUIRE(monitor::symbol() == std::string("monitor"));
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

BOOST_AUTO_TEST_CASE(generated__symbol__rawscript__returns_expected_value)
{
    BOOST_REQUIRE(rawscript::symbol() == std::string("rawscript"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__ripemd160__returns_expected_value)
{
    BOOST_REQUIRE(ripemd160::symbol() == std::string("ripemd160"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__satoshi__returns_expected_value)
{
    BOOST_REQUIRE(satoshi::symbol() == std::string("satoshi"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__scripthash__returns_expected_value)
{
    BOOST_REQUIRE(scripthash::symbol() == std::string("scripthash"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__seed__returns_expected_value)
{
    BOOST_REQUIRE(seed::symbol() == std::string("seed"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__sendtx_node__returns_expected_value)
{
    BOOST_REQUIRE(sendtx_node::symbol() == std::string("sendtx-node"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__sendtx_obelisk__returns_expected_value)
{
    BOOST_REQUIRE(sendtx_obelisk::symbol() == std::string("sendtx-obelisk"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__sendtx_p2p__returns_expected_value)
{
    BOOST_REQUIRE(sendtx_p2p::symbol() == std::string("sendtx-p2p"));
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

BOOST_AUTO_TEST_CASE(generated__symbol__showscript__returns_expected_value)
{
    BOOST_REQUIRE(showscript::symbol() == std::string("showscript"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__signtx__returns_expected_value)
{
    BOOST_REQUIRE(signtx::symbol() == std::string("signtx"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_addr__returns_expected_value)
{
    BOOST_REQUIRE(stealth_addr::symbol() == std::string("stealth-addr"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__unwrap__returns_expected_value)
{
    BOOST_REQUIRE(unwrap::symbol() == std::string("unwrap"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__validtx__returns_expected_value)
{
    BOOST_REQUIRE(validtx::symbol() == std::string("validtx"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__wallet__returns_expected_value)
{
    BOOST_REQUIRE(wallet::symbol() == std::string("wallet"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__watchtx__returns_expected_value)
{
    BOOST_REQUIRE(watchtx::symbol() == std::string("watchtx"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__wif_to_ec__returns_expected_value)
{
    BOOST_REQUIRE(wif_to_ec::symbol() == std::string("wif-to-ec"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__wif_to_pub__returns_expected_value)
{
    BOOST_REQUIRE(wif_to_pub::symbol() == std::string("wif-to-pub"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__wrap__returns_expected_value)
{
    BOOST_REQUIRE(wrap::symbol() == std::string("wrap"));
}

BOOST_AUTO_TEST_SUITE_END()
