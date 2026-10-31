/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace bc::explorer;
using namespace bc::explorer::commands;

BC_AUTO_TEST_SUITE(generated)
BC_AUTO_TEST_SUITE(generated__symbol)

BC_AUTO_TEST_CASE(generated__symbol__address_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(address_decode::symbol(), "address-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__address_embed__returns_expected_value)
{
    BC_REQUIRE_EQUAL(address_embed::symbol(), "address-embed");
}

BC_AUTO_TEST_CASE(generated__symbol__address_encode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(address_encode::symbol(), "address-encode");
}

BC_AUTO_TEST_CASE(generated__symbol__address_to_key__returns_expected_value)
{
    BC_REQUIRE_EQUAL(address_to_key::symbol(), "address-to-key");
}

BC_AUTO_TEST_CASE(generated__symbol__base16_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(base16_decode::symbol(), "base16-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__base16_encode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(base16_encode::symbol(), "base16-encode");
}

BC_AUTO_TEST_CASE(generated__symbol__base32_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(base32_decode::symbol(), "base32-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__base32_encode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(base32_encode::symbol(), "base32-encode");
}

BC_AUTO_TEST_CASE(generated__symbol__base58_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(base58_decode::symbol(), "base58-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__base58_encode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(base58_encode::symbol(), "base58-encode");
}

BC_AUTO_TEST_CASE(generated__symbol__base58check_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(base58check_decode::symbol(), "base58check-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__base58check_encode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(base58check_encode::symbol(), "base58check-encode");
}

BC_AUTO_TEST_CASE(generated__symbol__base64_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(base64_decode::symbol(), "base64-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__base64_encode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(base64_encode::symbol(), "base64-encode");
}

BC_AUTO_TEST_CASE(generated__symbol__bech32_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(bech32_decode::symbol(), "bech32-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__bech32_encode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(bech32_encode::symbol(), "bech32-encode");
}

BC_AUTO_TEST_CASE(generated__symbol__bitcoin160__returns_expected_value)
{
    BC_REQUIRE_EQUAL(bitcoin160::symbol(), "bitcoin160");
}

BC_AUTO_TEST_CASE(generated__symbol__bitcoin256__returns_expected_value)
{
    BC_REQUIRE_EQUAL(bitcoin256::symbol(), "bitcoin256");
}

BC_AUTO_TEST_CASE(generated__symbol__broadcast_tx__returns_expected_value)
{
    BC_REQUIRE_EQUAL(broadcast_tx::symbol(), "broadcast-tx");
}

BC_AUTO_TEST_CASE(generated__symbol__btc_to_satoshi__returns_expected_value)
{
    BC_REQUIRE_EQUAL(btc_to_satoshi::symbol(), "btc-to-satoshi");
}

BC_AUTO_TEST_CASE(generated__symbol__cert_new__returns_expected_value)
{
    BC_REQUIRE_EQUAL(cert_new::symbol(), "cert-new");
}

BC_AUTO_TEST_CASE(generated__symbol__cert_public__returns_expected_value)
{
    BC_REQUIRE_EQUAL(cert_public::symbol(), "cert-public");
}

BC_AUTO_TEST_CASE(generated__symbol__checked_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(checked_decode::symbol(), "checked-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__checked_encode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(checked_encode::symbol(), "checked-encode");
}

BC_AUTO_TEST_CASE(generated__symbol__dice_entropy__returns_expected_value)
{
    BC_REQUIRE_EQUAL(dice_entropy::symbol(), "dice-entropy");
}

BC_AUTO_TEST_CASE(generated__symbol__ec_add__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ec_add::symbol(), "ec-add");
}

BC_AUTO_TEST_CASE(generated__symbol__ec_add_secrets__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ec_add_secrets::symbol(), "ec-add-secrets");
}

BC_AUTO_TEST_CASE(generated__symbol__ec_decompress__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ec_decompress::symbol(), "ec-decompress");
}

BC_AUTO_TEST_CASE(generated__symbol__ec_multiply__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ec_multiply::symbol(), "ec-multiply");
}

BC_AUTO_TEST_CASE(generated__symbol__ec_multiply_secrets__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ec_multiply_secrets::symbol(), "ec-multiply-secrets");
}

BC_AUTO_TEST_CASE(generated__symbol__ec_new__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ec_new::symbol(), "ec-new");
}

BC_AUTO_TEST_CASE(generated__symbol__ec_to_address__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ec_to_address::symbol(), "ec-to-address");
}

BC_AUTO_TEST_CASE(generated__symbol__ec_to_ek__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ec_to_ek::symbol(), "ec-to-ek");
}

BC_AUTO_TEST_CASE(generated__symbol__ec_to_public__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ec_to_public::symbol(), "ec-to-public");
}

