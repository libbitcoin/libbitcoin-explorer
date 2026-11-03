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

template <typename Value>
static std::string serial(const Value& value)
{
    std::ostringstream text;
    text << value;
    return text.str();
}

template <typename Value>
static std::string serial(const std::vector<Value>& values)
{
    std::ostringstream text;
    for (const auto& value: values)
        text << value;

    return text.str();
}

BC_AUTO_TEST_SUITE(generated)
BC_AUTO_TEST_SUITE(generated__property)

BC_AUTO_TEST_CASE(generated__property__address_decode__round_trips)
{
    address_decode command;

    const system::wallet::payment_address payment_address_argument{ "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa" };
    command.set_payment_address_argument(payment_address_argument);
    BC_REQUIRE_EQUAL(serial(command.get_payment_address_argument()), serial(payment_address_argument));
}

BC_AUTO_TEST_CASE(generated__property__address_embed__round_trips)
{
    address_embed command;

    const explorer::config::bytes data_argument{ "baadf00d" };
    command.set_data_argument(data_argument);
    BC_REQUIRE_EQUAL(serial(command.get_data_argument()), serial(data_argument));

    const explorer::config::byte version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__address_encode__round_trips)
{
    address_encode command;

    const system::config::hash160 ripemd160_argument{ "b472a266d0bd89c13706a4132ccfb16f7c3b9fcb" };
    command.set_ripemd160_argument(ripemd160_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ripemd160_argument()), serial(ripemd160_argument));

    const explorer::config::byte version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__address_to_key__round_trips)
{
    address_to_key command;

    const system::wallet::payment_address payment_address_argument{ "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa" };
    command.set_payment_address_argument(payment_address_argument);
    BC_REQUIRE_EQUAL(serial(command.get_payment_address_argument()), serial(payment_address_argument));
}

BC_AUTO_TEST_CASE(generated__property__base16_decode__round_trips)
{
    base16_decode command;

    const system::config::base16 base16_argument{ "baadf00d" };
    command.set_base16_argument(base16_argument);
    BC_REQUIRE_EQUAL(serial(command.get_base16_argument()), serial(base16_argument));
}

BC_AUTO_TEST_CASE(generated__property__base16_encode__round_trips)
{
    base16_encode command;

    const explorer::config::bytes data_argument{ "baadf00d" };
    command.set_data_argument(data_argument);
    BC_REQUIRE_EQUAL(serial(command.get_data_argument()), serial(data_argument));
}

BC_AUTO_TEST_CASE(generated__property__base32_decode__round_trips)
{
    base32_decode command;

    const system::config::base32 base32_argument{ "MJQWCZDGGAYGI===" };
    command.set_base32_argument(base32_argument);
    BC_REQUIRE_EQUAL(serial(command.get_base32_argument()), serial(base32_argument));
}

BC_AUTO_TEST_CASE(generated__property__base32_encode__round_trips)
{
    base32_encode command;

    const explorer::config::bytes data_argument{ "baadf00d" };
    command.set_data_argument(data_argument);
    BC_REQUIRE_EQUAL(serial(command.get_data_argument()), serial(data_argument));
}

BC_AUTO_TEST_CASE(generated__property__base58_decode__round_trips)
{
    base58_decode command;

    const system::config::base58 base58_argument{ "5mm7zk" };
    command.set_base58_argument(base58_argument);
    BC_REQUIRE_EQUAL(serial(command.get_base58_argument()), serial(base58_argument));
}

BC_AUTO_TEST_CASE(generated__property__base58_encode__round_trips)
{
    base58_encode command;

    const system::config::base16 base16_argument{ "baadf00d" };
    command.set_base16_argument(base16_argument);
    BC_REQUIRE_EQUAL(serial(command.get_base16_argument()), serial(base16_argument));
}

BC_AUTO_TEST_CASE(generated__property__base64_decode__round_trips)
{
    base64_decode command;

    const system::config::base64 base64_argument{ "YmFhZGYwMGQ=" };
    command.set_base64_argument(base64_argument);
    BC_REQUIRE_EQUAL(serial(command.get_base64_argument()), serial(base64_argument));
}

BC_AUTO_TEST_CASE(generated__property__base64_encode__round_trips)
{
    base64_encode command;

    const explorer::config::bytes data_argument{ "baadf00d" };
    command.set_data_argument(data_argument);
    BC_REQUIRE_EQUAL(serial(command.get_data_argument()), serial(data_argument));
}

BC_AUTO_TEST_CASE(generated__property__bech32_decode__round_trips)
{
    bech32_decode command;

    const system::config::base16 checked_argument{ "baadf00d" };
    command.set_checked_argument(checked_argument);
    BC_REQUIRE_EQUAL(serial(command.get_checked_argument()), serial(checked_argument));
}

BC_AUTO_TEST_CASE(generated__property__bech32_encode__round_trips)
{
    bech32_encode command;

    const std::string prefix_argument{ "string" };
    command.set_prefix_argument(prefix_argument);
    BC_REQUIRE_EQUAL(serial(command.get_prefix_argument()), serial(prefix_argument));

    const system::config::base16 program_argument{ "baadf00d" };
    command.set_program_argument(program_argument);
    BC_REQUIRE_EQUAL(serial(command.get_program_argument()), serial(program_argument));

    const explorer::config::byte version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__bitcoin160__round_trips)
{
    bitcoin160 command;

    const system::config::base16 base16_argument{ "baadf00d" };
    command.set_base16_argument(base16_argument);
    BC_REQUIRE_EQUAL(serial(command.get_base16_argument()), serial(base16_argument));
}

BC_AUTO_TEST_CASE(generated__property__bitcoin256__round_trips)
{
    bitcoin256 command;

    const system::config::base16 base16_argument{ "baadf00d" };
    command.set_base16_argument(base16_argument);
    BC_REQUIRE_EQUAL(serial(command.get_base16_argument()), serial(base16_argument));
}

BC_AUTO_TEST_CASE(generated__property__broadcast_tx__round_trips)
{
    broadcast_tx command;

    const system::config::transaction transaction_argument{ "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000" };
    command.set_transaction_argument(transaction_argument);
    BC_REQUIRE_EQUAL(serial(command.get_transaction_argument()), serial(transaction_argument));

    const size_t nodes_option{ 42 };
    command.set_nodes_option(nodes_option);
    BC_REQUIRE_EQUAL(serial(command.get_nodes_option()), serial(nodes_option));
}

BC_AUTO_TEST_CASE(generated__property__btc_to_satoshi__round_trips)
{
    btc_to_satoshi command;

    const explorer::config::btc btc_argument{ "42.42" };
    command.set_btc_argument(btc_argument);
    BC_REQUIRE_EQUAL(serial(command.get_btc_argument()), serial(btc_argument));
}

BC_AUTO_TEST_CASE(generated__property__cert_public__round_trips)
{
    cert_public command;

    const system::config::base85 private_key_argument{ "HelloWorld" };
    command.set_private_key_argument(private_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_private_key_argument()), serial(private_key_argument));
}

