/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <boost/test/unit_test.hpp>

#include <bitcoin/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace bc::explorer;
using namespace bc::explorer::commands;

BOOST_AUTO_TEST_SUITE(generated)
BOOST_AUTO_TEST_SUITE(generated__symbol)

BOOST_AUTO_TEST_CASE(generated__symbol__address_decode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(address_decode::symbol(), "address-decode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__address_embed__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(address_embed::symbol(), "address-embed");
}

BOOST_AUTO_TEST_CASE(generated__symbol__address_encode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(address_encode::symbol(), "address-encode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__base16_decode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(base16_decode::symbol(), "base16-decode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__base16_encode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(base16_encode::symbol(), "base16-encode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__base58_decode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(base58_decode::symbol(), "base58-decode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__base58_encode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(base58_encode::symbol(), "base58-encode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__base58check_decode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(base58check_decode::symbol(), "base58check-decode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__base58check_encode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(base58check_encode::symbol(), "base58check-encode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__base64_decode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(base64_decode::symbol(), "base64-decode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__base64_encode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(base64_encode::symbol(), "base64-encode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__bitcoin160__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(bitcoin160::symbol(), "bitcoin160");
}

BOOST_AUTO_TEST_CASE(generated__symbol__bitcoin256__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(bitcoin256::symbol(), "bitcoin256");
}

BOOST_AUTO_TEST_CASE(generated__symbol__btc_to_satoshi__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(btc_to_satoshi::symbol(), "btc-to-satoshi");
}

BOOST_AUTO_TEST_CASE(generated__symbol__cert_new__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(cert_new::symbol(), "cert-new");
}

BOOST_AUTO_TEST_CASE(generated__symbol__cert_public__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(cert_public::symbol(), "cert-public");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_add__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ec_add::symbol(), "ec-add");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_add_secrets__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ec_add_secrets::symbol(), "ec-add-secrets");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_multiply__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ec_multiply::symbol(), "ec-multiply");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_multiply_secrets__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ec_multiply_secrets::symbol(), "ec-multiply-secrets");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_new__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ec_new::symbol(), "ec-new");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_to_address__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ec_to_address::symbol(), "ec-to-address");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_to_ek__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ec_to_ek::symbol(), "ec-to-ek");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_to_public__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ec_to_public::symbol(), "ec-to-public");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ec_to_wif__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ec_to_wif::symbol(), "ec-to-wif");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ek_address__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ek_address::symbol(), "ek-address");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ek_new__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ek_new::symbol(), "ek-new");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ek_public__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ek_public::symbol(), "ek-public");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ek_public_to_address__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ek_public_to_address::symbol(), "ek-public-to-address");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ek_public_to_ec__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ek_public_to_ec::symbol(), "ek-public-to-ec");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ek_to_address__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ek_to_address::symbol(), "ek-to-address");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ek_to_ec__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ek_to_ec::symbol(), "ek-to-ec");
}

BOOST_AUTO_TEST_CASE(generated__symbol__electrum_new__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(electrum_new::symbol(), "electrum-new");
}

BOOST_AUTO_TEST_CASE(generated__symbol__electrum_to_seed__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(electrum_to_seed::symbol(), "electrum-to-seed");
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_balance__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(fetch_balance::symbol(), "fetch-balance");
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_header__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(fetch_header::symbol(), "fetch-header");
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_height__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(fetch_height::symbol(), "fetch-height");
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_history__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(fetch_history::symbol(), "fetch-history");
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_public_key__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(fetch_public_key::symbol(), "fetch-public-key");
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_stealth__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(fetch_stealth::symbol(), "fetch-stealth");
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_tx__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(fetch_tx::symbol(), "fetch-tx");
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_tx_index__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(fetch_tx_index::symbol(), "fetch-tx-index");
}

BOOST_AUTO_TEST_CASE(generated__symbol__fetch_utxo__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(fetch_utxo::symbol(), "fetch-utxo");
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_new__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(hd_new::symbol(), "hd-new");
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_private__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(hd_private::symbol(), "hd-private");
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_public__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(hd_public::symbol(), "hd-public");
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_to_address__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(hd_to_address::symbol(), "hd-to-address");
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_to_ec__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(hd_to_ec::symbol(), "hd-to-ec");
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_to_public__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(hd_to_public::symbol(), "hd-to-public");
}

BOOST_AUTO_TEST_CASE(generated__symbol__hd_to_wif__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(hd_to_wif::symbol(), "hd-to-wif");
}

BOOST_AUTO_TEST_CASE(generated__symbol__help__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(help::symbol(), "help");
}

BOOST_AUTO_TEST_CASE(generated__symbol__input_set__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(input_set::symbol(), "input-set");
}