BC_AUTO_TEST_CASE(generated__symbol__ec_to_wif__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ec_to_wif::symbol(), "ec-to-wif");
}

BC_AUTO_TEST_CASE(generated__symbol__ec_to_witness__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ec_to_witness::symbol(), "ec-to-witness");
}

BC_AUTO_TEST_CASE(generated__symbol__ek_address__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ek_address::symbol(), "ek-address");
}

BC_AUTO_TEST_CASE(generated__symbol__ek_new__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ek_new::symbol(), "ek-new");
}

BC_AUTO_TEST_CASE(generated__symbol__ek_public__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ek_public::symbol(), "ek-public");
}

BC_AUTO_TEST_CASE(generated__symbol__ek_public_to_address__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ek_public_to_address::symbol(), "ek-public-to-address");
}

BC_AUTO_TEST_CASE(generated__symbol__ek_public_to_ec__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ek_public_to_ec::symbol(), "ek-public-to-ec");
}

BC_AUTO_TEST_CASE(generated__symbol__ek_to_address__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ek_to_address::symbol(), "ek-to-address");
}

BC_AUTO_TEST_CASE(generated__symbol__ek_to_ec__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ek_to_ec::symbol(), "ek-to-ec");
}

BC_AUTO_TEST_CASE(generated__symbol__electrum_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(electrum_decode::symbol(), "electrum-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__electrum_new__returns_expected_value)
{
    BC_REQUIRE_EQUAL(electrum_new::symbol(), "electrum-new");
}

BC_AUTO_TEST_CASE(generated__symbol__electrum_to_seed__returns_expected_value)
{
    BC_REQUIRE_EQUAL(electrum_to_seed::symbol(), "electrum-to-seed");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_balance__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_balance::symbol(), "fetch-balance");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_block__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_block::symbol(), "fetch-block");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_block_hashes__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_block_hashes::symbol(), "fetch-block-hashes");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_block_height__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_block_height::symbol(), "fetch-block-height");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_filter__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_filter::symbol(), "fetch-filter");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_filter_checkpoint__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_filter_checkpoint::symbol(), "fetch-filter-checkpoint");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_filter_headers__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_filter_headers::symbol(), "fetch-filter-headers");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_header__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_header::symbol(), "fetch-header");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_height__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_height::symbol(), "fetch-height");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_history__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_history::symbol(), "fetch-history");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_public_key__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_public_key::symbol(), "fetch-public-key");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_tx__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_tx::symbol(), "fetch-tx");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_tx_index__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_tx_index::symbol(), "fetch-tx-index");
}

BC_AUTO_TEST_CASE(generated__symbol__fetch_utxo__returns_expected_value)
{
    BC_REQUIRE_EQUAL(fetch_utxo::symbol(), "fetch-utxo");
}

BC_AUTO_TEST_CASE(generated__symbol__get_filter_checkpoint__returns_expected_value)
{
    BC_REQUIRE_EQUAL(get_filter_checkpoint::symbol(), "get-filter-checkpoint");
}

BC_AUTO_TEST_CASE(generated__symbol__get_filter_headers__returns_expected_value)
{
    BC_REQUIRE_EQUAL(get_filter_headers::symbol(), "get-filter-headers");
}

BC_AUTO_TEST_CASE(generated__symbol__get_filters__returns_expected_value)
{
    BC_REQUIRE_EQUAL(get_filters::symbol(), "get-filters");
}

BC_AUTO_TEST_CASE(generated__symbol__hd_new__returns_expected_value)
{
    BC_REQUIRE_EQUAL(hd_new::symbol(), "hd-new");
}

BC_AUTO_TEST_CASE(generated__symbol__hd_private__returns_expected_value)
{
    BC_REQUIRE_EQUAL(hd_private::symbol(), "hd-private");
}

BC_AUTO_TEST_CASE(generated__symbol__hd_public__returns_expected_value)
{
    BC_REQUIRE_EQUAL(hd_public::symbol(), "hd-public");
}