BC_AUTO_TEST_CASE(generated__property__checked_decode__round_trips)
{
    checked_decode command;

    const system::config::base16 checked_argument{ "baadf00d" };
    command.set_checked_argument(checked_argument);
    BC_REQUIRE_EQUAL(serial(command.get_checked_argument()), serial(checked_argument));
}

BC_AUTO_TEST_CASE(generated__property__checked_encode__round_trips)
{
    checked_encode command;

    const system::config::base16 payload_argument{ "baadf00d" };
    command.set_payload_argument(payload_argument);
    BC_REQUIRE_EQUAL(serial(command.get_payload_argument()), serial(payload_argument));

    const explorer::config::byte version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__dice_entropy__round_trips)
{
    dice_entropy command;

    const std::string rolls_argument{ "string" };
    command.set_rolls_argument(rolls_argument);
    BC_REQUIRE_EQUAL(serial(command.get_rolls_argument()), serial(rolls_argument));

    const uint8_t sides_option{ 42 };
    command.set_sides_option(sides_option);
    BC_REQUIRE_EQUAL(serial(command.get_sides_option()), serial(sides_option));
}

BC_AUTO_TEST_CASE(generated__property__ec_add__round_trips)
{
    ec_add command;

    const system::wallet::ec_public point_argument{ "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5" };
    command.set_point_argument(point_argument);
    BC_REQUIRE_EQUAL(serial(command.get_point_argument()), serial(point_argument));

    const explorer::config::ec_private secret_argument{ "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" };
    command.set_secret_argument(secret_argument);
    BC_REQUIRE_EQUAL(serial(command.get_secret_argument()), serial(secret_argument));
}

BC_AUTO_TEST_CASE(generated__property__ec_add_secrets__round_trips)
{
    ec_add_secrets command;

    const std::vector<explorer::config::ec_private> secrets_argument{ { "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" } };
    command.set_secrets_argument(secrets_argument);
    BC_REQUIRE_EQUAL(serial(command.get_secrets_argument()), serial(secrets_argument));
}

BC_AUTO_TEST_CASE(generated__property__ec_decompress__round_trips)
{
    ec_decompress command;

    const system::wallet::ec_public ec_public_key_argument{ "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5" };
    command.set_ec_public_key_argument(ec_public_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ec_public_key_argument()), serial(ec_public_key_argument));
}

BC_AUTO_TEST_CASE(generated__property__ec_multiply__round_trips)
{
    ec_multiply command;

    const system::wallet::ec_public point_argument{ "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5" };
    command.set_point_argument(point_argument);
    BC_REQUIRE_EQUAL(serial(command.get_point_argument()), serial(point_argument));

    const explorer::config::ec_private secret_argument{ "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" };
    command.set_secret_argument(secret_argument);
    BC_REQUIRE_EQUAL(serial(command.get_secret_argument()), serial(secret_argument));
}

BC_AUTO_TEST_CASE(generated__property__ec_multiply_secrets__round_trips)
{
    ec_multiply_secrets command;

    const std::vector<explorer::config::ec_private> secrets_argument{ { "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" } };
    command.set_secrets_argument(secrets_argument);
    BC_REQUIRE_EQUAL(serial(command.get_secrets_argument()), serial(secrets_argument));
}

BC_AUTO_TEST_CASE(generated__property__ec_new__round_trips)
{
    ec_new command;

    const system::config::base16 entropy_argument{ "baadf00d" };
    command.set_entropy_argument(entropy_argument);
    BC_REQUIRE_EQUAL(serial(command.get_entropy_argument()), serial(entropy_argument));
}

BC_AUTO_TEST_CASE(generated__property__ec_to_address__round_trips)
{
    ec_to_address command;

    const system::wallet::ec_public ec_public_key_argument{ "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5" };
    command.set_ec_public_key_argument(ec_public_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ec_public_key_argument()), serial(ec_public_key_argument));

    const explorer::config::byte version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__ec_to_ek__round_trips)
{
    ec_to_ek command;

    const std::string passphrase_argument{ "string" };
    command.set_passphrase_argument(passphrase_argument);
    BC_REQUIRE_EQUAL(serial(command.get_passphrase_argument()), serial(passphrase_argument));

    const explorer::config::ec_private ec_private_key_argument{ "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" };
    command.set_ec_private_key_argument(ec_private_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ec_private_key_argument()), serial(ec_private_key_argument));

    const bool uncompressed_option{ true };
    command.set_uncompressed_option(uncompressed_option);
    BC_REQUIRE_EQUAL(serial(command.get_uncompressed_option()), serial(uncompressed_option));

    const explorer::config::byte version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__ec_to_public__round_trips)
{
    ec_to_public command;

    const explorer::config::ec_private ec_private_key_argument{ "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" };
    command.set_ec_private_key_argument(ec_private_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ec_private_key_argument()), serial(ec_private_key_argument));

    const bool uncompressed_option{ true };
    command.set_uncompressed_option(uncompressed_option);
    BC_REQUIRE_EQUAL(serial(command.get_uncompressed_option()), serial(uncompressed_option));
}

BC_AUTO_TEST_CASE(generated__property__ec_to_wif__round_trips)
{
    ec_to_wif command;

    const explorer::config::ec_private ec_private_key_argument{ "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" };
    command.set_ec_private_key_argument(ec_private_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ec_private_key_argument()), serial(ec_private_key_argument));

    const bool uncompressed_option{ true };
    command.set_uncompressed_option(uncompressed_option);
    BC_REQUIRE_EQUAL(serial(command.get_uncompressed_option()), serial(uncompressed_option));

    const explorer::config::byte version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__ec_to_witness__round_trips)
{
    ec_to_witness command;

    const std::string prefix_argument{ "string" };
    command.set_prefix_argument(prefix_argument);
    BC_REQUIRE_EQUAL(serial(command.get_prefix_argument()), serial(prefix_argument));

    const system::wallet::ec_public ec_public_key_argument{ "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5" };
    command.set_ec_public_key_argument(ec_public_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ec_public_key_argument()), serial(ec_public_key_argument));
}

