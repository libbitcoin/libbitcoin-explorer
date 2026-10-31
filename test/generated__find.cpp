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
BC_AUTO_TEST_SUITE(generated__find)

BC_AUTO_TEST_CASE(generated__find__address_decode__returns_object)
{
    BC_REQUIRE(find("address-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__address_embed__returns_object)
{
    BC_REQUIRE(find("address-embed") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__address_encode__returns_object)
{
    BC_REQUIRE(find("address-encode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__address_to_key__returns_object)
{
    BC_REQUIRE(find("address-to-key") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__base16_decode__returns_object)
{
    BC_REQUIRE(find("base16-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__base16_encode__returns_object)
{
    BC_REQUIRE(find("base16-encode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__base32_decode__returns_object)
{
    BC_REQUIRE(find("base32-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__base32_encode__returns_object)
{
    BC_REQUIRE(find("base32-encode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__base58_decode__returns_object)
{
    BC_REQUIRE(find("base58-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__base58_encode__returns_object)
{
    BC_REQUIRE(find("base58-encode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__base58check_decode__returns_object)
{
    BC_REQUIRE(find("base58check-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__base58check_encode__returns_object)
{
    BC_REQUIRE(find("base58check-encode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__base64_decode__returns_object)
{
    BC_REQUIRE(find("base64-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__base64_encode__returns_object)
{
    BC_REQUIRE(find("base64-encode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__bech32_decode__returns_object)
{
    BC_REQUIRE(find("bech32-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__bech32_encode__returns_object)
{
    BC_REQUIRE(find("bech32-encode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__bitcoin160__returns_object)
{
    BC_REQUIRE(find("bitcoin160") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__bitcoin256__returns_object)
{
    BC_REQUIRE(find("bitcoin256") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__broadcast_tx__returns_object)
{
    BC_REQUIRE(find("broadcast-tx") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__btc_to_satoshi__returns_object)
{
    BC_REQUIRE(find("btc-to-satoshi") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__cert_new__returns_object)
{
    BC_REQUIRE(find("cert-new") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__cert_public__returns_object)
{
    BC_REQUIRE(find("cert-public") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__checked_decode__returns_object)
{
    BC_REQUIRE(find("checked-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__checked_encode__returns_object)
{
    BC_REQUIRE(find("checked-encode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__dice_entropy__returns_object)
{
    BC_REQUIRE(find("dice-entropy") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ec_add__returns_object)
{
    BC_REQUIRE(find("ec-add") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ec_add_secrets__returns_object)
{
    BC_REQUIRE(find("ec-add-secrets") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ec_decompress__returns_object)
{
    BC_REQUIRE(find("ec-decompress") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ec_multiply__returns_object)
{
    BC_REQUIRE(find("ec-multiply") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ec_multiply_secrets__returns_object)
{
    BC_REQUIRE(find("ec-multiply-secrets") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ec_new__returns_object)
{
    BC_REQUIRE(find("ec-new") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ec_to_address__returns_object)
{
    BC_REQUIRE(find("ec-to-address") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ec_to_ek__returns_object)
{
    BC_REQUIRE(find("ec-to-ek") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ec_to_public__returns_object)
{
    BC_REQUIRE(find("ec-to-public") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ec_to_wif__returns_object)
{
    BC_REQUIRE(find("ec-to-wif") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ec_to_witness__returns_object)
{
    BC_REQUIRE(find("ec-to-witness") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ek_address__returns_object)
{
    BC_REQUIRE(find("ek-address") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ek_new__returns_object)
{
    BC_REQUIRE(find("ek-new") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ek_public__returns_object)
{
    BC_REQUIRE(find("ek-public") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ek_public_to_address__returns_object)
{
    BC_REQUIRE(find("ek-public-to-address") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ek_public_to_ec__returns_object)
{
    BC_REQUIRE(find("ek-public-to-ec") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ek_to_address__returns_object)
{
    BC_REQUIRE(find("ek-to-address") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ek_to_ec__returns_object)
{
    BC_REQUIRE(find("ek-to-ec") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__electrum_decode__returns_object)
{
    BC_REQUIRE(find("electrum-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__electrum_new__returns_object)
{
    BC_REQUIRE(find("electrum-new") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__electrum_to_seed__returns_object)
{
    BC_REQUIRE(find("electrum-to-seed") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_balance__returns_object)
{
    BC_REQUIRE(find("fetch-balance") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_block__returns_object)
{
    BC_REQUIRE(find("fetch-block") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_block_hashes__returns_object)
{
    BC_REQUIRE(find("fetch-block-hashes") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_block_height__returns_object)
{
    BC_REQUIRE(find("fetch-block-height") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_filter__returns_object)
{
    BC_REQUIRE(find("fetch-filter") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_filter_checkpoint__returns_object)
{
    BC_REQUIRE(find("fetch-filter-checkpoint") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_filter_headers__returns_object)
{
    BC_REQUIRE(find("fetch-filter-headers") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_header__returns_object)
{
    BC_REQUIRE(find("fetch-header") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_height__returns_object)
{
    BC_REQUIRE(find("fetch-height") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_history__returns_object)
{
    BC_REQUIRE(find("fetch-history") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_public_key__returns_object)
{
    BC_REQUIRE(find("fetch-public-key") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_tx__returns_object)
{
    BC_REQUIRE(find("fetch-tx") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_tx_index__returns_object)
{
    BC_REQUIRE(find("fetch-tx-index") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__fetch_utxo__returns_object)
{
    BC_REQUIRE(find("fetch-utxo") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__get_filter_checkpoint__returns_object)
{
    BC_REQUIRE(find("get-filter-checkpoint") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__get_filter_headers__returns_object)
{
    BC_REQUIRE(find("get-filter-headers") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__get_filters__returns_object)
{
    BC_REQUIRE(find("get-filters") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__hd_new__returns_object)
{
    BC_REQUIRE(find("hd-new") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__hd_private__returns_object)
{
    BC_REQUIRE(find("hd-private") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__hd_public__returns_object)
{
    BC_REQUIRE(find("hd-public") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__hd_to_address__returns_object)
{
    BC_REQUIRE(find("hd-to-address") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__hd_to_ec__returns_object)
{
    BC_REQUIRE(find("hd-to-ec") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__hd_to_public__returns_object)
{
    BC_REQUIRE(find("hd-to-public") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__hd_to_wif__returns_object)
{
    BC_REQUIRE(find("hd-to-wif") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__help__returns_object)
{
    BC_REQUIRE(find("help") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__input_set__returns_object)
{
    BC_REQUIRE(find("input-set") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__input_sign__returns_object)
{
    BC_REQUIRE(find("input-sign") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__input_validate__returns_object)
{
    BC_REQUIRE(find("input-validate") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__match_neutrino_address__returns_object)
{
    BC_REQUIRE(find("match-neutrino-address") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__match_neutrino_script__returns_object)
{
    BC_REQUIRE(find("match-neutrino-script") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__message_sign__returns_object)
{
    BC_REQUIRE(find("message-sign") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__message_validate__returns_object)
{
    BC_REQUIRE(find("message-validate") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__mnemonic_decode__returns_object)
{
    BC_REQUIRE(find("mnemonic-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__mnemonic_encode__returns_object)
{
    BC_REQUIRE(find("mnemonic-encode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__mnemonic_to_seed__returns_object)
{
    BC_REQUIRE(find("mnemonic-to-seed") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__put_tx__returns_object)
{
    BC_REQUIRE(find("put-tx") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__qrcode__returns_object)
{
    BC_REQUIRE(find("qrcode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__ripemd160__returns_object)
{
    BC_REQUIRE(find("ripemd160") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__satoshi_to_btc__returns_object)
{
    BC_REQUIRE(find("satoshi-to-btc") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__script_decode__returns_object)
{
    BC_REQUIRE(find("script-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__script_encode__returns_object)
{
    BC_REQUIRE(find("script-encode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__script_to_address__returns_object)
{
    BC_REQUIRE(find("script-to-address") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__script_to_key__returns_object)
{
    BC_REQUIRE(find("script-to-key") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__script_to_witness__returns_object)
{
    BC_REQUIRE(find("script-to-witness") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__seed__returns_object)
{
    BC_REQUIRE(find("seed") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__send_tx__returns_object)
{
    BC_REQUIRE(find("send-tx") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__settings__returns_object)
{
    BC_REQUIRE(find("settings") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__sha160__returns_object)
{
    BC_REQUIRE(find("sha160") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__sha256__returns_object)
{
    BC_REQUIRE(find("sha256") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__sha512__returns_object)
{
    BC_REQUIRE(find("sha512") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__stealth_public__returns_object)
{
    BC_REQUIRE(find("stealth-public") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__stealth_secret__returns_object)
{
    BC_REQUIRE(find("stealth-secret") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__stealth_shared__returns_object)
{
    BC_REQUIRE(find("stealth-shared") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__subscribe_block__returns_object)
{
    BC_REQUIRE(find("subscribe-block") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__subscribe_tx__returns_object)
{
    BC_REQUIRE(find("subscribe-tx") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__token_new__returns_object)
{
    BC_REQUIRE(find("token-new") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__tx_decode__returns_object)
{
    BC_REQUIRE(find("tx-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__tx_encode__returns_object)
{
    BC_REQUIRE(find("tx-encode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__tx_sign__returns_object)
{
    BC_REQUIRE(find("tx-sign") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__uri_decode__returns_object)
{
    BC_REQUIRE(find("uri-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__uri_encode__returns_object)
{
    BC_REQUIRE(find("uri-encode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__validate_tx__returns_object)
{
    BC_REQUIRE(find("validate-tx") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__version__returns_object)
{
    BC_REQUIRE(find("version") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__watch_key__returns_object)
{
    BC_REQUIRE(find("watch-key") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__watch_tx__returns_object)
{
    BC_REQUIRE(find("watch-tx") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__wif_to_ec__returns_object)
{
    BC_REQUIRE(find("wif-to-ec") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__wif_to_public__returns_object)
{
    BC_REQUIRE(find("wif-to-public") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__witness_to_key__returns_object)
{
    BC_REQUIRE(find("witness-to-key") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__wrap_decode__returns_object)
{
    BC_REQUIRE(find("wrap-decode") != nullptr);
}

BC_AUTO_TEST_CASE(generated__find__wrap_encode__returns_object)
{
    BC_REQUIRE(find("wrap-encode") != nullptr);
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