BOOST_AUTO_TEST_CASE(generated__symbol__input_sign__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(input_sign::symbol(), "input-sign");
}

BOOST_AUTO_TEST_CASE(generated__symbol__input_validate__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(input_validate::symbol(), "input-validate");
}

BOOST_AUTO_TEST_CASE(generated__symbol__message_sign__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(message_sign::symbol(), "message-sign");
}

BOOST_AUTO_TEST_CASE(generated__symbol__message_validate__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(message_validate::symbol(), "message-validate");
}

BOOST_AUTO_TEST_CASE(generated__symbol__mnemonic_decode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(mnemonic_decode::symbol(), "mnemonic-decode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__mnemonic_encode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(mnemonic_encode::symbol(), "mnemonic-encode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__mnemonic_new__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(mnemonic_new::symbol(), "mnemonic-new");
}

BOOST_AUTO_TEST_CASE(generated__symbol__mnemonic_to_seed__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(mnemonic_to_seed::symbol(), "mnemonic-to-seed");
}

BOOST_AUTO_TEST_CASE(generated__symbol__qrcode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(qrcode::symbol(), "qrcode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__ripemd160__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(ripemd160::symbol(), "ripemd160");
}

BOOST_AUTO_TEST_CASE(generated__symbol__satoshi_to_btc__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(satoshi_to_btc::symbol(), "satoshi-to-btc");
}

BOOST_AUTO_TEST_CASE(generated__symbol__script_decode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(script_decode::symbol(), "script-decode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__script_encode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(script_encode::symbol(), "script-encode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__script_to_address__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(script_to_address::symbol(), "script-to-address");
}

BOOST_AUTO_TEST_CASE(generated__symbol__seed__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(seed::symbol(), "seed");
}

BOOST_AUTO_TEST_CASE(generated__symbol__send_tx__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(send_tx::symbol(), "send-tx");
}

BOOST_AUTO_TEST_CASE(generated__symbol__send_tx_node__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(send_tx_node::symbol(), "send-tx-node");
}

BOOST_AUTO_TEST_CASE(generated__symbol__send_tx_p2p__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(send_tx_p2p::symbol(), "send-tx-p2p");
}

BOOST_AUTO_TEST_CASE(generated__symbol__settings__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(settings::symbol(), "settings");
}

BOOST_AUTO_TEST_CASE(generated__symbol__sha160__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(sha160::symbol(), "sha160");
}

BOOST_AUTO_TEST_CASE(generated__symbol__sha256__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(sha256::symbol(), "sha256");
}

BOOST_AUTO_TEST_CASE(generated__symbol__sha512__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(sha512::symbol(), "sha512");
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_decode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(stealth_decode::symbol(), "stealth-decode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_encode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(stealth_encode::symbol(), "stealth-encode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_public__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(stealth_public::symbol(), "stealth-public");
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_secret__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(stealth_secret::symbol(), "stealth-secret");
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_shared__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(stealth_shared::symbol(), "stealth-shared");
}

BOOST_AUTO_TEST_CASE(generated__symbol__token_new__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(token_new::symbol(), "token-new");
}

BOOST_AUTO_TEST_CASE(generated__symbol__tx_decode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(tx_decode::symbol(), "tx-decode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__tx_encode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(tx_encode::symbol(), "tx-encode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__tx_sign__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(tx_sign::symbol(), "tx-sign");
}

BOOST_AUTO_TEST_CASE(generated__symbol__uri_decode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(uri_decode::symbol(), "uri-decode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__uri_encode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(uri_encode::symbol(), "uri-encode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__validate_tx__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(validate_tx::symbol(), "validate-tx");
}

BOOST_AUTO_TEST_CASE(generated__symbol__watch_address__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(watch_address::symbol(), "watch-address");
}

BOOST_AUTO_TEST_CASE(generated__symbol__watch_stealth__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(watch_stealth::symbol(), "watch-stealth");
}

BOOST_AUTO_TEST_CASE(generated__symbol__watch_tx__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(watch_tx::symbol(), "watch-tx");
}

BOOST_AUTO_TEST_CASE(generated__symbol__wif_to_ec__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(wif_to_ec::symbol(), "wif-to-ec");
}

BOOST_AUTO_TEST_CASE(generated__symbol__wif_to_public__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(wif_to_public::symbol(), "wif-to-public");
}

BOOST_AUTO_TEST_CASE(generated__symbol__wrap_decode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(wrap_decode::symbol(), "wrap-decode");
}

BOOST_AUTO_TEST_CASE(generated__symbol__wrap_encode__returns_expected_value)
{
    BOOST_REQUIRE_EQUAL(wrap_encode::symbol(), "wrap-encode");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