BC_AUTO_TEST_CASE(generated__property__ek_address__round_trips)
{
    ek_address command;

    const system::wallet::ek_token token_argument{ "passphrasecpXbDpHuo8F7yuZqR49koDA9uQojPijjjZaxsar7Woo9pfHJbeWF3VMU9EPBqJ" };
    command.set_token_argument(token_argument);
    BC_REQUIRE_EQUAL(serial(command.get_token_argument()), serial(token_argument));

    const system::config::base16 entropy_argument{ "baadf00d" };
    command.set_entropy_argument(entropy_argument);
    BC_REQUIRE_EQUAL(serial(command.get_entropy_argument()), serial(entropy_argument));

    const bool uncompressed_option{ true };
    command.set_uncompressed_option(uncompressed_option);
    BC_REQUIRE_EQUAL(serial(command.get_uncompressed_option()), serial(uncompressed_option));

    const explorer::config::byte version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__ek_new__round_trips)
{
    ek_new command;

    const system::wallet::ek_token token_argument{ "passphrasecpXbDpHuo8F7yuZqR49koDA9uQojPijjjZaxsar7Woo9pfHJbeWF3VMU9EPBqJ" };
    command.set_token_argument(token_argument);
    BC_REQUIRE_EQUAL(serial(command.get_token_argument()), serial(token_argument));

    const system::config::base16 entropy_argument{ "baadf00d" };
    command.set_entropy_argument(entropy_argument);
    BC_REQUIRE_EQUAL(serial(command.get_entropy_argument()), serial(entropy_argument));

    const bool uncompressed_option{ true };
    command.set_uncompressed_option(uncompressed_option);
    BC_REQUIRE_EQUAL(serial(command.get_uncompressed_option()), serial(uncompressed_option));

    const explorer::config::byte version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__ek_public__round_trips)
{
    ek_public command;

    const system::wallet::ek_token token_argument{ "passphrasecpXbDpHuo8F7yuZqR49koDA9uQojPijjjZaxsar7Woo9pfHJbeWF3VMU9EPBqJ" };
    command.set_token_argument(token_argument);
    BC_REQUIRE_EQUAL(serial(command.get_token_argument()), serial(token_argument));

    const system::config::base16 entropy_argument{ "baadf00d" };
    command.set_entropy_argument(entropy_argument);
    BC_REQUIRE_EQUAL(serial(command.get_entropy_argument()), serial(entropy_argument));

    const bool uncompressed_option{ true };
    command.set_uncompressed_option(uncompressed_option);
    BC_REQUIRE_EQUAL(serial(command.get_uncompressed_option()), serial(uncompressed_option));

    const explorer::config::byte version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__ek_public_to_address__round_trips)
{
    ek_public_to_address command;

    const std::string passphrase_argument{ "string" };
    command.set_passphrase_argument(passphrase_argument);
    BC_REQUIRE_EQUAL(serial(command.get_passphrase_argument()), serial(passphrase_argument));

    const system::wallet::ek_public ek_public_key_argument{ "cfrm38V8aXBn7JWA1ESmFMUn6erxeBGZGAxJPY4e36S9QWkzZKtaVqLNMgnifETYw7BPwWC9aPD" };
    command.set_ek_public_key_argument(ek_public_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ek_public_key_argument()), serial(ek_public_key_argument));
}

BC_AUTO_TEST_CASE(generated__property__ek_public_to_ec__round_trips)
{
    ek_public_to_ec command;

    const std::string passphrase_argument{ "string" };
    command.set_passphrase_argument(passphrase_argument);
    BC_REQUIRE_EQUAL(serial(command.get_passphrase_argument()), serial(passphrase_argument));

    const system::wallet::ek_public ek_public_key_argument{ "cfrm38V8aXBn7JWA1ESmFMUn6erxeBGZGAxJPY4e36S9QWkzZKtaVqLNMgnifETYw7BPwWC9aPD" };
    command.set_ek_public_key_argument(ek_public_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ek_public_key_argument()), serial(ek_public_key_argument));
}

BC_AUTO_TEST_CASE(generated__property__ek_to_address__round_trips)
{
    ek_to_address command;

    const std::string passphrase_argument{ "string" };
    command.set_passphrase_argument(passphrase_argument);
    BC_REQUIRE_EQUAL(serial(command.get_passphrase_argument()), serial(passphrase_argument));

    const system::wallet::ek_private ek_private_key_argument{ "6PRVWUbkzzsbcVac2qwfssoUJAN1Xhrg6bNk8J7Nzm5H7kxEbn2Nh2ZoGg" };
    command.set_ek_private_key_argument(ek_private_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ek_private_key_argument()), serial(ek_private_key_argument));
}

BC_AUTO_TEST_CASE(generated__property__ek_to_ec__round_trips)
{
    ek_to_ec command;

    const std::string passphrase_argument{ "string" };
    command.set_passphrase_argument(passphrase_argument);
    BC_REQUIRE_EQUAL(serial(command.get_passphrase_argument()), serial(passphrase_argument));

    const system::wallet::ek_private ek_private_key_argument{ "6PRVWUbkzzsbcVac2qwfssoUJAN1Xhrg6bNk8J7Nzm5H7kxEbn2Nh2ZoGg" };
    command.set_ek_private_key_argument(ek_private_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ek_private_key_argument()), serial(ek_private_key_argument));
}

BC_AUTO_TEST_CASE(generated__property__electrum_decode__round_trips)
{
    electrum_decode command;

    const std::vector<std::string> words_argument{ { "string" } };
    command.set_words_argument(words_argument);
    BC_REQUIRE_EQUAL(serial(command.get_words_argument()), serial(words_argument));

    const explorer::config::language language_option{ "en" };
    command.set_language_option(language_option);
    BC_REQUIRE_EQUAL(serial(command.get_language_option()), serial(language_option));
}

BC_AUTO_TEST_CASE(generated__property__electrum_new__round_trips)
{
    electrum_new command;

    const system::config::base16 entropy_argument{ "baadf00d" };
    command.set_entropy_argument(entropy_argument);
    BC_REQUIRE_EQUAL(serial(command.get_entropy_argument()), serial(entropy_argument));

    const explorer::config::language language_option{ "en" };
    command.set_language_option(language_option);
    BC_REQUIRE_EQUAL(serial(command.get_language_option()), serial(language_option));

    const explorer::config::electrum prefix_option{ "standard" };
    command.set_prefix_option(prefix_option);
    BC_REQUIRE_EQUAL(serial(command.get_prefix_option()), serial(prefix_option));
}

BC_AUTO_TEST_CASE(generated__property__electrum_to_seed__round_trips)
{
    electrum_to_seed command;

    const std::vector<std::string> words_argument{ { "string" } };
    command.set_words_argument(words_argument);
    BC_REQUIRE_EQUAL(serial(command.get_words_argument()), serial(words_argument));

    const explorer::config::language language_option{ "en" };
    command.set_language_option(language_option);
    BC_REQUIRE_EQUAL(serial(command.get_language_option()), serial(language_option));

    const std::string passphrase_option{ "string" };
    command.set_passphrase_option(passphrase_option);
    BC_REQUIRE_EQUAL(serial(command.get_passphrase_option()), serial(passphrase_option));
}

BC_AUTO_TEST_CASE(generated__property__fetch_balance__round_trips)
{
    fetch_balance command;

    const system::config::url server_url_argument{ "http://127.0.0.1:1" };
    command.set_server_url_argument(server_url_argument);
    BC_REQUIRE_EQUAL(serial(command.get_server_url_argument()), serial(server_url_argument));

    const system::config::hash256 hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_argument(hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hash_argument()), serial(hash_argument));
}

