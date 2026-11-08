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
BC_AUTO_TEST_SUITE(generated__parse)

BC_AUTO_TEST_CASE(generated__parse__address_decode__okay)
{
    address_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "address-decode",
        "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__address_embed__okay)
{
    address_embed command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "address-embed",
        "--version", "42",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__address_encode__okay)
{
    address_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "address-encode",
        "--version", "42",
        "b472a266d0bd89c13706a4132ccfb16f7c3b9fcb",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__address_to_key__okay)
{
    address_to_key command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "address-to-key",
        "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__address_to_script__okay)
{
    address_to_script command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "address-to-script",
        "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__base16_decode__okay)
{
    base16_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "base16-decode",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__base16_encode__okay)
{
    base16_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "base16-encode",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__base32_decode__okay)
{
    base32_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "base32-decode",
        "MJQWCZDGGAYGI===",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__base32_encode__okay)
{
    base32_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "base32-encode",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__base58_decode__okay)
{
    base58_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "base58-decode",
        "5mm7zk",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__base58_encode__okay)
{
    base58_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "base58-encode",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__base58check_decode__okay)
{
    base58check_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "base58check-decode",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__base58check_encode__okay)
{
    base58check_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "base58check-encode",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__base64_decode__okay)
{
    base64_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "base64-decode",
        "YmFhZGYwMGQ=",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__base64_encode__okay)
{
    base64_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "base64-encode",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__bech32_decode__okay)
{
    bech32_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "bech32-decode",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__bech32_encode__okay)
{
    bech32_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "bech32-encode",
        "--version", "42",
        "string",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 5, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__bitcoin160__okay)
{
    bitcoin160 command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "bitcoin160",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__bitcoin256__okay)
{
    bitcoin256 command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "bitcoin256",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__broadcast_tx__okay)
{
    broadcast_tx command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "broadcast-tx",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__btc_to_satoshi__okay)
{
    btc_to_satoshi command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "btc-to-satoshi",
        "42.42",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__checked_decode__okay)
{
    checked_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "checked-decode",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__checked_encode__okay)
{
    checked_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "checked-encode",
        "--version", "42",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__curve_new__okay)
{
    curve_new command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "curve-new",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__curve_public__okay)
{
    curve_public command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "curve-public",
        "HelloWorld",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__dice_entropy__okay)
{
    dice_entropy command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "dice-entropy",
        "--sides", "42",
        "string",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__dice_rolls__okay)
{
    dice_rolls command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "dice-rolls",
        "--sides", "42",
        "--bits", "42",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 5, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ec_add__okay)
{
    ec_add command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ec-add",
        "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5",
        "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ec_add_secrets__okay)
{
    ec_add_secrets command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ec-add-secrets",
        "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ec_decompress__okay)
{
    ec_decompress command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ec-decompress",
        "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ec_multiply__okay)
{
    ec_multiply command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ec-multiply",
        "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5",
        "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ec_multiply_secrets__okay)
{
    ec_multiply_secrets command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ec-multiply-secrets",
        "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ec_new__okay)
{
    ec_new command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ec-new",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ec_to_address__okay)
{
    ec_to_address command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ec-to-address",
        "--version", "42",
        "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ec_to_ek__okay)
{
    ec_to_ek command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ec-to-ek",
        "--uncompressed",
        "--version", "42",
        "string",
        "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ec_to_public__okay)
{
    ec_to_public command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ec-to-public",
        "--uncompressed",
        "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ec_to_wif__okay)
{
    ec_to_wif command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ec-to-wif",
        "--uncompressed",
        "--version", "42",
        "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 5, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ec_to_witness__okay)
{
    ec_to_witness command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ec-to-witness",
        "string",
        "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ek_address__okay)
{
    ek_address command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ek-address",
        "--uncompressed",
        "--version", "42",
        "passphrasecpXbDpHuo8F7yuZqR49koDA9uQojPijjjZaxsar7Woo9pfHJbeWF3VMU9EPBqJ",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ek_new__okay)
{
    ek_new command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ek-new",
        "--uncompressed",
        "--version", "42",
        "passphrasecpXbDpHuo8F7yuZqR49koDA9uQojPijjjZaxsar7Woo9pfHJbeWF3VMU9EPBqJ",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ek_public__okay)
{
    ek_public command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ek-public",
        "--uncompressed",
        "--version", "42",
        "passphrasecpXbDpHuo8F7yuZqR49koDA9uQojPijjjZaxsar7Woo9pfHJbeWF3VMU9EPBqJ",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ek_public_to_address__okay)
{
    ek_public_to_address command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ek-public-to-address",
        "string",
        "cfrm38V8aXBn7JWA1ESmFMUn6erxeBGZGAxJPY4e36S9QWkzZKtaVqLNMgnifETYw7BPwWC9aPD",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ek_public_to_ec__okay)
{
    ek_public_to_ec command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ek-public-to-ec",
        "string",
        "cfrm38V8aXBn7JWA1ESmFMUn6erxeBGZGAxJPY4e36S9QWkzZKtaVqLNMgnifETYw7BPwWC9aPD",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ek_to_address__okay)
{
    ek_to_address command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ek-to-address",
        "string",
        "6PRVWUbkzzsbcVac2qwfssoUJAN1Xhrg6bNk8J7Nzm5H7kxEbn2Nh2ZoGg",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ek_to_ec__okay)
{
    ek_to_ec command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ek-to-ec",
        "string",
        "6PRVWUbkzzsbcVac2qwfssoUJAN1Xhrg6bNk8J7Nzm5H7kxEbn2Nh2ZoGg",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__electrum_decode__okay)
{
    electrum_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "electrum-decode",
        "--language", "en",
        "string",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__electrum_new__okay)
{
    electrum_new command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "electrum-new",
        "--language", "en",
        "--prefix", "standard",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__electrum_to_prefix__okay)
{
    electrum_to_prefix command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "electrum-to-prefix",
        "string",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__electrum_to_seed__okay)
{
    electrum_to_seed command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "electrum-to-seed",
        "--language", "en",
        "--passphrase", "string",
        "string",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__electrum_v1_decode__okay)
{
    electrum_v1_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "electrum-v1-decode",
        "--language", "en",
        "string",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__electrum_v1_encode__okay)
{
    electrum_v1_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "electrum-v1-encode",
        "--language", "en",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__electrum_v1_to_seed__okay)
{
    electrum_v1_to_seed command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "electrum-v1-to-seed",
        "--language", "en",
        "string",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_balance__okay)
{
    fetch_balance command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-balance",
        "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "http://127.0.0.1:1",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_block__okay)
{
    fetch_block command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-block",
        "--hash", "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "--height", "42",
        "http://127.0.0.1:1",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_block_hashes__okay)
{
    fetch_block_hashes command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-block-hashes",
        "--hash", "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "--height", "42",
        "http://127.0.0.1:1",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_block_height__okay)
{
    fetch_block_height command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-block-height",
        "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "http://127.0.0.1:1",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_filter__okay)
{
    fetch_filter command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-filter",
        "--hash", "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "--height", "42",
        "--type", "42",
        "http://127.0.0.1:1",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 8, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_filter_checkpoint__okay)
{
    fetch_filter_checkpoint command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-filter-checkpoint",
        "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_filter_headers__okay)
{
    fetch_filter_headers command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-filter-headers",
        "--stop_hash", "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "--stop_height", "42",
        "42",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_header__okay)
{
    fetch_header command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-header",
        "--hash", "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "--height", "42",
        "http://127.0.0.1:1",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_height__okay)
{
    fetch_height command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-height",
        "http://127.0.0.1:1",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_history__okay)
{
    fetch_history command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-history",
        "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "http://127.0.0.1:1",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_public_key__okay)
{
    fetch_public_key command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-public-key",
        "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_tx__okay)
{
    fetch_tx command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-tx",
        "--witness",
        "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "http://127.0.0.1:1",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_tx_index__okay)
{
    fetch_tx_index command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-tx-index",
        "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "http://127.0.0.1:1",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__fetch_utxo__okay)
{
    fetch_utxo command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "fetch-utxo",
        "--algorithm", "greedy",
        "42",
        "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "http://127.0.0.1:1",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__get_filter_checkpoint__okay)
{
    get_filter_checkpoint command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "get-filter-checkpoint",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__get_filter_headers__okay)
{
    get_filter_headers command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "get-filter-headers",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__get_filters__okay)
{
    get_filters command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "get-filters",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__hd_new__okay)
{
    hd_new command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "hd-new",
        "--version", "42",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__hd_private__okay)
{
    hd_private command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "hd-private",
        "--hard",
        "--index", "42",
        "--secret_version", "42",
        "--public_version", "42",
        "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 9, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__hd_public__okay)
{
    hd_public command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "hd-public",
        "--hard",
        "--index", "42",
        "--secret_version", "42",
        "--public_version", "42",
        "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 9, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__hd_to_address__okay)
{
    hd_to_address command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "hd-to-address",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__hd_to_ec__okay)
{
    hd_to_ec command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "hd-to-ec",
        "--secret_version", "42",
        "--public_version", "42",
        "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__hd_to_public__okay)
{
    hd_to_public command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "hd-to-public",
        "--secret_version", "42",
        "--version", "42",
        "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__hd_to_wif__okay)
{
    hd_to_wif command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "hd-to-wif",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__help__okay)
{
    help command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "help",
        "string",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__input_set__okay)
{
    input_set command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "input-set",
        "--index", "42",
        "--witness", "[baadf00d] [beefcafe]",
        "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig",
        "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 7, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__input_sign__okay)
{
    input_sign command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "input-sign",
        "--anyone",
        "--index", "42",
        "--segwit",
        "--sign_type", "all",
        "--value", "42",
        "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475",
        "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig",
        "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 12, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__input_validate__okay)
{
    input_validate command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "input-validate",
        "--index", "42",
        "--segwit",
        "--value", "42",
        "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5",
        "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig",
        "3044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd01",
        "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 10, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__match_neutrino_address__okay)
{
    match_neutrino_address command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "match-neutrino-address",
        "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "baadf00d",
        "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__match_neutrino_script__okay)
{
    match_neutrino_script command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "match-neutrino-script",
        "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "baadf00d",
        "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__message_sign__okay)
{
    message_sign command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "message-sign",
        "KynK1v6fGwt2deK5axWUi4dStZzyuhrMbsYwk52kXM5LMivMMrQp",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__message_validate__okay)
{
    message_validate command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "message-validate",
        "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa",
        "HxQp3cXgOIhBEGXks27sfeSQHVgNUeYgl5i5wG/dOUYaSIRnnzXR6NcyH+AfNAHtkWcyOD9rX4pojqmuQyH79K4=",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__mnemonic_decode__okay)
{
    mnemonic_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "mnemonic-decode",
        "--language", "en",
        "string",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__mnemonic_encode__okay)
{
    mnemonic_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "mnemonic-encode",
        "--language", "en",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__mnemonic_to_seed__okay)
{
    mnemonic_to_seed command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "mnemonic-to-seed",
        "--language", "en",
        "--passphrase", "string",
        "string",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 6, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__put_tx__okay)
{
    put_tx command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "put-tx",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__qrcode__okay)
{
    qrcode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "qrcode",
        "--margin", "42",
        "--pixels", "42",
        "--version", "42",
        "string",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 8, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__ripemd160__okay)
{
    ripemd160 command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "ripemd160",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__satoshi_to_btc__okay)
{
    satoshi_to_btc command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "satoshi-to-btc",
        "42",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__script_decode__okay)
{
    script_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "script-decode",
        "--flags", "42",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__script_encode__okay)
{
    script_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "script-encode",
        "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__script_to_address__okay)
{
    script_to_address command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "script-to-address",
        "--version", "42",
        "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__script_to_key__okay)
{
    script_to_key command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "script-to-key",
        "--version", "42",
        "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__script_to_witness__okay)
{
    script_to_witness command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "script-to-witness",
        "string",
        "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__seed__okay)
{
    seed command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "seed",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__send_tx__okay)
{
    send_tx command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "send-tx",
        "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__settings__okay)
{
    settings command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "settings",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__sha160__okay)
{
    sha160 command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "sha160",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__sha256__okay)
{
    sha256 command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "sha256",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__sha512__okay)
{
    sha512 command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "sha512",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__slip39_combine__okay)
{
    slip39_combine command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "slip39-combine",
        "--passphrase", "string",
        "duckling enlarge academic academic agency result length solution fridge kidney coal piece deal husband erode duke ajar critical decision keyboard",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__slip39_decode__okay)
{
    slip39_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "slip39-decode",
        "duckling enlarge academic academic agency result length solution fridge kidney coal piece deal husband erode duke ajar critical decision keyboard",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__slip39_split__okay)
{
    slip39_split command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "slip39-split",
        "--exponent", "42",
        "--group", "2/3",
        "--identifier", "42",
        "--passphrase", "string",
        "--secret", "baadf00d",
        "--threshold", "42",
        "--unextendable",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 15, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__stealth_public__okay)
{
    stealth_public command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "stealth-public",
        "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5",
        "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__stealth_secret__okay)
{
    stealth_secret command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "stealth-secret",
        "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475",
        "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__stealth_shared__okay)
{
    stealth_shared command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "stealth-shared",
        "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475",
        "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__subscribe_block__okay)
{
    subscribe_block command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "subscribe-block",
        "--duration", "42",
        "string",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__subscribe_tx__okay)
{
    subscribe_tx command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "subscribe-tx",
        "--duration", "42",
        "string",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__tls_cert__okay)
{
    tls_cert command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "tls-cert",
        "--name", "string",
        "--host", "string",
        "--ip", "string",
        "--not_before", "42",
        "--days", "42",
        "string",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 12, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__tls_new__okay)
{
    tls_new command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "tls-new",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__token_new__okay)
{
    token_new command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "token-new",
        "--lot", "42",
        "--sequence", "42",
        "string",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 7, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__tx_decode__okay)
{
    tx_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "tx-decode",
        "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__tx_encode__okay)
{
    tx_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "tx-encode",
        "--lock_time", "42",
        "--version", "42",
        "--input", "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b:0:4294967295",
        "--output", "[baadf00d]:42",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 9, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__tx_sign__okay)
{
    tx_sign command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "tx-sign",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__uri_decode__okay)
{
    uri_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "uri-decode",
        "bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__uri_encode__okay)
{
    uri_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "uri-encode",
        "--amount", "42.42",
        "--label", "string",
        "--message", "string",
        "--request", "string",
        "1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 10, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__validate_tx__okay)
{
    validate_tx command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "validate-tx",
        "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__version__okay)
{
    version command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "version",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__watch_key__okay)
{
    watch_key command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "watch-key",
        "--duration", "42",
        "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 4, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__watch_tx__okay)
{
    watch_tx command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "watch-tx",
        "--duration", "42",
        "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
        "http://127.0.0.1:1",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 5, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__wif_to_ec__okay)
{
    wif_to_ec command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "wif-to-ec",
        "KynK1v6fGwt2deK5axWUi4dStZzyuhrMbsYwk52kXM5LMivMMrQp",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__wif_to_public__okay)
{
    wif_to_public command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "wif-to-public",
        "KynK1v6fGwt2deK5axWUi4dStZzyuhrMbsYwk52kXM5LMivMMrQp",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__witness_decode__okay)
{
    witness_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "witness-decode",
        "--prefix",
        "baadf00d",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__witness_encode__okay)
{
    witness_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "witness-encode",
        "--prefix",
        "[baadf00d] [beefcafe]",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 3, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__witness_to_key__okay)
{
    witness_to_key command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "witness-to-key",
        "bc1qw508d6qejxtdg4y5r3zarvary0c5xw7kv8f3t4",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__witness_to_script__okay)
{
    witness_to_script command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "witness-to-script",
        "bc1qw508d6qejxtdg4y5r3zarvary0c5xw7kv8f3t4",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__wrap_decode__okay)
{
    wrap_decode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "wrap-decode",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(generated__parse__wrap_encode__okay)
{
    wrap_encode command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "wrap-encode",
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
