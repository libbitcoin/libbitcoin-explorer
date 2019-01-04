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
BOOST_AUTO_TEST_SUITE(stealth_decode__invoke)

// vectors
#define STEALTH_DECODE_ADDRESS_A "1DsiaW2kjjZAT92tAW8rvS1tF9ZSVzpz5WPBLAQFrPrMRMQQz7X6qR8h"
#define STEALTH_ENCODE_ADDRESS_AT "2rT9GaRuU7hM5DiaP6FDbRWX9tLuh5E5QC6mG6jVfMSm7LHmiGFbDhHfHe"
#define STEALTH_DECODE_ADDRESS_AB "11CkApw4tph2ABwF5Uiaf4od863GnZ4AyDn4NvAEsKwNqCMzHN3nnUStpTYMyU1KadXfwFSsY4pxKpsNYhdEKkfYR7KTxKLb1r4mc"
#define STEALTH_DECODE_ADDRESS_AAB "1Ht5EmHdUNVvRyMdJCwTZdBowDnbNJu8kaaZbkn4D4p7HTrppupQzETxVMdguNviAyEFj7e7mqKkqTncNeLdAv81Mm8jf9bzn7hBP"
#define STEALTH_DECODE_ADDRESS_AAB1 "1Ht5EmHdUNVvRyMdJCwTZdBowDnbNJu8kaaZbkn4D4p7HTrppupQzETxVMdguNviAyEFj7e7mqKkqTncNeLdAv81Mm8jf978insV8"
#define STEALTH_DECODE_ADDRESS_AAB10 "16frt2rsvRjxyyqExjiRAkmm6g8NPRnFURWCZosVnPrSYBK9sM8j74PPGDd2MtiZuSPoLzVTgQ1P5k9Xm2ExkMhFqVTQfZ8jFEqkNomZ"
#define STEALTH_DECODE_ADDRESS_AAB1F "12uTi7oidePLNjGJwfwLy1P834WusAUEsrGWCKPuaHR6f8fmxXHn8n8YsBwqy1w9HCN7SMHhWpiWqBuJDgY8v9sBsGi3YEWef2s4oAWeUy6"
#define STEALTH_DECODE_ADDRESS_AAB1FT "GtumWpbyb5tVoyj9GFpTVK5aFwT1CpkFNzoFa2vcC98uxEYHqFGSMMuQGxidEdVwP6scgLk1u8aykLSuWATbpJcLm7Z35nFD52RckrfKcJGB"

// expectations
#define STEALTH_DECODE_A \
    "stealth_address\n" \
    "{\n" \
    "    encoded 1DsiaW2kjjZAT92tAW8rvS1tF9ZSVzpz5WPBLAQFrPrMRMQQz7X6qR8h\n" \
    "    filter \"\"\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 1\n" \
    "    spends\n" \
    "    {\n" \
    "        public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    }\n" \
    "    version 0\n" \
    "}\n"
#define STEALTH_DECODE_AB \
    "stealth_address\n" \
    "{\n" \
    "    encoded 11CkApw4tph2ABwF5Uiaf4od863GnZ4AyDn4NvAEsKwNqCMzHN3nnUStpTYMyU1KadXfwFSsY4pxKpsNYhdEKkfYR7KTxKLb1r4mc\n" \
    "    filter \"\"\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 1\n" \
    "    spends\n" \
    "    {\n" \
    "        public_key 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969\n" \
    "    }\n" \
    "    version 0\n" \
    "}\n"
#define STEALTH_DECODE_AAB \
    "stealth_address\n" \
    "{\n" \
    "    encoded 1Ht5EmHdUNVvRyMdJCwTZdBowDnbNJu8kaaZbkn4D4p7HTrppupQzETxVMdguNviAyEFj7e7mqKkqTncNeLdAv81Mm8jf9bzn7hBP\n" \
    "    filter \"\"\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 2\n" \
    "    spends\n" \
    "    {\n" \
    "        public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "        public_key 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969\n" \
    "    }\n" \
    "    version 0\n" \
    "}\n"
#define STEALTH_DECODE_AAB1 \
    "stealth_address\n" \
    "{\n" \
    "    encoded 1Ht5EmHdUNVvRyMdJCwTZdBowDnbNJu8kaaZbkn4D4p7HTrppupQzETxVMdguNviAyEFj7e7mqKkqTncNeLdAv81Mm8jf978insV8\n" \
    "    filter \"\"\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 1\n" \
    "    spends\n" \
    "    {\n" \
    "        public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "        public_key 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969\n" \
    "    }\n" \
    "    version 0\n" \
    "}\n"