BC_AUTO_TEST_CASE(generated__property__fetch_block__round_trips)
{
    fetch_block command;

    const system::config::url server_url_argument{ "http://127.0.0.1:1" };
    command.set_server_url_argument(server_url_argument);
    BC_REQUIRE_EQUAL(serial(command.get_server_url_argument()), serial(server_url_argument));

    const system::config::hash256 hash_option{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_option(hash_option);
    BC_REQUIRE_EQUAL(serial(command.get_hash_option()), serial(hash_option));

    const uint32_t height_option{ 42 };
    command.set_height_option(height_option);
    BC_REQUIRE_EQUAL(serial(command.get_height_option()), serial(height_option));
}

BC_AUTO_TEST_CASE(generated__property__fetch_block_hashes__round_trips)
{
    fetch_block_hashes command;

    const system::config::url server_url_argument{ "http://127.0.0.1:1" };
    command.set_server_url_argument(server_url_argument);
    BC_REQUIRE_EQUAL(serial(command.get_server_url_argument()), serial(server_url_argument));

    const system::config::hash256 hash_option{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_option(hash_option);
    BC_REQUIRE_EQUAL(serial(command.get_hash_option()), serial(hash_option));

    const uint32_t height_option{ 42 };
    command.set_height_option(height_option);
    BC_REQUIRE_EQUAL(serial(command.get_height_option()), serial(height_option));
}

BC_AUTO_TEST_CASE(generated__property__fetch_block_height__round_trips)
{
    fetch_block_height command;

    const system::config::hash256 hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_argument(hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hash_argument()), serial(hash_argument));

    const system::config::url server_url_argument{ "http://127.0.0.1:1" };
    command.set_server_url_argument(server_url_argument);
    BC_REQUIRE_EQUAL(serial(command.get_server_url_argument()), serial(server_url_argument));
}

BC_AUTO_TEST_CASE(generated__property__fetch_filter__round_trips)
{
    fetch_filter command;

    const system::config::url server_url_argument{ "http://127.0.0.1:1" };
    command.set_server_url_argument(server_url_argument);
    BC_REQUIRE_EQUAL(serial(command.get_server_url_argument()), serial(server_url_argument));

    const system::config::hash256 hash_option{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_option(hash_option);
    BC_REQUIRE_EQUAL(serial(command.get_hash_option()), serial(hash_option));

    const uint32_t height_option{ 42 };
    command.set_height_option(height_option);
    BC_REQUIRE_EQUAL(serial(command.get_height_option()), serial(height_option));

    const uint8_t type_option{ 42 };
    command.set_type_option(type_option);
    BC_REQUIRE_EQUAL(serial(command.get_type_option()), serial(type_option));
}

BC_AUTO_TEST_CASE(generated__property__fetch_filter_checkpoint__round_trips)
{
    fetch_filter_checkpoint command;

    const system::config::hash256 hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_argument(hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hash_argument()), serial(hash_argument));
}

BC_AUTO_TEST_CASE(generated__property__fetch_filter_headers__round_trips)
{
    fetch_filter_headers command;

    const uint32_t start_height_argument{ 42 };
    command.set_start_height_argument(start_height_argument);
    BC_REQUIRE_EQUAL(serial(command.get_start_height_argument()), serial(start_height_argument));

    const system::config::hash256 stop_hash_option{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_stop_hash_option(stop_hash_option);
    BC_REQUIRE_EQUAL(serial(command.get_stop_hash_option()), serial(stop_hash_option));

    const uint32_t stop_height_option{ 42 };
    command.set_stop_height_option(stop_height_option);
    BC_REQUIRE_EQUAL(serial(command.get_stop_height_option()), serial(stop_height_option));
}

BC_AUTO_TEST_CASE(generated__property__fetch_header__round_trips)
{
    fetch_header command;

    const system::config::url server_url_argument{ "http://127.0.0.1:1" };
    command.set_server_url_argument(server_url_argument);
    BC_REQUIRE_EQUAL(serial(command.get_server_url_argument()), serial(server_url_argument));

    const system::config::hash256 hash_option{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_option(hash_option);
    BC_REQUIRE_EQUAL(serial(command.get_hash_option()), serial(hash_option));

    const uint32_t height_option{ 42 };
    command.set_height_option(height_option);
    BC_REQUIRE_EQUAL(serial(command.get_height_option()), serial(height_option));
}

BC_AUTO_TEST_CASE(generated__property__fetch_height__round_trips)
{
    fetch_height command;

    const system::config::url server_url_argument{ "http://127.0.0.1:1" };
    command.set_server_url_argument(server_url_argument);
    BC_REQUIRE_EQUAL(serial(command.get_server_url_argument()), serial(server_url_argument));
}

BC_AUTO_TEST_CASE(generated__property__fetch_history__round_trips)
{
    fetch_history command;

    const system::config::url server_url_argument{ "http://127.0.0.1:1" };
    command.set_server_url_argument(server_url_argument);
    BC_REQUIRE_EQUAL(serial(command.get_server_url_argument()), serial(server_url_argument));

    const system::config::hash256 hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_argument(hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hash_argument()), serial(hash_argument));
}

BC_AUTO_TEST_CASE(generated__property__fetch_public_key__round_trips)
{
    fetch_public_key command;

    const system::config::hash256 hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_argument(hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hash_argument()), serial(hash_argument));
}

BC_AUTO_TEST_CASE(generated__property__fetch_tx__round_trips)
{
    fetch_tx command;

    const system::config::hash256 hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_argument(hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hash_argument()), serial(hash_argument));

    const system::config::url server_url_argument{ "http://127.0.0.1:1" };
    command.set_server_url_argument(server_url_argument);
    BC_REQUIRE_EQUAL(serial(command.get_server_url_argument()), serial(server_url_argument));

    const bool witness_option{ true };
    command.set_witness_option(witness_option);
    BC_REQUIRE_EQUAL(serial(command.get_witness_option()), serial(witness_option));
}

BC_AUTO_TEST_CASE(generated__property__fetch_tx_index__round_trips)
{
    fetch_tx_index command;

    const system::config::hash256 hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_argument(hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hash_argument()), serial(hash_argument));

    const system::config::url server_url_argument{ "http://127.0.0.1:1" };
    command.set_server_url_argument(server_url_argument);
    BC_REQUIRE_EQUAL(serial(command.get_server_url_argument()), serial(server_url_argument));
}

BC_AUTO_TEST_CASE(generated__property__fetch_utxo__round_trips)
{
    fetch_utxo command;

    const uint64_t satoshi_argument{ 42 };
    command.set_satoshi_argument(satoshi_argument);
    BC_REQUIRE_EQUAL(serial(command.get_satoshi_argument()), serial(satoshi_argument));

    const system::config::hash256 hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_argument(hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hash_argument()), serial(hash_argument));

    const explorer::config::algorithm algorithm_option{ "greedy" };
    command.set_algorithm_option(algorithm_option);
    BC_REQUIRE_EQUAL(serial(command.get_algorithm_option()), serial(algorithm_option));
}

