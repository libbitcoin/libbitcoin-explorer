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

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;

BC_AUTO_TEST_SUITE(generated)
BC_AUTO_TEST_SUITE(generated__metadata)

BC_AUTO_TEST_CASE(generated__metadata__address_decode__returns_expected_values)
{
    address_decode command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__address_embed__returns_expected_values)
{
    address_embed command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__address_encode__returns_expected_values)
{
    address_encode command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__address_to_key__returns_expected_values)
{
    address_to_key command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__address_to_script__returns_expected_values)
{
    address_to_script command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__base16_decode__returns_expected_values)
{
    base16_decode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__base16_encode__returns_expected_values)
{
    base16_encode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__base32_decode__returns_expected_values)
{
    base32_decode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__base32_encode__returns_expected_values)
{
    base32_encode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__base58_decode__returns_expected_values)
{
    base58_decode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__base58_encode__returns_expected_values)
{
    base58_encode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__base58check_decode__returns_expected_values)
{
    base58check_decode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__base58check_encode__returns_expected_values)
{
    base58check_encode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__base64_decode__returns_expected_values)
{
    base64_decode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__base64_encode__returns_expected_values)
{
    base64_encode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__bech32_decode__returns_expected_values)
{
    bech32_decode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__bech32_encode__returns_expected_values)
{
    bech32_encode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__bitcoin160__returns_expected_values)
{
    bitcoin160 command;
    BC_REQUIRE_EQUAL(command.category(), "HASH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__bitcoin256__returns_expected_values)
{
    bitcoin256 command;
    BC_REQUIRE_EQUAL(command.category(), "HASH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__broadcast_tx__returns_expected_values)
{
    broadcast_tx command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__btc_to_satoshi__returns_expected_values)
{
    btc_to_satoshi command;
    BC_REQUIRE_EQUAL(command.category(), "MATH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__checked_decode__returns_expected_values)
{
    checked_decode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__checked_encode__returns_expected_values)
{
    checked_encode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__curve_new__returns_expected_values)
{
    curve_new command;
    BC_REQUIRE_EQUAL(command.category(), "MATH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__curve_public__returns_expected_values)
{
    curve_public command;
    BC_REQUIRE_EQUAL(command.category(), "MATH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__dice_entropy__returns_expected_values)
{
    dice_entropy command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__dice_rolls__returns_expected_values)
{
    dice_rolls command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ec_add__returns_expected_values)
{
    ec_add command;
    BC_REQUIRE_EQUAL(command.category(), "MATH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ec_add_secrets__returns_expected_values)
{
    ec_add_secrets command;
    BC_REQUIRE_EQUAL(command.category(), "MATH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ec_decompress__returns_expected_values)
{
    ec_decompress command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ec_multiply__returns_expected_values)
{
    ec_multiply command;
    BC_REQUIRE_EQUAL(command.category(), "MATH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ec_multiply_secrets__returns_expected_values)
{
    ec_multiply_secrets command;
    BC_REQUIRE_EQUAL(command.category(), "MATH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ec_new__returns_expected_values)
{
    ec_new command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ec_to_address__returns_expected_values)
{
    ec_to_address command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ec_to_ek__returns_expected_values)
{
    ec_to_ek command;
    BC_REQUIRE_EQUAL(command.category(), "KEY_ENCRYPTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ec_to_public__returns_expected_values)
{
    ec_to_public command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ec_to_wif__returns_expected_values)
{
    ec_to_wif command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ec_to_witness__returns_expected_values)
{
    ec_to_witness command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ek_address__returns_expected_values)
{
    ek_address command;
    BC_REQUIRE_EQUAL(command.category(), "KEY_ENCRYPTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ek_new__returns_expected_values)
{
    ek_new command;
    BC_REQUIRE_EQUAL(command.category(), "KEY_ENCRYPTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ek_public__returns_expected_values)
{
    ek_public command;
    BC_REQUIRE_EQUAL(command.category(), "KEY_ENCRYPTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ek_public_to_address__returns_expected_values)
{
    ek_public_to_address command;
    BC_REQUIRE_EQUAL(command.category(), "KEY_ENCRYPTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ek_public_to_ec__returns_expected_values)
{
    ek_public_to_ec command;
    BC_REQUIRE_EQUAL(command.category(), "KEY_ENCRYPTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ek_to_address__returns_expected_values)
{
    ek_to_address command;
    BC_REQUIRE_EQUAL(command.category(), "KEY_ENCRYPTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ek_to_ec__returns_expected_values)
{
    ek_to_ec command;
    BC_REQUIRE_EQUAL(command.category(), "KEY_ENCRYPTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__electrum_decode__returns_expected_values)
{
    electrum_decode command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__electrum_new__returns_expected_values)
{
    electrum_new command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__electrum_to_prefix__returns_expected_values)
{
    electrum_to_prefix command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__electrum_to_seed__returns_expected_values)
{
    electrum_to_seed command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__electrum_v1_decode__returns_expected_values)
{
    electrum_v1_decode command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__electrum_v1_encode__returns_expected_values)
{
    electrum_v1_encode command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__electrum_v1_to_seed__returns_expected_values)
{
    electrum_v1_to_seed command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_balance__returns_expected_values)
{
    fetch_balance command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_block__returns_expected_values)
{
    fetch_block command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_block_hashes__returns_expected_values)
{
    fetch_block_hashes command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_block_height__returns_expected_values)
{
    fetch_block_height command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_filter__returns_expected_values)
{
    fetch_filter command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_filter_checkpoint__returns_expected_values)
{
    fetch_filter_checkpoint command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_filter_headers__returns_expected_values)
{
    fetch_filter_headers command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_header__returns_expected_values)
{
    fetch_header command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_height__returns_expected_values)
{
    fetch_height command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_history__returns_expected_values)
{
    fetch_history command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_public_key__returns_expected_values)
{
    fetch_public_key command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_tx__returns_expected_values)
{
    fetch_tx command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_tx_index__returns_expected_values)
{
    fetch_tx_index command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__fetch_utxo__returns_expected_values)
{
    fetch_utxo command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__get_filter_checkpoint__returns_expected_values)
{
    get_filter_checkpoint command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__get_filter_headers__returns_expected_values)
{
    get_filter_headers command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__get_filters__returns_expected_values)
{
    get_filters command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__hd_new__returns_expected_values)
{
    hd_new command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__hd_private__returns_expected_values)
{
    hd_private command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__hd_public__returns_expected_values)
{
    hd_public command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__hd_to_address__returns_expected_values)
{
    hd_to_address command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__hd_to_ec__returns_expected_values)
{
    hd_to_ec command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__hd_to_public__returns_expected_values)
{
    hd_to_public command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__hd_to_wif__returns_expected_values)
{
    hd_to_wif command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__help__returns_expected_values)
{
    help command;
    BC_REQUIRE_EQUAL(command.category(), "META");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__input_set__returns_expected_values)
{
    input_set command;
    BC_REQUIRE_EQUAL(command.category(), "TRANSACTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__input_sign__returns_expected_values)
{
    input_sign command;
    BC_REQUIRE_EQUAL(command.category(), "TRANSACTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__input_validate__returns_expected_values)
{
    input_validate command;
    BC_REQUIRE_EQUAL(command.category(), "TRANSACTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__match_neutrino_address__returns_expected_values)
{
    match_neutrino_address command;
    BC_REQUIRE_EQUAL(command.category(), "MATH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__match_neutrino_script__returns_expected_values)
{
    match_neutrino_script command;
    BC_REQUIRE_EQUAL(command.category(), "MATH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__message_sign__returns_expected_values)
{
    message_sign command;
    BC_REQUIRE_EQUAL(command.category(), "MESSAGING");
    BC_REQUIRE(command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__message_validate__returns_expected_values)
{
    message_validate command;
    BC_REQUIRE_EQUAL(command.category(), "MESSAGING");
    BC_REQUIRE(command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__mnemonic_decode__returns_expected_values)
{
    mnemonic_decode command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__mnemonic_encode__returns_expected_values)
{
    mnemonic_encode command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__mnemonic_to_seed__returns_expected_values)
{
    mnemonic_to_seed command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__put_tx__returns_expected_values)
{
    put_tx command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__qrcode__returns_expected_values)
{
    qrcode command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__ripemd160__returns_expected_values)
{
    ripemd160 command;
    BC_REQUIRE_EQUAL(command.category(), "HASH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__satoshi_to_btc__returns_expected_values)
{
    satoshi_to_btc command;
    BC_REQUIRE_EQUAL(command.category(), "MATH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__script_decode__returns_expected_values)
{
    script_decode command;
    BC_REQUIRE_EQUAL(command.category(), "TRANSACTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__script_encode__returns_expected_values)
{
    script_encode command;
    BC_REQUIRE_EQUAL(command.category(), "TRANSACTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__script_to_address__returns_expected_values)
{
    script_to_address command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__script_to_key__returns_expected_values)
{
    script_to_key command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__script_to_witness__returns_expected_values)
{
    script_to_witness command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__seed__returns_expected_values)
{
    seed command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__send_tx__returns_expected_values)
{
    send_tx command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__settings__returns_expected_values)
{
    settings command;
    BC_REQUIRE_EQUAL(command.category(), "META");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__sha160__returns_expected_values)
{
    sha160 command;
    BC_REQUIRE_EQUAL(command.category(), "HASH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__sha256__returns_expected_values)
{
    sha256 command;
    BC_REQUIRE_EQUAL(command.category(), "HASH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__sha512__returns_expected_values)
{
    sha512 command;
    BC_REQUIRE_EQUAL(command.category(), "HASH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__slip39_combine__returns_expected_values)
{
    slip39_combine command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__slip39_decode__returns_expected_values)
{
    slip39_decode command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__slip39_split__returns_expected_values)
{
    slip39_split command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__stealth_public__returns_expected_values)
{
    stealth_public command;
    BC_REQUIRE_EQUAL(command.category(), "STEALTH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__stealth_secret__returns_expected_values)
{
    stealth_secret command;
    BC_REQUIRE_EQUAL(command.category(), "STEALTH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__stealth_shared__returns_expected_values)
{
    stealth_shared command;
    BC_REQUIRE_EQUAL(command.category(), "STEALTH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__subscribe_block__returns_expected_values)
{
    subscribe_block command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__subscribe_tx__returns_expected_values)
{
    subscribe_tx command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__tls_cert__returns_expected_values)
{
    tls_cert command;
    BC_REQUIRE_EQUAL(command.category(), "MATH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__tls_new__returns_expected_values)
{
    tls_new command;
    BC_REQUIRE_EQUAL(command.category(), "MATH");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__token_new__returns_expected_values)
{
    token_new command;
    BC_REQUIRE_EQUAL(command.category(), "KEY_ENCRYPTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__tx_decode__returns_expected_values)
{
    tx_decode command;
    BC_REQUIRE_EQUAL(command.category(), "TRANSACTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__tx_encode__returns_expected_values)
{
    tx_encode command;
    BC_REQUIRE_EQUAL(command.category(), "TRANSACTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__tx_sign__returns_expected_values)
{
    tx_sign command;
    BC_REQUIRE_EQUAL(command.category(), "TRANSACTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__uri_decode__returns_expected_values)
{
    uri_decode command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__uri_encode__returns_expected_values)
{
    uri_encode command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__validate_tx__returns_expected_values)
{
    validate_tx command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__version__returns_expected_values)
{
    version command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__watch_key__returns_expected_values)
{
    watch_key command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__watch_tx__returns_expected_values)
{
    watch_tx command;
    BC_REQUIRE_EQUAL(command.category(), "ONLINE");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__wif_to_ec__returns_expected_values)
{
    wif_to_ec command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__wif_to_public__returns_expected_values)
{
    wif_to_public command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__witness_decode__returns_expected_values)
{
    witness_decode command;
    BC_REQUIRE_EQUAL(command.category(), "TRANSACTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__witness_encode__returns_expected_values)
{
    witness_encode command;
    BC_REQUIRE_EQUAL(command.category(), "TRANSACTION");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__witness_to_key__returns_expected_values)
{
    witness_to_key command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__witness_to_script__returns_expected_values)
{
    witness_to_script command;
    BC_REQUIRE_EQUAL(command.category(), "WALLET");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__wrap_decode__returns_expected_values)
{
    wrap_decode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_CASE(generated__metadata__wrap_encode__returns_expected_values)
{
    wrap_encode command;
    BC_REQUIRE_EQUAL(command.category(), "ENCODING");
    BC_REQUIRE(!command.requires_raw_input());
    BC_REQUIRE(!command.requires_raw_output());
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
