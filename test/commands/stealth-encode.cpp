/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(stealth_encode__invoke)

// mainnet

// vectors
#define STEALTH_ENCODE_SCAN_PUBKEY_A "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006"
#define STEALTH_ENCODE_SPEND_PUBKEY_B "024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969"
#define STEALTH_ENCODE_LEADING0_FILTER "000000001010"
#define STEALTH_ENCODE_BAADF00D_FILTER "10111010101011011111000000001101"
#define STEALTH_ENCODE_MAX_FILTER_LENGTH "11111111110000000000111111111100"

// expectations
#define STEALTH_ENCODE_ADDRESS_A "1DsiaW2kjjZAT92tAW8rvS1tF9ZSVzpz5WPBLAQFrPrMRMQQz7X6qR8h"
#define STEALTH_ENCODE_ADDRESS_AT "2rT9GaRuU7hM5DiaP6FDbRWX9tLuh5E5QC6mG6jVfMSm7LHmiGFbDhHfHe"
#define STEALTH_ENCODE_ADDRESS_AM "12TFFcDyvpZd4Zy1GAS7sp7Xz9sgRabovgf8xfD4EMGxenJw8ivsa3bBj8TzjR"
#define STEALTH_ENCODE_ADDRESS_AB "11CkApw4tph2ABwF5Uiaf4od863GnZ4AyDn4NvAEsKwNqCMzHN3nnUStpTYMyU1KadXfwFSsY4pxKpsNYhdEKkfYR7KTxKLb1r4mc"
#define STEALTH_ENCODE_ADDRESS_AAB "1Ht5EmHdUNVvRyMdJCwTZdBowDnbNJu8kaaZbkn4D4p7HTrppupQzETxVMdguNviAyEFj7e7mqKkqTncNeLdAv81Mm8jf9bzn7hBP"
#define STEALTH_ENCODE_ADDRESS_AAB1 "1Ht5EmHdUNVvRyMdJCwTZdBowDnbNJu8kaaZbkn4D4p7HTrppupQzETxVMdguNviAyEFj7e7mqKkqTncNeLdAv81Mm8jf978insV8"
#define STEALTH_ENCODE_ADDRESS_AAB10 "16frt2rsvRjxyyqExjiRAkmm6g8NPRnFURWCZosVnPrSYBK9sM8j74PPGDd2MtiZuSPoLzVTgQ1P5k9Xm2ExkMhFqVTQfZ8jFEqkNomZ"
#define STEALTH_ENCODE_ADDRESS_AAB1F "12uTi7oidePLNjGJwfwLy1P834WusAUEsrGWCKPuaHR6f8fmxXHn8n8YsBwqy1w9HCN7SMHhWpiWqBuJDgY8v9sBsGi3YEWef2s4oAWeUy6"
#define STEALTH_ENCODE_ADDRESS_AAB1FT "GtumWpbyb5tVoyj9GFpTVK5aFwT1CpkFNzoFa2vcC98uxEYHqFGSMMuQGxidEdVwP6scgLk1u8aykLSuWATbpJcLm7Z35nFD52RckrfKcJGB"

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key_mainnet__okay_output)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_version_option(0);
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_ENCODE_ADDRESS_A "\n");
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key_testnet__okay_output)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_version_option(111);
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_ENCODE_ADDRESS_AT "\n");
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key_spend_key__okay_output)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_version_option(0);
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkey_argument({ STEALTH_ENCODE_SPEND_PUBKEY_B });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_ENCODE_ADDRESS_AB "\n");
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key_same_key__okay_output)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_version_option(0);
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_ENCODE_ADDRESS_A "\n");
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__max_filter__okay_output)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_version_option(0);
    command.set_filter_option({ STEALTH_ENCODE_MAX_FILTER_LENGTH });
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE_EQUAL(output.str(), STEALTH_ENCODE_ADDRESS_AM "\n");
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__filter_too_long__okay_output)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_version_option(0);
    command.set_filter_option({ STEALTH_ENCODE_MAX_FILTER_LENGTH "1" });
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BOOST_REQUIRE_EQUAL(error.str(), BX_STEALTH_ENCODE_FILTER_TOO_LONG "\n");
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__leading_0_filter__okay_output)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_version_option(0);
    command.set_filter_option({ STEALTH_ENCODE_LEADING0_FILTER });
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE_EQUAL(output.str(), STEALTH_ENCODE_ADDRESS_AAB10 "\n");
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__baadf00d_filter__okay_output)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_version_option(0);
    command.set_filter_option({ STEALTH_ENCODE_BAADF00D_FILTER });
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE_EQUAL(output.str(), STEALTH_ENCODE_ADDRESS_AAB1F "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