BC_AUTO_TEST_CASE(generated__property__get_filter_checkpoint__round_trips)
{
    get_filter_checkpoint command;

    const system::config::hash256 hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_argument(hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hash_argument()), serial(hash_argument));

    const std::string host_option{ "string" };
    command.set_host_option(host_option);
    BC_REQUIRE_EQUAL(serial(command.get_host_option()), serial(host_option));

    const uint16_t port_option{ 42 };
    command.set_port_option(port_option);
    BC_REQUIRE_EQUAL(serial(command.get_port_option()), serial(port_option));
}

BC_AUTO_TEST_CASE(generated__property__get_filter_headers__round_trips)
{
    get_filter_headers command;

    const uint32_t height_argument{ 42 };
    command.set_height_argument(height_argument);
    BC_REQUIRE_EQUAL(serial(command.get_height_argument()), serial(height_argument));

    const system::config::hash256 hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_argument(hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hash_argument()), serial(hash_argument));

    const std::string host_option{ "string" };
    command.set_host_option(host_option);
    BC_REQUIRE_EQUAL(serial(command.get_host_option()), serial(host_option));

    const uint16_t port_option{ 42 };
    command.set_port_option(port_option);
    BC_REQUIRE_EQUAL(serial(command.get_port_option()), serial(port_option));
}

BC_AUTO_TEST_CASE(generated__property__get_filters__round_trips)
{
    get_filters command;

    const uint32_t height_argument{ 42 };
    command.set_height_argument(height_argument);
    BC_REQUIRE_EQUAL(serial(command.get_height_argument()), serial(height_argument));

    const system::config::hash256 hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_argument(hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hash_argument()), serial(hash_argument));

    const std::string host_option{ "string" };
    command.set_host_option(host_option);
    BC_REQUIRE_EQUAL(serial(command.get_host_option()), serial(host_option));

    const uint16_t port_option{ 42 };
    command.set_port_option(port_option);
    BC_REQUIRE_EQUAL(serial(command.get_port_option()), serial(port_option));
}

BC_AUTO_TEST_CASE(generated__property__hd_new__round_trips)
{
    hd_new command;

    const system::config::base16 entropy_argument{ "baadf00d" };
    command.set_entropy_argument(entropy_argument);
    BC_REQUIRE_EQUAL(serial(command.get_entropy_argument()), serial(entropy_argument));

    const uint32_t version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__hd_private__round_trips)
{
    hd_private command;

    const explorer::config::hd_key hd_key_argument{ "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi" };
    command.set_hd_key_argument(hd_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hd_key_argument()), serial(hd_key_argument));

    const bool hard_option{ true };
    command.set_hard_option(hard_option);
    BC_REQUIRE_EQUAL(serial(command.get_hard_option()), serial(hard_option));

    const uint32_t index_option{ 42 };
    command.set_index_option(index_option);
    BC_REQUIRE_EQUAL(serial(command.get_index_option()), serial(index_option));

    const uint32_t secret_version_option{ 42 };
    command.set_secret_version_option(secret_version_option);
    BC_REQUIRE_EQUAL(serial(command.get_secret_version_option()), serial(secret_version_option));

    const uint32_t public_version_option{ 42 };
    command.set_public_version_option(public_version_option);
    BC_REQUIRE_EQUAL(serial(command.get_public_version_option()), serial(public_version_option));
}

BC_AUTO_TEST_CASE(generated__property__hd_public__round_trips)
{
    hd_public command;

    const explorer::config::hd_key hd_key_argument{ "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi" };
    command.set_hd_key_argument(hd_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hd_key_argument()), serial(hd_key_argument));

    const bool hard_option{ true };
    command.set_hard_option(hard_option);
    BC_REQUIRE_EQUAL(serial(command.get_hard_option()), serial(hard_option));

    const uint32_t index_option{ 42 };
    command.set_index_option(index_option);
    BC_REQUIRE_EQUAL(serial(command.get_index_option()), serial(index_option));

    const uint32_t secret_version_option{ 42 };
    command.set_secret_version_option(secret_version_option);
    BC_REQUIRE_EQUAL(serial(command.get_secret_version_option()), serial(secret_version_option));

    const uint32_t public_version_option{ 42 };
    command.set_public_version_option(public_version_option);
    BC_REQUIRE_EQUAL(serial(command.get_public_version_option()), serial(public_version_option));
}

BC_AUTO_TEST_CASE(generated__property__hd_to_ec__round_trips)
{
    hd_to_ec command;

    const explorer::config::hd_key hd_key_argument{ "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi" };
    command.set_hd_key_argument(hd_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hd_key_argument()), serial(hd_key_argument));

    const uint32_t secret_version_option{ 42 };
    command.set_secret_version_option(secret_version_option);
    BC_REQUIRE_EQUAL(serial(command.get_secret_version_option()), serial(secret_version_option));

    const uint32_t public_version_option{ 42 };
    command.set_public_version_option(public_version_option);
    BC_REQUIRE_EQUAL(serial(command.get_public_version_option()), serial(public_version_option));
}

BC_AUTO_TEST_CASE(generated__property__hd_to_public__round_trips)
{
    hd_to_public command;

    const explorer::config::hd_key hd_key_argument{ "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi" };
    command.set_hd_key_argument(hd_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hd_key_argument()), serial(hd_key_argument));

    const uint32_t secret_version_option{ 42 };
    command.set_secret_version_option(secret_version_option);
    BC_REQUIRE_EQUAL(serial(command.get_secret_version_option()), serial(secret_version_option));

    const uint32_t version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__help__round_trips)
{
    help command;

    const std::string command_argument{ "string" };
    command.set_command_argument(command_argument);
    BC_REQUIRE_EQUAL(serial(command.get_command_argument()), serial(command_argument));
}

BC_AUTO_TEST_CASE(generated__property__input_set__round_trips)
{
    input_set command;

    const system::config::script endorsement_script_argument{ "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig" };
    command.set_endorsement_script_argument(endorsement_script_argument);
    BC_REQUIRE_EQUAL(serial(command.get_endorsement_script_argument()), serial(endorsement_script_argument));

    const system::config::transaction transaction_argument{ "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000" };
    command.set_transaction_argument(transaction_argument);
    BC_REQUIRE_EQUAL(serial(command.get_transaction_argument()), serial(transaction_argument));

    const uint32_t index_option{ 42 };
    command.set_index_option(index_option);
    BC_REQUIRE_EQUAL(serial(command.get_index_option()), serial(index_option));
}

BC_AUTO_TEST_CASE(generated__property__input_sign__round_trips)
{
    input_sign command;

    const explorer::config::ec_private ec_private_key_argument{ "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" };
    command.set_ec_private_key_argument(ec_private_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ec_private_key_argument()), serial(ec_private_key_argument));

    const system::config::script contract_argument{ "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig" };
    command.set_contract_argument(contract_argument);
    BC_REQUIRE_EQUAL(serial(command.get_contract_argument()), serial(contract_argument));

    const system::config::transaction transaction_argument{ "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000" };
    command.set_transaction_argument(transaction_argument);
    BC_REQUIRE_EQUAL(serial(command.get_transaction_argument()), serial(transaction_argument));

    const bool anyone_option{ true };
    command.set_anyone_option(anyone_option);
    BC_REQUIRE_EQUAL(serial(command.get_anyone_option()), serial(anyone_option));

    const uint32_t index_option{ 42 };
    command.set_index_option(index_option);
    BC_REQUIRE_EQUAL(serial(command.get_index_option()), serial(index_option));

    const explorer::config::sighash sign_type_option{ "all" };
    command.set_sign_type_option(sign_type_option);
    BC_REQUIRE_EQUAL(serial(command.get_sign_type_option()), serial(sign_type_option));
}

