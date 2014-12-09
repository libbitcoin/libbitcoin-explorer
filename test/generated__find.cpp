/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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
#include <boost/test/unit_test.hpp>

#include <bitcoin/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace bc::explorer;
using namespace bc::explorer::commands;

BOOST_AUTO_TEST_SUITE(generated)
BOOST_AUTO_TEST_SUITE(generated__find)

BOOST_AUTO_TEST_CASE(generated__find__address_decode__returns_object)
{
    BOOST_REQUIRE(find("address-decode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__address_embed__returns_object)
{
    BOOST_REQUIRE(find("address-embed") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__address_encode__returns_object)
{
    BOOST_REQUIRE(find("address-encode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__address_validate__returns_object)
{
    BOOST_REQUIRE(find("address-validate") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base16_decode__returns_object)
{
    BOOST_REQUIRE(find("base16-decode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base16_encode__returns_object)
{
    BOOST_REQUIRE(find("base16-encode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base58_decode__returns_object)
{
    BOOST_REQUIRE(find("base58-decode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base58_encode__returns_object)
{
    BOOST_REQUIRE(find("base58-encode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base58check_decode__returns_object)
{
    BOOST_REQUIRE(find("base58check-decode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base58check_encode__returns_object)
{
    BOOST_REQUIRE(find("base58check-encode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base64_decode__returns_object)
{
    BOOST_REQUIRE(find("base64-decode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base64_encode__returns_object)
{
    BOOST_REQUIRE(find("base64-encode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__bci_fetch_last_height__returns_object)
{
    BOOST_REQUIRE(find("bci-fetch-last-height") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__bci_history__returns_object)
{
    BOOST_REQUIRE(find("bci-history") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__bitcoin160__returns_object)
{
    BOOST_REQUIRE(find("bitcoin160") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__bitcoin256__returns_object)
{
    BOOST_REQUIRE(find("bitcoin256") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__blke_fetch_transaction__returns_object)
{
    BOOST_REQUIRE(find("blke-fetch-transaction") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__btc_to_satoshi__returns_object)
{
    BOOST_REQUIRE(find("btc-to-satoshi") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_add__returns_object)
{
    BOOST_REQUIRE(find("ec-add") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_add_secrets__returns_object)
{
    BOOST_REQUIRE(find("ec-add-secrets") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_lock__returns_object)
{
    BOOST_REQUIRE(find("ec-lock") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_multiply__returns_object)
{
    BOOST_REQUIRE(find("ec-multiply") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_multiply_secrets__returns_object)
{
    BOOST_REQUIRE(find("ec-multiply-secrets") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_new__returns_object)
{
    BOOST_REQUIRE(find("ec-new") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_to_address__returns_object)
{
    BOOST_REQUIRE(find("ec-to-address") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_to_public__returns_object)
{
    BOOST_REQUIRE(find("ec-to-public") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_to_wif__returns_object)
{
    BOOST_REQUIRE(find("ec-to-wif") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_unlock__returns_object)
{
    BOOST_REQUIRE(find("ec-unlock") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_balance__returns_object)
{
    BOOST_REQUIRE(find("fetch-balance") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_header__returns_object)
{
    BOOST_REQUIRE(find("fetch-header") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_height__returns_object)
{
    BOOST_REQUIRE(find("fetch-height") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_history__returns_object)
{
    BOOST_REQUIRE(find("fetch-history") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_public_key__returns_object)
{
    BOOST_REQUIRE(find("fetch-public-key") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_stealth__returns_object)
{
    BOOST_REQUIRE(find("fetch-stealth") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_tx__returns_object)
{
    BOOST_REQUIRE(find("fetch-tx") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_tx_index__returns_object)
{
    BOOST_REQUIRE(find("fetch-tx-index") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__fetch_utxo__returns_object)
{
    BOOST_REQUIRE(find("fetch-utxo") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__genaddr__returns_object)
{
    BOOST_REQUIRE(find("genaddr") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__genpriv__returns_object)
{
    BOOST_REQUIRE(find("genpriv") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__genpub__returns_object)
{
    BOOST_REQUIRE(find("genpub") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_new__returns_object)
{
    BOOST_REQUIRE(find("hd-new") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_private__returns_object)
{
    BOOST_REQUIRE(find("hd-private") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_public__returns_object)
{
    BOOST_REQUIRE(find("hd-public") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_to_address__returns_object)
{
    BOOST_REQUIRE(find("hd-to-address") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_to_ec__returns_object)
{
    BOOST_REQUIRE(find("hd-to-ec") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_to_public__returns_object)
{
    BOOST_REQUIRE(find("hd-to-public") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__hd_to_wif__returns_object)
{
    BOOST_REQUIRE(find("hd-to-wif") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__help__returns_object)
{
    BOOST_REQUIRE(find("help") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__initchain__returns_object)
{
    BOOST_REQUIRE(find("initchain") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__input_set__returns_object)
{
    BOOST_REQUIRE(find("input-set") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__input_sign__returns_object)
{
    BOOST_REQUIRE(find("input-sign") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__input_validate__returns_object)
{
    BOOST_REQUIRE(find("input-validate") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__message_sign__returns_object)
{
    BOOST_REQUIRE(find("message-sign") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__message_validate__returns_object)
{
    BOOST_REQUIRE(find("message-validate") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__mnemonic_decode__returns_object)
{
    BOOST_REQUIRE(find("mnemonic-decode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__mnemonic_encode__returns_object)
{
    BOOST_REQUIRE(find("mnemonic-encode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__mpk__returns_object)
{
    BOOST_REQUIRE(find("mpk") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__newseed__returns_object)
{
    BOOST_REQUIRE(find("newseed") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__qrcode__returns_object)
{
    BOOST_REQUIRE(find("qrcode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ripemd160__returns_object)
{
    BOOST_REQUIRE(find("ripemd160") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__satoshi_to_btc__returns_object)
{
    BOOST_REQUIRE(find("satoshi-to-btc") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__script_decode__returns_object)
{
    BOOST_REQUIRE(find("script-decode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__script_encode__returns_object)
{
    BOOST_REQUIRE(find("script-encode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__script_to_address__returns_object)
{
    BOOST_REQUIRE(find("script-to-address") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__seed__returns_object)
{
    BOOST_REQUIRE(find("seed") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__send_tx__returns_object)
{
    BOOST_REQUIRE(find("send-tx") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__send_tx_node__returns_object)
{
    BOOST_REQUIRE(find("send-tx-node") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__send_tx_p2p__returns_object)
{
    BOOST_REQUIRE(find("send-tx-p2p") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__sendtx_bci__returns_object)
{
    BOOST_REQUIRE(find("sendtx-bci") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__settings__returns_object)
{
    BOOST_REQUIRE(find("settings") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__sha160__returns_object)
{
    BOOST_REQUIRE(find("sha160") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__sha256__returns_object)
{
    BOOST_REQUIRE(find("sha256") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__sha512__returns_object)
{
    BOOST_REQUIRE(find("sha512") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__showblkhead__returns_object)
{
    BOOST_REQUIRE(find("showblkhead") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_decode__returns_object)
{
    BOOST_REQUIRE(find("stealth-decode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_encode__returns_object)
{
    BOOST_REQUIRE(find("stealth-encode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_initiate__returns_object)
{
    BOOST_REQUIRE(find("stealth-initiate") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_newkey__returns_object)
{
    BOOST_REQUIRE(find("stealth-newkey") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_public__returns_object)
{
    BOOST_REQUIRE(find("stealth-public") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_secret__returns_object)
{
    BOOST_REQUIRE(find("stealth-secret") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_shared__returns_object)
{
    BOOST_REQUIRE(find("stealth-shared") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__tx_decode__returns_object)
{
    BOOST_REQUIRE(find("tx-decode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__tx_encode__returns_object)
{
    BOOST_REQUIRE(find("tx-encode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__tx_sign__returns_object)
{
    BOOST_REQUIRE(find("tx-sign") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__uri_decode__returns_object)
{
    BOOST_REQUIRE(find("uri-decode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__uri_encode__returns_object)
{
    BOOST_REQUIRE(find("uri-encode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__validate_tx__returns_object)
{
    BOOST_REQUIRE(find("validate-tx") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__wallet__returns_object)
{
    BOOST_REQUIRE(find("wallet") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__watch_address__returns_object)
{
    BOOST_REQUIRE(find("watch-address") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__watch_tx__returns_object)
{
    BOOST_REQUIRE(find("watch-tx") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__wif_to_ec__returns_object)
{
    BOOST_REQUIRE(find("wif-to-ec") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__wif_to_public__returns_object)
{
    BOOST_REQUIRE(find("wif-to-public") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__wrap_decode__returns_object)
{
    BOOST_REQUIRE(find("wrap-decode") != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__wrap_encode__returns_object)
{
    BOOST_REQUIRE(find("wrap-encode") != nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
