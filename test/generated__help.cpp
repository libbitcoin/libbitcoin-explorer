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
BC_AUTO_TEST_SUITE(generated__help)

BC_AUTO_TEST_CASE(generated__help__address_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "address-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__address_embed__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "address-embed", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__address_encode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "address-encode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__address_to_key__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "address-to-key", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base16_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "base16-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base16_encode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "base16-encode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base32_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "base32-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base32_encode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "base32-encode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base58_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "base58-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base58_encode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "base58-encode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base58check_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "base58check-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base58check_encode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "base58check-encode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base64_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "base64-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base64_encode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "base64-encode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__bech32_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "bech32-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__bech32_encode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "bech32-encode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__bitcoin160__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "bitcoin160", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__bitcoin256__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "bitcoin256", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__broadcast_tx__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "broadcast-tx", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__btc_to_satoshi__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "btc-to-satoshi", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__cert_new__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "cert-new", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__cert_public__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "cert-public", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__checked_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "checked-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__checked_encode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "checked-encode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__dice_entropy__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "dice-entropy", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_add__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ec-add", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_add_secrets__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ec-add-secrets", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_decompress__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ec-decompress", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_multiply__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ec-multiply", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_multiply_secrets__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ec-multiply-secrets", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_new__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ec-new", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_to_address__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ec-to-address", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_to_ek__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ec-to-ek", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_to_public__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ec-to-public", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_to_wif__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ec-to-wif", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_to_witness__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ec-to-witness", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_address__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ek-address", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_new__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ek-new", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_public__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ek-public", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_public_to_address__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ek-public-to-address", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_public_to_ec__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ek-public-to-ec", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_to_address__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ek-to-address", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_to_ec__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ek-to-ec", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__electrum_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "electrum-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__electrum_new__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "electrum-new", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__electrum_to_seed__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "electrum-to-seed", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_balance__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-balance", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_block__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-block", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_block_hashes__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-block-hashes", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_block_height__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-block-height", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_filter__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-filter", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_filter_checkpoint__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-filter-checkpoint", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_filter_headers__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-filter-headers", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_header__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-header", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_height__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-height", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_history__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-history", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_public_key__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-public-key", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_tx__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-tx", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_tx_index__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-tx-index", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_utxo__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "fetch-utxo", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__get_filter_checkpoint__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "get-filter-checkpoint", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__get_filter_headers__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "get-filter-headers", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__get_filters__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "get-filters", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_new__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "hd-new", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_private__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "hd-private", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_public__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "hd-public", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_to_address__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "hd-to-address", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_to_ec__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "hd-to-ec", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_to_public__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "hd-to-public", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_to_wif__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "hd-to-wif", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__help__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "help", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__input_set__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "input-set", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__input_sign__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "input-sign", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__input_validate__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "input-validate", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__match_neutrino_address__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "match-neutrino-address", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__match_neutrino_script__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "match-neutrino-script", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__message_sign__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "message-sign", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__message_validate__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "message-validate", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__mnemonic_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "mnemonic-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__mnemonic_encode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "mnemonic-encode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__mnemonic_to_seed__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "mnemonic-to-seed", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__put_tx__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "put-tx", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__qrcode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "qrcode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ripemd160__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "ripemd160", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__satoshi_to_btc__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "satoshi-to-btc", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__script_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "script-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__script_encode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "script-encode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__script_to_address__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "script-to-address", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__script_to_key__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "script-to-key", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__script_to_witness__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "script-to-witness", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__seed__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "seed", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__send_tx__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "send-tx", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__settings__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "settings", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__sha160__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "sha160", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__sha256__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "sha256", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__sha512__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "sha512", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__stealth_public__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "stealth-public", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__stealth_secret__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "stealth-secret", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__stealth_shared__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "stealth-shared", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__subscribe_block__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "subscribe-block", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__subscribe_tx__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "subscribe-tx", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__token_new__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "token-new", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__tx_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "tx-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__tx_encode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "tx-encode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__tx_sign__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "tx-sign", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__uri_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "uri-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__uri_encode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "uri-encode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__validate_tx__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "validate-tx", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__version__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "version", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__watch_key__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "watch-key", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__watch_tx__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "watch-tx", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__wif_to_ec__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "wif-to-ec", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__wif_to_public__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "wif-to-public", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__witness_to_key__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "witness-to-key", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__wrap_decode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "wrap-decode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__wrap_encode__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "wrap-encode", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