BC_AUTO_TEST_CASE(generated__property__input_validate__round_trips)
{
    input_validate command;

    const system::wallet::ec_public ec_public_key_argument{ "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5" };
    command.set_ec_public_key_argument(ec_public_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ec_public_key_argument()), serial(ec_public_key_argument));

    const system::config::script contract_argument{ "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig" };
    command.set_contract_argument(contract_argument);
    BC_REQUIRE_EQUAL(serial(command.get_contract_argument()), serial(contract_argument));

    const explorer::config::endorsement endorsement_argument{ "3044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd01" };
    command.set_endorsement_argument(endorsement_argument);
    BC_REQUIRE_EQUAL(serial(command.get_endorsement_argument()), serial(endorsement_argument));

    const system::config::transaction transaction_argument{ "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000" };
    command.set_transaction_argument(transaction_argument);
    BC_REQUIRE_EQUAL(serial(command.get_transaction_argument()), serial(transaction_argument));

    const uint32_t index_option{ 42 };
    command.set_index_option(index_option);
    BC_REQUIRE_EQUAL(serial(command.get_index_option()), serial(index_option));
}

BC_AUTO_TEST_CASE(generated__property__match_neutrino_address__round_trips)
{
    match_neutrino_address command;

    const system::config::hash256 block_hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_block_hash_argument(block_hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_block_hash_argument()), serial(block_hash_argument));

    const system::config::base16 client_filter_argument{ "baadf00d" };
    command.set_client_filter_argument(client_filter_argument);
    BC_REQUIRE_EQUAL(serial(command.get_client_filter_argument()), serial(client_filter_argument));

    const system::wallet::payment_address address_argument{ "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa" };
    command.set_address_argument(address_argument);
    BC_REQUIRE_EQUAL(serial(command.get_address_argument()), serial(address_argument));
}

BC_AUTO_TEST_CASE(generated__property__match_neutrino_script__round_trips)
{
    match_neutrino_script command;

    const system::config::hash256 block_hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_block_hash_argument(block_hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_block_hash_argument()), serial(block_hash_argument));

    const system::config::base16 client_filter_argument{ "baadf00d" };
    command.set_client_filter_argument(client_filter_argument);
    BC_REQUIRE_EQUAL(serial(command.get_client_filter_argument()), serial(client_filter_argument));

    const system::config::script script_argument{ "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig" };
    command.set_script_argument(script_argument);
    BC_REQUIRE_EQUAL(serial(command.get_script_argument()), serial(script_argument));
}

BC_AUTO_TEST_CASE(generated__property__message_sign__round_trips)
{
    message_sign command;

    const system::wallet::ec_private wif_argument{ "KynK1v6fGwt2deK5axWUi4dStZzyuhrMbsYwk52kXM5LMivMMrQp" };
    command.set_wif_argument(wif_argument);
    BC_REQUIRE_EQUAL(serial(command.get_wif_argument()), serial(wif_argument));

    const explorer::config::bytes message_argument{ "baadf00d" };
    command.set_message_argument(message_argument);
    BC_REQUIRE_EQUAL(serial(command.get_message_argument()), serial(message_argument));
}

BC_AUTO_TEST_CASE(generated__property__message_validate__round_trips)
{
    message_validate command;

    const system::wallet::payment_address payment_address_argument{ "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa" };
    command.set_payment_address_argument(payment_address_argument);
    BC_REQUIRE_EQUAL(serial(command.get_payment_address_argument()), serial(payment_address_argument));

    const explorer::config::signature signature_argument{ "HxQp3cXgOIhBEGXks27sfeSQHVgNUeYgl5i5wG/dOUYaSIRnnzXR6NcyH+AfNAHtkWcyOD9rX4pojqmuQyH79K4=" };
    command.set_signature_argument(signature_argument);
    BC_REQUIRE_EQUAL(serial(command.get_signature_argument()), serial(signature_argument));

    const explorer::config::bytes message_argument{ "baadf00d" };
    command.set_message_argument(message_argument);
    BC_REQUIRE_EQUAL(serial(command.get_message_argument()), serial(message_argument));
}

BC_AUTO_TEST_CASE(generated__property__mnemonic_decode__round_trips)
{
    mnemonic_decode command;

    const std::vector<std::string> words_argument{ { "string" } };
    command.set_words_argument(words_argument);
    BC_REQUIRE_EQUAL(serial(command.get_words_argument()), serial(words_argument));

    const explorer::config::language language_option{ "en" };
    command.set_language_option(language_option);
    BC_REQUIRE_EQUAL(serial(command.get_language_option()), serial(language_option));
}

BC_AUTO_TEST_CASE(generated__property__mnemonic_encode__round_trips)
{
    mnemonic_encode command;

    const system::config::base16 entropy_argument{ "baadf00d" };
    command.set_entropy_argument(entropy_argument);
    BC_REQUIRE_EQUAL(serial(command.get_entropy_argument()), serial(entropy_argument));

    const explorer::config::language language_option{ "en" };
    command.set_language_option(language_option);
    BC_REQUIRE_EQUAL(serial(command.get_language_option()), serial(language_option));
}

BC_AUTO_TEST_CASE(generated__property__mnemonic_to_seed__round_trips)
{
    mnemonic_to_seed command;

    const std::vector<std::string> words_argument{ { "string" } };
    command.set_words_argument(words_argument);
    BC_REQUIRE_EQUAL(serial(command.get_words_argument()), serial(words_argument));

    const explorer::config::language language_option{ "en" };
    command.set_language_option(language_option);
    BC_REQUIRE_EQUAL(serial(command.get_language_option()), serial(language_option));

    const std::string passphrase_option{ "string" };
    command.set_passphrase_option(passphrase_option);
    BC_REQUIRE_EQUAL(serial(command.get_passphrase_option()), serial(passphrase_option));
}

BC_AUTO_TEST_CASE(generated__property__put_tx__round_trips)
{
    put_tx command;

    const system::config::transaction transaction_argument{ "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000" };
    command.set_transaction_argument(transaction_argument);
    BC_REQUIRE_EQUAL(serial(command.get_transaction_argument()), serial(transaction_argument));

    const std::string host_option{ "string" };
    command.set_host_option(host_option);
    BC_REQUIRE_EQUAL(serial(command.get_host_option()), serial(host_option));

    const uint16_t port_option{ 42 };
    command.set_port_option(port_option);
    BC_REQUIRE_EQUAL(serial(command.get_port_option()), serial(port_option));
}

