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
    address_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "address-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__address_embed__okay_output)
{
    address_embed command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "address-embed", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__address_encode__okay_output)
{
    address_encode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "address-encode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__address_to_key__okay_output)
{
    address_to_key command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "address-to-key", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base16_decode__okay_output)
{
    base16_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "base16-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base16_encode__okay_output)
{
    base16_encode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "base16-encode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base32_decode__okay_output)
{
    base32_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "base32-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base32_encode__okay_output)
{
    base32_encode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "base32-encode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base58_decode__okay_output)
{
    base58_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "base58-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base58_encode__okay_output)
{
    base58_encode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "base58-encode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base58check_decode__okay_output)
{
    base58check_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "base58check-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base58check_encode__okay_output)
{
    base58check_encode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "base58check-encode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base64_decode__okay_output)
{
    base64_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "base64-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__base64_encode__okay_output)
{
    base64_encode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "base64-encode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__bech32_decode__okay_output)
{
    bech32_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "bech32-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__bech32_encode__okay_output)
{
    bech32_encode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "bech32-encode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__bitcoin160__okay_output)
{
    bitcoin160 command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "bitcoin160", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__bitcoin256__okay_output)
{
    bitcoin256 command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "bitcoin256", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__broadcast_tx__okay_output)
{
    broadcast_tx command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "broadcast-tx", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__btc_to_satoshi__okay_output)
{
    btc_to_satoshi command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "btc-to-satoshi", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__cert_new__okay_output)
{
    cert_new command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "cert-new", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__cert_public__okay_output)
{
    cert_public command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "cert-public", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__checked_decode__okay_output)
{
    checked_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "checked-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__checked_encode__okay_output)
{
    checked_encode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "checked-encode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__dice_entropy__okay_output)
{
    dice_entropy command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "dice-entropy", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__dice_rolls__okay_output)
{
    dice_rolls command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "dice-rolls", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_add__okay_output)
{
    ec_add command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ec-add", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_add_secrets__okay_output)
{
    ec_add_secrets command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ec-add-secrets", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_decompress__okay_output)
{
    ec_decompress command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ec-decompress", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_multiply__okay_output)
{
    ec_multiply command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ec-multiply", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_multiply_secrets__okay_output)
{
    ec_multiply_secrets command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ec-multiply-secrets", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_new__okay_output)
{
    ec_new command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ec-new", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_to_address__okay_output)
{
    ec_to_address command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ec-to-address", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_to_ek__okay_output)
{
    ec_to_ek command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ec-to-ek", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_to_public__okay_output)
{
    ec_to_public command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ec-to-public", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_to_wif__okay_output)
{
    ec_to_wif command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ec-to-wif", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ec_to_witness__okay_output)
{
    ec_to_witness command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ec-to-witness", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_address__okay_output)
{
    ek_address command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ek-address", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_new__okay_output)
{
    ek_new command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ek-new", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_public__okay_output)
{
    ek_public command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ek-public", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_public_to_address__okay_output)
{
    ek_public_to_address command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ek-public-to-address", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_public_to_ec__okay_output)
{
    ek_public_to_ec command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ek-public-to-ec", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_to_address__okay_output)
{
    ek_to_address command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ek-to-address", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ek_to_ec__okay_output)
{
    ek_to_ec command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ek-to-ec", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__electrum_decode__okay_output)
{
    electrum_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "electrum-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__electrum_new__okay_output)
{
    electrum_new command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "electrum-new", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__electrum_to_seed__okay_output)
{
    electrum_to_seed command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "electrum-to-seed", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_balance__okay_output)
{
    fetch_balance command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-balance", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_block__okay_output)
{
    fetch_block command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-block", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_block_hashes__okay_output)
{
    fetch_block_hashes command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-block-hashes", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_block_height__okay_output)
{
    fetch_block_height command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-block-height", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_filter__okay_output)
{
    fetch_filter command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-filter", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_filter_checkpoint__okay_output)
{
    fetch_filter_checkpoint command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-filter-checkpoint", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_filter_headers__okay_output)
{
    fetch_filter_headers command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-filter-headers", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_header__okay_output)
{
    fetch_header command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-header", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_height__okay_output)
{
    fetch_height command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-height", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_history__okay_output)
{
    fetch_history command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-history", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_public_key__okay_output)
{
    fetch_public_key command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-public-key", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_tx__okay_output)
{
    fetch_tx command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-tx", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_tx_index__okay_output)
{
    fetch_tx_index command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-tx-index", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__fetch_utxo__okay_output)
{
    fetch_utxo command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "fetch-utxo", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__get_filter_checkpoint__okay_output)
{
    get_filter_checkpoint command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "get-filter-checkpoint", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__get_filter_headers__okay_output)
{
    get_filter_headers command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "get-filter-headers", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__get_filters__okay_output)
{
    get_filters command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "get-filters", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_new__okay_output)
{
    hd_new command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "hd-new", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_private__okay_output)
{
    hd_private command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "hd-private", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_public__okay_output)
{
    hd_public command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "hd-public", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_to_address__okay_output)
{
    hd_to_address command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "hd-to-address", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_to_ec__okay_output)
{
    hd_to_ec command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "hd-to-ec", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_to_public__okay_output)
{
    hd_to_public command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "hd-to-public", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__hd_to_wif__okay_output)
{
    hd_to_wif command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "hd-to-wif", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__help__okay_output)
{
    help command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "help", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__input_set__okay_output)
{
    input_set command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "input-set", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__input_sign__okay_output)
{
    input_sign command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "input-sign", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__input_validate__okay_output)
{
    input_validate command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "input-validate", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__match_neutrino_address__okay_output)
{
    match_neutrino_address command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "match-neutrino-address", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__match_neutrino_script__okay_output)
{
    match_neutrino_script command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "match-neutrino-script", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__message_sign__okay_output)
{
    message_sign command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "message-sign", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__message_validate__okay_output)
{
    message_validate command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "message-validate", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__mnemonic_decode__okay_output)
{
    mnemonic_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "mnemonic-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__mnemonic_encode__okay_output)
{
    mnemonic_encode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "mnemonic-encode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__mnemonic_to_seed__okay_output)
{
    mnemonic_to_seed command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "mnemonic-to-seed", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__put_tx__okay_output)
{
    put_tx command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "put-tx", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__qrcode__okay_output)
{
    qrcode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "qrcode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__ripemd160__okay_output)
{
    ripemd160 command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "ripemd160", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__satoshi_to_btc__okay_output)
{
    satoshi_to_btc command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "satoshi-to-btc", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__script_decode__okay_output)
{
    script_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "script-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__script_encode__okay_output)
{
    script_encode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "script-encode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__script_to_address__okay_output)
{
    script_to_address command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "script-to-address", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__script_to_key__okay_output)
{
    script_to_key command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "script-to-key", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__script_to_witness__okay_output)
{
    script_to_witness command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "script-to-witness", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__seed__okay_output)
{
    seed command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "seed", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__send_tx__okay_output)
{
    send_tx command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "send-tx", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__settings__okay_output)
{
    settings command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "settings", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__sha160__okay_output)
{
    sha160 command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "sha160", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__sha256__okay_output)
{
    sha256 command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "sha256", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__sha512__okay_output)
{
    sha512 command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "sha512", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__stealth_public__okay_output)
{
    stealth_public command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "stealth-public", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__stealth_secret__okay_output)
{
    stealth_secret command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "stealth-secret", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__stealth_shared__okay_output)
{
    stealth_shared command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "stealth-shared", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__subscribe_block__okay_output)
{
    subscribe_block command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "subscribe-block", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__subscribe_tx__okay_output)
{
    subscribe_tx command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "subscribe-tx", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__token_new__okay_output)
{
    token_new command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "token-new", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__tx_decode__okay_output)
{
    tx_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "tx-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__tx_encode__okay_output)
{
    tx_encode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "tx-encode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__tx_sign__okay_output)
{
    tx_sign command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "tx-sign", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__uri_decode__okay_output)
{
    uri_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "uri-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__uri_encode__okay_output)
{
    uri_encode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "uri-encode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__validate_tx__okay_output)
{
    validate_tx command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "validate-tx", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__version__okay_output)
{
    version command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "version", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__watch_key__okay_output)
{
    watch_key command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "watch-key", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__watch_tx__okay_output)
{
    watch_tx command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "watch-tx", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__wif_to_ec__okay_output)
{
    wif_to_ec command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "wif-to-ec", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__wif_to_public__okay_output)
{
    wif_to_public command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "wif-to-public", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__witness_to_key__okay_output)
{
    witness_to_key command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "witness-to-key", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__wrap_decode__okay_output)
{
    wrap_decode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "wrap-decode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(generated__help__wrap_encode__okay_output)
{
    wrap_encode command;
    std::string message;
    std::stringstream input, output;
    const char* argv[]{ "wrap-encode", "--help" };
    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
    command.write_help(output);
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