#define STEALTH_DECODE_AAB10 \
    "stealth_address\n" \
    "{\n" \
    "    encoded 16frt2rsvRjxyyqExjiRAkmm6g8NPRnFURWCZosVnPrSYBK9sM8j74PPGDd2MtiZuSPoLzVTgQ1P5k9Xm2ExkMhFqVTQfZ8jFEqkNomZ\n" \
    "    filter 000000001010\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 1\n" \
    "    spends\n" \
    "    {\n" \
    "        public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "        public_key 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969\n" \
    "    }\n" \
    "    version 0\n" \
    "}\n"
#define STEALTH_DECODE_AAB1F \
    "stealth_address\n" \
    "{\n" \
    "    encoded 12uTi7oidePLNjGJwfwLy1P834WusAUEsrGWCKPuaHR6f8fmxXHn8n8YsBwqy1w9HCN7SMHhWpiWqBuJDgY8v9sBsGi3YEWef2s4oAWeUy6\n" \
    "    filter 10111010101011011111000000001101\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 1\n" \
    "    spends\n" \
    "    {\n" \
    "        public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "        public_key 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969\n" \
    "    }\n" \
    "    version 0\n" \
    "}\n"
#define STEALTH_DECODE_AAB1FT \
    "stealth_address\n" \
    "{\n" \
    "    encoded GtumWpbyb5tVoyj9GFpTVK5aFwT1CpkFNzoFa2vcC98uxEYHqFGSMMuQGxidEdVwP6scgLk1u8aykLSuWATbpJcLm7Z35nFD52RckrfKcJGB\n" \
    "    filter 10111010101011011111000000001101\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 1\n" \
    "    spends\n" \
    "    {\n" \
    "        public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "        public_key 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969\n" \
    "    }\n" \
    "    version 111\n" \
    "}\n"


BOOST_AUTO_TEST_CASE(stealth_decode__invoke__scan_key__okay_output)
{
    BX_DECLARE_COMMAND(stealth_decode);
    command.set_stealth_address_argument({ STEALTH_DECODE_ADDRESS_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_DECODE_A);
}

BOOST_AUTO_TEST_CASE(stealth_decode__invoke__scan_key_spend_key__okay_output)
{
    BX_DECLARE_COMMAND(stealth_decode);
    command.set_stealth_address_argument({ STEALTH_DECODE_ADDRESS_AB });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_DECODE_AB);
}

BOOST_AUTO_TEST_CASE(stealth_decode__invoke__scan_key_2spend_keys_reuse__okay_output)
{
    BX_DECLARE_COMMAND(stealth_decode);
    command.set_stealth_address_argument({ STEALTH_DECODE_ADDRESS_AAB });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_DECODE_AAB);
}

BOOST_AUTO_TEST_CASE(stealth_decode__invoke__scan_key_2_spend_keys_reuse_1_signature__okay_output)
{
    BX_DECLARE_COMMAND(stealth_decode);
    command.set_stealth_address_argument({ STEALTH_DECODE_ADDRESS_AAB1 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_DECODE_AAB1);
}

BOOST_AUTO_TEST_CASE(stealth_decode__invoke__scan_key_2_spend_keys_reuse_1_signature_leading_0_prefix__okay_output)
{
    BX_DECLARE_COMMAND(stealth_decode);
    command.set_stealth_address_argument({ STEALTH_DECODE_ADDRESS_AAB10 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_DECODE_AAB10);
}

BOOST_AUTO_TEST_CASE(stealth_decode__invoke__scan_key_2_spend_keys_reuse_1_signature_baadf00d_prefix__okay_output)
{
    BX_DECLARE_COMMAND(stealth_decode);
    command.set_stealth_address_argument({ STEALTH_DECODE_ADDRESS_AAB1F });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_DECODE_AAB1F);
}

BOOST_AUTO_TEST_CASE(stealth_decode__invoke__scan_key_2_spend_keys_reuse_1_signature_baadf00d_prefix_testnet__okay_output)
{
    BX_DECLARE_COMMAND(stealth_decode);
    command.set_stealth_address_argument({ STEALTH_DECODE_ADDRESS_AAB1FT });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_DECODE_AAB1FT);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