BC_AUTO_TEST_CASE(generated__property__qrcode__round_trips)
{
    qrcode command;

    const system::wallet::payment_address payment_address_argument{ "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa" };
    command.set_payment_address_argument(payment_address_argument);
    BC_REQUIRE_EQUAL(serial(command.get_payment_address_argument()), serial(payment_address_argument));

    const uint16_t margin_option{ 42 };
    command.set_margin_option(margin_option);
    BC_REQUIRE_EQUAL(serial(command.get_margin_option()), serial(margin_option));

    const uint16_t pixels_option{ 42 };
    command.set_pixels_option(pixels_option);
    BC_REQUIRE_EQUAL(serial(command.get_pixels_option()), serial(pixels_option));

    const std::string scheme_option{ "string" };
    command.set_scheme_option(scheme_option);
    BC_REQUIRE_EQUAL(serial(command.get_scheme_option()), serial(scheme_option));

    const uint8_t version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__ripemd160__round_trips)
{
    ripemd160 command;

    const system::config::base16 base16_argument{ "baadf00d" };
    command.set_base16_argument(base16_argument);
    BC_REQUIRE_EQUAL(serial(command.get_base16_argument()), serial(base16_argument));
}

BC_AUTO_TEST_CASE(generated__property__satoshi_to_btc__round_trips)
{
    satoshi_to_btc command;

    const uint64_t satoshi_argument{ 42 };
    command.set_satoshi_argument(satoshi_argument);
    BC_REQUIRE_EQUAL(serial(command.get_satoshi_argument()), serial(satoshi_argument));
}

BC_AUTO_TEST_CASE(generated__property__script_decode__round_trips)
{
    script_decode command;

    const system::config::base16 base16_argument{ "baadf00d" };
    command.set_base16_argument(base16_argument);
    BC_REQUIRE_EQUAL(serial(command.get_base16_argument()), serial(base16_argument));

    const uint32_t flags_option{ 42 };
    command.set_flags_option(flags_option);
    BC_REQUIRE_EQUAL(serial(command.get_flags_option()), serial(flags_option));
}

BC_AUTO_TEST_CASE(generated__property__script_encode__round_trips)
{
    script_encode command;

    const system::config::script script_argument{ "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig" };
    command.set_script_argument(script_argument);
    BC_REQUIRE_EQUAL(serial(command.get_script_argument()), serial(script_argument));
}

BC_AUTO_TEST_CASE(generated__property__script_to_address__round_trips)
{
    script_to_address command;

    const system::config::script script_argument{ "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig" };
    command.set_script_argument(script_argument);
    BC_REQUIRE_EQUAL(serial(command.get_script_argument()), serial(script_argument));

    const explorer::config::byte version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__script_to_key__round_trips)
{
    script_to_key command;

    const system::config::script script_argument{ "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig" };
    command.set_script_argument(script_argument);
    BC_REQUIRE_EQUAL(serial(command.get_script_argument()), serial(script_argument));

    const explorer::config::byte version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));
}

BC_AUTO_TEST_CASE(generated__property__script_to_witness__round_trips)
{
    script_to_witness command;

    const std::string prefix_argument{ "string" };
    command.set_prefix_argument(prefix_argument);
    BC_REQUIRE_EQUAL(serial(command.get_prefix_argument()), serial(prefix_argument));

    const system::config::script script_argument{ "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig" };
    command.set_script_argument(script_argument);
    BC_REQUIRE_EQUAL(serial(command.get_script_argument()), serial(script_argument));
}

BC_AUTO_TEST_CASE(generated__property__send_tx__round_trips)
{
    send_tx command;

    const system::config::transaction transaction_argument{ "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000" };
    command.set_transaction_argument(transaction_argument);
    BC_REQUIRE_EQUAL(serial(command.get_transaction_argument()), serial(transaction_argument));
}

BC_AUTO_TEST_CASE(generated__property__sha160__round_trips)
{
    sha160 command;

    const system::config::base16 base16_argument{ "baadf00d" };
    command.set_base16_argument(base16_argument);
    BC_REQUIRE_EQUAL(serial(command.get_base16_argument()), serial(base16_argument));
}

BC_AUTO_TEST_CASE(generated__property__sha256__round_trips)
{
    sha256 command;

    const system::config::base16 base16_argument{ "baadf00d" };
    command.set_base16_argument(base16_argument);
    BC_REQUIRE_EQUAL(serial(command.get_base16_argument()), serial(base16_argument));
}

BC_AUTO_TEST_CASE(generated__property__sha512__round_trips)
{
    sha512 command;

    const system::config::base16 base16_argument{ "baadf00d" };
    command.set_base16_argument(base16_argument);
    BC_REQUIRE_EQUAL(serial(command.get_base16_argument()), serial(base16_argument));
}

BC_AUTO_TEST_CASE(generated__property__stealth_public__round_trips)
{
    stealth_public command;

    const system::wallet::ec_public spend_pubkey_argument{ "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5" };
    command.set_spend_pubkey_argument(spend_pubkey_argument);
    BC_REQUIRE_EQUAL(serial(command.get_spend_pubkey_argument()), serial(spend_pubkey_argument));

    const explorer::config::ec_private shared_secret_argument{ "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" };
    command.set_shared_secret_argument(shared_secret_argument);
    BC_REQUIRE_EQUAL(serial(command.get_shared_secret_argument()), serial(shared_secret_argument));
}

BC_AUTO_TEST_CASE(generated__property__stealth_secret__round_trips)
{
    stealth_secret command;

    const explorer::config::ec_private spend_secret_argument{ "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" };
    command.set_spend_secret_argument(spend_secret_argument);
    BC_REQUIRE_EQUAL(serial(command.get_spend_secret_argument()), serial(spend_secret_argument));

    const explorer::config::ec_private shared_secret_argument{ "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" };
    command.set_shared_secret_argument(shared_secret_argument);
    BC_REQUIRE_EQUAL(serial(command.get_shared_secret_argument()), serial(shared_secret_argument));
}

BC_AUTO_TEST_CASE(generated__property__stealth_shared__round_trips)
{
    stealth_shared command;

    const explorer::config::ec_private secret_argument{ "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" };
    command.set_secret_argument(secret_argument);
    BC_REQUIRE_EQUAL(serial(command.get_secret_argument()), serial(secret_argument));

    const system::wallet::ec_public pubkey_argument{ "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5" };
    command.set_pubkey_argument(pubkey_argument);
    BC_REQUIRE_EQUAL(serial(command.get_pubkey_argument()), serial(pubkey_argument));
}

BC_AUTO_TEST_CASE(generated__property__subscribe_block__round_trips)
{
    subscribe_block command;

    const std::string server_url_argument{ "string" };
    command.set_server_url_argument(server_url_argument);
    BC_REQUIRE_EQUAL(serial(command.get_server_url_argument()), serial(server_url_argument));

    const uint32_t duration_option{ 42 };
    command.set_duration_option(duration_option);
    BC_REQUIRE_EQUAL(serial(command.get_duration_option()), serial(duration_option));
}

