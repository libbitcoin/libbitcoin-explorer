/*
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
#include "precompile.hpp"
#include "command.hpp"

SX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(stealth_address_encode__invoke)

// mainnet

// vectors
// sx.dyne.org/stealth.html
#define STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A  "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006"
#define STEALTH_ADDRESS_ENCODE_SPEND_PUBKEY_B "024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969"

// expectations
#define STEALTH_ADDRESS_ENCODE_MAINNET_ADDRESS_A     "hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i"
#define STEALTH_ADDRESS_ENCODE_TESTNET_ADDRESS_A     "idPayBqZUpZH7Y5GTaoEyGxDsEmU377JUmhtqG8yoHCkfGfhnAHmGUJbL"
#define STEALTH_ADDRESS_ENCODE_MAINNET_ADDRESS_AB    "vJmwY32eS5VDC2C4GaZyXt7i4iCjzSMZ1XSd6KbkA7QbGE492akT2eZZMjCwWDqKRSYhnSA8Bgp78KeAYFVCi8ke5mELdoYMBNep7L"
#define STEALTH_ADDRESS_ENCODE_TESTNET_ADDRESS_AB    "waPXhQwQE9tDugfgLkvpDs3dnkPx1RsfDjFt4zBq7EeWeATRHpyQpYrFZR8T4BQy91Vpvshm2TDER8b9ZryuZ8VSzz8ywzNzX8NqF4"
#define STEALTH_ADDRESS_ENCODE_MAINNET_ADDRESS_AAB   "vK4cs6xzzf326HyUeoJCQng6FXLVK27PyJoRbYSMyT9TzgKds8JDerKaRQ72q9kEp2tQNE2KRvabvqH5n5Rv6yv6Yht9uWNcbDGD7d"
#define STEALTH_ADDRESS_ENCODE_TESTNET_ADDRESS_AAB   "wagD2UsknjS2oxT6iyf36mc1yZXhL1dWBWcgaD2SvaPPNciv8NXBSkcGd62YP7KtXbqXWfZxGgyjDeE4ogvcwyeuTvnoDhDFvouxfN"
#define STEALTH_ADDRESS_ENCODE_MAINNET_ADDRESS_AAB1  "vK4cs6xzzf326HyUeoJCQng6FXLVK27PyJoRbYSMyT9TzgKds8JDerKaRQ72q9kEp2tQNE2KRvabvqH5n5Rv6yv6Yht9uWN7nyPnY7"
#define STEALTH_ADDRESS_ENCODE_TESTNET_ADDRESS_AAB1  "wagD2UsknjS2oxT6iyf36mc1yZXhL1dWBWcgaD2SvaPPNciv8NXBSkcGd62YP7KtXbqXWfZxGgyjDeE4ogvcwyeuTvnoDhCm5ezXKQ"
#define STEALTH_ADDRESS_ENCODE_MAINNET_ADDRESS_AAB1P ""
#define STEALTH_ADDRESS_ENCODE_TESTNET_ADDRESS_AAB1P ""

BOOST_AUTO_TEST_CASE(stealth_address_encode__invoke__scan_key_mainnet__okay_output)
{
    SX_DECLARE_COMMAND(stealth_address_encode);
    command.set_scan_pubkey_argument({ STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    // unverified value
    SX_REQUIRE_OUTPUT(STEALTH_ADDRESS_ENCODE_MAINNET_ADDRESS_A "\n");
}

BOOST_AUTO_TEST_CASE(stealth_address_encode__invoke__scan_key_spend_key_mainnet__okay_output)
{
    SX_DECLARE_COMMAND(stealth_address_encode);
    command.set_scan_pubkey_argument({ STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ADDRESS_ENCODE_SPEND_PUBKEY_B } });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT(STEALTH_ADDRESS_ENCODE_MAINNET_ADDRESS_AB "\n");
}

BOOST_AUTO_TEST_CASE(stealth_address_encode__invoke__scan_key_two_spend_key_mainnet__okay_output)
{
    SX_DECLARE_COMMAND(stealth_address_encode);
    command.set_scan_pubkey_argument({ STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ADDRESS_ENCODE_SPEND_PUBKEY_B } });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT(STEALTH_ADDRESS_ENCODE_MAINNET_ADDRESS_AAB "\n");
}

BOOST_AUTO_TEST_CASE(stealth_address_encode__invoke__scan_key_two_spend_key_signatures_overflow_mainnet__failure_error)
{
    SX_DECLARE_COMMAND(stealth_address_encode);
    command.set_signatures_option(42);
    command.set_scan_pubkey_argument({ STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ADDRESS_ENCODE_SPEND_PUBKEY_B } });
    SX_REQUIRE_FAILURE(command.invoke(output, error));
    SX_REQUIRE_ERROR(SX_STEALTH_ADDRESS_ENCODE_SIGNATURES_OVERFLOW "\n");
}

BOOST_AUTO_TEST_CASE(stealth_address_encode__invoke__scan_key_two_spend_key_1_signature_mainnet__okay_output)
{
    SX_DECLARE_COMMAND(stealth_address_encode);
    command.set_signatures_option(1);
    command.set_scan_pubkey_argument({ STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ADDRESS_ENCODE_SPEND_PUBKEY_B } });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT(STEALTH_ADDRESS_ENCODE_MAINNET_ADDRESS_AAB1 "\n");
}

//BOOST_AUTO_TEST_CASE(stealth_address_encode__invoke__scan_key_two_spend_key_1_signature_prefix_mainnet__okay_output)
//{
//    SX_DECLARE_COMMAND(stealth_address_encode);
//    command.set_signatures_option(1);
//    command.set_prefix_option({ "0010011" });
//    command.set_scan_pubkey_argument({ STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A });
//    command.set_spend_pubkeys_argument({ { STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ADDRESS_ENCODE_SPEND_PUBKEY_B } });
//    SX_REQUIRE_OKAY(command.invoke(output, error));
//    SX_REQUIRE_OUTPUT(STEALTH_ADDRESS_ENCODE_MAINNET_ADDRESS_AAB1P "\n");
//}

// testnet

BOOST_AUTO_TEST_CASE(stealth_address_encode__invoke__scan_key_testnet__okay_output)
{
    SX_DECLARE_COMMAND(stealth_address_encode);
    command.set_general_testnet_setting(true);
    command.set_scan_pubkey_argument({ STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    // unverified value
    SX_REQUIRE_OUTPUT(STEALTH_ADDRESS_ENCODE_TESTNET_ADDRESS_A "\n");
}

BOOST_AUTO_TEST_CASE(stealth_address_encode__invoke__scan_key_spend_key_testnet__okay_output)
{
    SX_DECLARE_COMMAND(stealth_address_encode);
    command.set_general_testnet_setting(true);
    command.set_scan_pubkey_argument({ STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ADDRESS_ENCODE_SPEND_PUBKEY_B } });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT(STEALTH_ADDRESS_ENCODE_TESTNET_ADDRESS_AB "\n");
}

BOOST_AUTO_TEST_CASE(stealth_address_encode__invoke__scan_key_two_spend_key_testnet__okay_output)
{
    SX_DECLARE_COMMAND(stealth_address_encode);
    command.set_general_testnet_setting(true);
    command.set_scan_pubkey_argument({ STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ADDRESS_ENCODE_SPEND_PUBKEY_B } });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    // unverified value
    SX_REQUIRE_OUTPUT(STEALTH_ADDRESS_ENCODE_TESTNET_ADDRESS_AAB "\n");
}

BOOST_AUTO_TEST_CASE(stealth_address_encode__invoke__scan_key_two_spend_key_signatures_overflow_testnet__failure_error)
{
    SX_DECLARE_COMMAND(stealth_address_encode);
    command.set_signatures_option(42);
    command.set_general_testnet_setting(true);
    command.set_scan_pubkey_argument({ STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ADDRESS_ENCODE_SPEND_PUBKEY_B } });
    SX_REQUIRE_FAILURE(command.invoke(output, error));
    SX_REQUIRE_ERROR(SX_STEALTH_ADDRESS_ENCODE_SIGNATURES_OVERFLOW "\n");
}

BOOST_AUTO_TEST_CASE(stealth_address_encode__invoke__scan_key_two_spend_key_1_signature_testnet__okay_output)
{
    SX_DECLARE_COMMAND(stealth_address_encode);
    command.set_signatures_option(1);
    command.set_general_testnet_setting(true);
    command.set_scan_pubkey_argument({ STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ADDRESS_ENCODE_SPEND_PUBKEY_B } });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT(STEALTH_ADDRESS_ENCODE_TESTNET_ADDRESS_AAB1 "\n");
}

//BOOST_AUTO_TEST_CASE(stealth_address_encode__invoke__scan_key_two_spend_key_1_signature_prefix_testnet__okay_output)
//{
//    SX_DECLARE_COMMAND(stealth_address_encode);
//    command.set_signatures_option(1);
//    command.set_prefix_option({ "0010011" });
//    command.set_general_testnet_setting(true);
//    command.set_scan_pubkey_argument({ STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A });
//    command.set_spend_pubkeys_argument({ { STEALTH_ADDRESS_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ADDRESS_ENCODE_SPEND_PUBKEY_B } });
//    SX_REQUIRE_OKAY(command.invoke(output, error));
//    SX_REQUIRE_OUTPUT(STEALTH_ADDRESS_ENCODE_TESTNET_ADDRESS_AAB1P "\n");
//}

BOOST_AUTO_TEST_SUITE_END()