BC_AUTO_TEST_CASE(generated__symbol__hd_to_address__returns_expected_value)
{
    BC_REQUIRE_EQUAL(hd_to_address::symbol(), "hd-to-address");
}

BC_AUTO_TEST_CASE(generated__symbol__hd_to_ec__returns_expected_value)
{
    BC_REQUIRE_EQUAL(hd_to_ec::symbol(), "hd-to-ec");
}

BC_AUTO_TEST_CASE(generated__symbol__hd_to_public__returns_expected_value)
{
    BC_REQUIRE_EQUAL(hd_to_public::symbol(), "hd-to-public");
}

BC_AUTO_TEST_CASE(generated__symbol__hd_to_wif__returns_expected_value)
{
    BC_REQUIRE_EQUAL(hd_to_wif::symbol(), "hd-to-wif");
}

BC_AUTO_TEST_CASE(generated__symbol__help__returns_expected_value)
{
    BC_REQUIRE_EQUAL(help::symbol(), "help");
}

BC_AUTO_TEST_CASE(generated__symbol__input_set__returns_expected_value)
{
    BC_REQUIRE_EQUAL(input_set::symbol(), "input-set");
}

BC_AUTO_TEST_CASE(generated__symbol__input_sign__returns_expected_value)
{
    BC_REQUIRE_EQUAL(input_sign::symbol(), "input-sign");
}

BC_AUTO_TEST_CASE(generated__symbol__input_validate__returns_expected_value)
{
    BC_REQUIRE_EQUAL(input_validate::symbol(), "input-validate");
}

BC_AUTO_TEST_CASE(generated__symbol__match_neutrino_address__returns_expected_value)
{
    BC_REQUIRE_EQUAL(match_neutrino_address::symbol(), "match-neutrino-address");
}

BC_AUTO_TEST_CASE(generated__symbol__match_neutrino_script__returns_expected_value)
{
    BC_REQUIRE_EQUAL(match_neutrino_script::symbol(), "match-neutrino-script");
}

BC_AUTO_TEST_CASE(generated__symbol__message_sign__returns_expected_value)
{
    BC_REQUIRE_EQUAL(message_sign::symbol(), "message-sign");
}

BC_AUTO_TEST_CASE(generated__symbol__message_validate__returns_expected_value)
{
    BC_REQUIRE_EQUAL(message_validate::symbol(), "message-validate");
}