BC_AUTO_TEST_CASE(generated__property__subscribe_tx__round_trips)
{
    subscribe_tx command;

    const std::string server_url_argument{ "string" };
    command.set_server_url_argument(server_url_argument);
    BC_REQUIRE_EQUAL(serial(command.get_server_url_argument()), serial(server_url_argument));

    const uint32_t duration_option{ 42 };
    command.set_duration_option(duration_option);
    BC_REQUIRE_EQUAL(serial(command.get_duration_option()), serial(duration_option));
}

BC_AUTO_TEST_CASE(generated__property__token_new__round_trips)
{
    token_new command;

    const std::string passphrase_argument{ "string" };
    command.set_passphrase_argument(passphrase_argument);
    BC_REQUIRE_EQUAL(serial(command.get_passphrase_argument()), serial(passphrase_argument));

    const system::config::base16 salt_argument{ "baadf00d" };
    command.set_salt_argument(salt_argument);
    BC_REQUIRE_EQUAL(serial(command.get_salt_argument()), serial(salt_argument));

    const uint32_t lot_option{ 42 };
    command.set_lot_option(lot_option);
    BC_REQUIRE_EQUAL(serial(command.get_lot_option()), serial(lot_option));

    const uint32_t sequence_option{ 42 };
    command.set_sequence_option(sequence_option);
    BC_REQUIRE_EQUAL(serial(command.get_sequence_option()), serial(sequence_option));
}

BC_AUTO_TEST_CASE(generated__property__tx_decode__round_trips)
{
    tx_decode command;

    const system::config::transaction transaction_argument{ "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000" };
    command.set_transaction_argument(transaction_argument);
    BC_REQUIRE_EQUAL(serial(command.get_transaction_argument()), serial(transaction_argument));
}

BC_AUTO_TEST_CASE(generated__property__tx_encode__round_trips)
{
    tx_encode command;

    const uint32_t lock_time_option{ 42 };
    command.set_lock_time_option(lock_time_option);
    BC_REQUIRE_EQUAL(serial(command.get_lock_time_option()), serial(lock_time_option));

    const uint32_t version_option{ 42 };
    command.set_version_option(version_option);
    BC_REQUIRE_EQUAL(serial(command.get_version_option()), serial(version_option));

    const std::vector<system::config::input> inputs_option{ { "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b:0:4294967295" } };
    command.set_inputs_option(inputs_option);
    BC_REQUIRE_EQUAL(serial(command.get_inputs_option()), serial(inputs_option));

    const std::vector<system::config::output> outputs_option{ { "[baadf00d]:42" } };
    command.set_outputs_option(outputs_option);
    BC_REQUIRE_EQUAL(serial(command.get_outputs_option()), serial(outputs_option));
}

BC_AUTO_TEST_CASE(generated__property__tx_sign__round_trips)
{
    tx_sign command;

    const explorer::config::ec_private ec_private_key_argument{ "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" };
    command.set_ec_private_key_argument(ec_private_key_argument);
    BC_REQUIRE_EQUAL(serial(command.get_ec_private_key_argument()), serial(ec_private_key_argument));

    const std::vector<system::config::transaction> transactions_argument{ { "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000" } };
    command.set_transactions_argument(transactions_argument);
    BC_REQUIRE_EQUAL(serial(command.get_transactions_argument()), serial(transactions_argument));
}

BC_AUTO_TEST_CASE(generated__property__uri_decode__round_trips)
{
    uri_decode command;

    const system::wallet::bitcoin_uri uri_argument{ "bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L" };
    command.set_uri_argument(uri_argument);
    BC_REQUIRE_EQUAL(serial(command.get_uri_argument()), serial(uri_argument));
}

BC_AUTO_TEST_CASE(generated__property__uri_encode__round_trips)
{
    uri_encode command;

    const explorer::config::address address_argument{ "1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L" };
    command.set_address_argument(address_argument);
    BC_REQUIRE_EQUAL(serial(command.get_address_argument()), serial(address_argument));

    const explorer::config::btc amount_option{ "42.42" };
    command.set_amount_option(amount_option);
    BC_REQUIRE_EQUAL(serial(command.get_amount_option()), serial(amount_option));

    const std::string label_option{ "string" };
    command.set_label_option(label_option);
    BC_REQUIRE_EQUAL(serial(command.get_label_option()), serial(label_option));

    const std::string message_option{ "string" };
    command.set_message_option(message_option);
    BC_REQUIRE_EQUAL(serial(command.get_message_option()), serial(message_option));

    const std::string request_option{ "string" };
    command.set_request_option(request_option);
    BC_REQUIRE_EQUAL(serial(command.get_request_option()), serial(request_option));
}

BC_AUTO_TEST_CASE(generated__property__validate_tx__round_trips)
{
    validate_tx command;

    const system::config::transaction transaction_argument{ "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000" };
    command.set_transaction_argument(transaction_argument);
    BC_REQUIRE_EQUAL(serial(command.get_transaction_argument()), serial(transaction_argument));
}

BC_AUTO_TEST_CASE(generated__property__watch_key__round_trips)
{
    watch_key command;

    const system::config::hash256 hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_argument(hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hash_argument()), serial(hash_argument));

    const uint32_t duration_option{ 42 };
    command.set_duration_option(duration_option);
    BC_REQUIRE_EQUAL(serial(command.get_duration_option()), serial(duration_option));
}

BC_AUTO_TEST_CASE(generated__property__watch_tx__round_trips)
{
    watch_tx command;

    const system::config::hash256 hash_argument{ "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f" };
    command.set_hash_argument(hash_argument);
    BC_REQUIRE_EQUAL(serial(command.get_hash_argument()), serial(hash_argument));
}

BC_AUTO_TEST_CASE(generated__property__wif_to_ec__round_trips)
{
    wif_to_ec command;

    const system::wallet::ec_private wif_argument{ "KynK1v6fGwt2deK5axWUi4dStZzyuhrMbsYwk52kXM5LMivMMrQp" };
    command.set_wif_argument(wif_argument);
    BC_REQUIRE_EQUAL(serial(command.get_wif_argument()), serial(wif_argument));
}

BC_AUTO_TEST_CASE(generated__property__wif_to_public__round_trips)
{
    wif_to_public command;

    const system::wallet::ec_private wif_argument{ "KynK1v6fGwt2deK5axWUi4dStZzyuhrMbsYwk52kXM5LMivMMrQp" };
    command.set_wif_argument(wif_argument);
    BC_REQUIRE_EQUAL(serial(command.get_wif_argument()), serial(wif_argument));
}

BC_AUTO_TEST_CASE(generated__property__witness_to_key__round_trips)
{
    witness_to_key command;

    const system::wallet::witness_address witness_address_argument{ "bc1qw508d6qejxtdg4y5r3zarvary0c5xw7kv8f3t4" };
    command.set_witness_address_argument(witness_address_argument);
    BC_REQUIRE_EQUAL(serial(command.get_witness_address_argument()), serial(witness_address_argument));
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