BC_AUTO_TEST_CASE(generated__symbol__mnemonic_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(mnemonic_decode::symbol(), "mnemonic-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__mnemonic_encode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(mnemonic_encode::symbol(), "mnemonic-encode");
}

BC_AUTO_TEST_CASE(generated__symbol__mnemonic_to_seed__returns_expected_value)
{
    BC_REQUIRE_EQUAL(mnemonic_to_seed::symbol(), "mnemonic-to-seed");
}

BC_AUTO_TEST_CASE(generated__symbol__put_tx__returns_expected_value)
{
    BC_REQUIRE_EQUAL(put_tx::symbol(), "put-tx");
}

BC_AUTO_TEST_CASE(generated__symbol__qrcode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(qrcode::symbol(), "qrcode");
}

BC_AUTO_TEST_CASE(generated__symbol__ripemd160__returns_expected_value)
{
    BC_REQUIRE_EQUAL(ripemd160::symbol(), "ripemd160");
}

BC_AUTO_TEST_CASE(generated__symbol__satoshi_to_btc__returns_expected_value)
{
    BC_REQUIRE_EQUAL(satoshi_to_btc::symbol(), "satoshi-to-btc");
}

BC_AUTO_TEST_CASE(generated__symbol__script_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(script_decode::symbol(), "script-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__script_encode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(script_encode::symbol(), "script-encode");
}

BC_AUTO_TEST_CASE(generated__symbol__script_to_address__returns_expected_value)
{
    BC_REQUIRE_EQUAL(script_to_address::symbol(), "script-to-address");
}

BC_AUTO_TEST_CASE(generated__symbol__script_to_key__returns_expected_value)
{
    BC_REQUIRE_EQUAL(script_to_key::symbol(), "script-to-key");
}

BC_AUTO_TEST_CASE(generated__symbol__script_to_witness__returns_expected_value)
{
    BC_REQUIRE_EQUAL(script_to_witness::symbol(), "script-to-witness");
}

BC_AUTO_TEST_CASE(generated__symbol__seed__returns_expected_value)
{
    BC_REQUIRE_EQUAL(seed::symbol(), "seed");
}

BC_AUTO_TEST_CASE(generated__symbol__send_tx__returns_expected_value)
{
    BC_REQUIRE_EQUAL(send_tx::symbol(), "send-tx");
}

BC_AUTO_TEST_CASE(generated__symbol__settings__returns_expected_value)
{
    BC_REQUIRE_EQUAL(settings::symbol(), "settings");
}

BC_AUTO_TEST_CASE(generated__symbol__sha160__returns_expected_value)
{
    BC_REQUIRE_EQUAL(sha160::symbol(), "sha160");
}

BC_AUTO_TEST_CASE(generated__symbol__sha256__returns_expected_value)
{
    BC_REQUIRE_EQUAL(sha256::symbol(), "sha256");
}

BC_AUTO_TEST_CASE(generated__symbol__sha512__returns_expected_value)
{
    BC_REQUIRE_EQUAL(sha512::symbol(), "sha512");
}

BC_AUTO_TEST_CASE(generated__symbol__stealth_public__returns_expected_value)
{
    BC_REQUIRE_EQUAL(stealth_public::symbol(), "stealth-public");
}

BC_AUTO_TEST_CASE(generated__symbol__stealth_secret__returns_expected_value)
{
    BC_REQUIRE_EQUAL(stealth_secret::symbol(), "stealth-secret");
}

BC_AUTO_TEST_CASE(generated__symbol__stealth_shared__returns_expected_value)
{
    BC_REQUIRE_EQUAL(stealth_shared::symbol(), "stealth-shared");
}

BC_AUTO_TEST_CASE(generated__symbol__subscribe_block__returns_expected_value)
{
    BC_REQUIRE_EQUAL(subscribe_block::symbol(), "subscribe-block");
}

BC_AUTO_TEST_CASE(generated__symbol__subscribe_tx__returns_expected_value)
{
    BC_REQUIRE_EQUAL(subscribe_tx::symbol(), "subscribe-tx");
}

BC_AUTO_TEST_CASE(generated__symbol__token_new__returns_expected_value)
{
    BC_REQUIRE_EQUAL(token_new::symbol(), "token-new");
}

BC_AUTO_TEST_CASE(generated__symbol__tx_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(tx_decode::symbol(), "tx-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__tx_encode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(tx_encode::symbol(), "tx-encode");
}

BC_AUTO_TEST_CASE(generated__symbol__tx_sign__returns_expected_value)
{
    BC_REQUIRE_EQUAL(tx_sign::symbol(), "tx-sign");
}

BC_AUTO_TEST_CASE(generated__symbol__uri_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(uri_decode::symbol(), "uri-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__uri_encode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(uri_encode::symbol(), "uri-encode");
}

BC_AUTO_TEST_CASE(generated__symbol__validate_tx__returns_expected_value)
{
    BC_REQUIRE_EQUAL(validate_tx::symbol(), "validate-tx");
}

BC_AUTO_TEST_CASE(generated__symbol__version__returns_expected_value)
{
    BC_REQUIRE_EQUAL(version::symbol(), "version");
}

BC_AUTO_TEST_CASE(generated__symbol__watch_key__returns_expected_value)
{
    BC_REQUIRE_EQUAL(watch_key::symbol(), "watch-key");
}

BC_AUTO_TEST_CASE(generated__symbol__watch_tx__returns_expected_value)
{
    BC_REQUIRE_EQUAL(watch_tx::symbol(), "watch-tx");
}

BC_AUTO_TEST_CASE(generated__symbol__wif_to_ec__returns_expected_value)
{
    BC_REQUIRE_EQUAL(wif_to_ec::symbol(), "wif-to-ec");
}

BC_AUTO_TEST_CASE(generated__symbol__wif_to_public__returns_expected_value)
{
    BC_REQUIRE_EQUAL(wif_to_public::symbol(), "wif-to-public");
}

BC_AUTO_TEST_CASE(generated__symbol__witness_to_key__returns_expected_value)
{
    BC_REQUIRE_EQUAL(witness_to_key::symbol(), "witness-to-key");
}

BC_AUTO_TEST_CASE(generated__symbol__wrap_decode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(wrap_decode::symbol(), "wrap-decode");
}

BC_AUTO_TEST_CASE(generated__symbol__wrap_encode__returns_expected_value)
{
    BC_REQUIRE_EQUAL(wrap_encode::symbol(), "wrap-encode");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
