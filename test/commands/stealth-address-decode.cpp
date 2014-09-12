/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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
// #include "precompile.hpp"
#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(stealth_address_decode__invoke)

// vectors
#define STEALTH_ADDRESS_DECODE_ADDRESS_A "hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i"
#define STEALTH_ADDRESS_DECODE_ADDRESS_AB "vJmwY32eS5VDC2C4GaZyXt7i4iCjzSMZ1XSd6KbkA7QbGE492akT2eZZMjCwWDqKRSYhnSA8Bgp78KeAYFVCi8ke5mELdoYMBNep7L"
#define STEALTH_ADDRESS_DECODE_ADDRESS_AAB "vK4cs6xzzf326HyUeoJCQng6FXLVK27PyJoRbYSMyT9TzgKds8JDerKaRQ72q9kEp2tQNE2KRvabvqH5n5Rv6yv6Yht9uWNcbDGD7d"
#define STEALTH_ADDRESS_DECODE_ADDRESS_AAB1 "vK4cs6xzzf326HyUeoJCQng6FXLVK27PyJoRbYSMyT9TzgKds8JDerKaRQ72q9kEp2tQNE2KRvabvqH5n5Rv6yv6Yht9uWN7nyPnY7"
#define STEALTH_ADDRESS_DECODE_ADDRESS_AAB10 "JubEFUfmd2J3i83L9qWNr7fDSbb2bE7PY6RvEzH6wsNW8Ls7Mw3hxKZHWr3SvEz4o6NWLguFmyK9yBPrzxtC7ssTXQKJnyMUpL71mzBgd"
#define STEALTH_ADDRESS_DECODE_ADDRESS_AAB1P "71rNEn94Rfjj2byKuyqRzcPM4kq5Zdi4ZdEe6ZqxmjaaSz3VuUNXzhxiiXLRHnVmpzkTd8Z2KG92pUudhYqkW6DcYHVA4PRkNJEYtpfK2nML"
#define STEALTH_ADDRESS_DECODE_ADDRESS_AAB1PT "7AA4vX3ZmyjrQGxHEmTZaef4Smpm1PaXcqKKH3ybTbWqrwjRXZE3LLf26rCLRJdLkRDTkk2vRdtH4iEaZpVFoAboEpSh4QbgYy6Pt91Mt1UK"

// expectations
#define STEALTH_ADDRESS_DECODE_A \
    "address\n" \
    "{\n" \
    "    encoded hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i\n" \
    "    prefix \"\"\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 1\n" \
    "    spend\n" \
    "    {\n" \
    "        public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    }\n" \
    "    testnet false\n" \
    "}\n"
#define STEALTH_ADDRESS_DECODE_AB \
    "address\n" \
    "{\n" \
    "    encoded vJmwY32eS5VDC2C4GaZyXt7i4iCjzSMZ1XSd6KbkA7QbGE492akT2eZZMjCwWDqKRSYhnSA8Bgp78KeAYFVCi8ke5mELdoYMBNep7L\n" \
    "    prefix \"\"\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 1\n" \
    "    spend\n" \
    "    {\n" \
    "        public_key 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969\n" \
    "    }\n" \
    "    testnet false\n" \
    "}\n"
#define STEALTH_ADDRESS_DECODE_AAB \
    "address\n" \
    "{\n" \
    "    encoded vK4cs6xzzf326HyUeoJCQng6FXLVK27PyJoRbYSMyT9TzgKds8JDerKaRQ72q9kEp2tQNE2KRvabvqH5n5Rv6yv6Yht9uWNcbDGD7d\n" \
    "    prefix \"\"\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 2\n" \
    "    spend\n" \
    "    {\n" \
    "        public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "        public_key 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969\n" \
    "    }\n" \
    "    testnet false\n" \
    "}\n"
#define STEALTH_ADDRESS_DECODE_AAB1 \
    "address\n" \
    "{\n" \
    "    encoded vK4cs6xzzf326HyUeoJCQng6FXLVK27PyJoRbYSMyT9TzgKds8JDerKaRQ72q9kEp2tQNE2KRvabvqH5n5Rv6yv6Yht9uWN7nyPnY7\n" \
    "    prefix \"\"\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 1\n" \
    "    spend\n" \
    "    {\n" \
    "        public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "        public_key 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969\n" \
    "    }\n" \
    "    testnet false\n" \
    "}\n"
#define STEALTH_ADDRESS_DECODE_AAB10 \
    "address\n" \
    "{\n" \
    "    encoded JubEFUfmd2J3i83L9qWNr7fDSbb2bE7PY6RvEzH6wsNW8Ls7Mw3hxKZHWr3SvEz4o6NWLguFmyK9yBPrzxtC7ssTXQKJnyMUpL71mzBgd\n" \
    "    prefix 000000001010\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 1\n" \
    "    spend\n" \
    "    {\n" \
    "        public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "        public_key 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969\n" \
    "    }\n" \
    "    testnet false\n" \
    "}\n"
#define STEALTH_ADDRESS_DECODE_AAB1P \
    "address\n" \
    "{\n" \
    "    encoded 71rNEn94Rfjj2byKuyqRzcPM4kq5Zdi4ZdEe6ZqxmjaaSz3VuUNXzhxiiXLRHnVmpzkTd8Z2KG92pUudhYqkW6DcYHVA4PRkNJEYtpfK2nML\n" \
    "    prefix 10111010101011011111000000001101\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 1\n" \
    "    spend\n" \
    "    {\n" \
    "        public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "        public_key 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969\n" \
    "    }\n" \
    "    testnet false\n" \
    "}\n"
#define STEALTH_ADDRESS_DECODE_AAB1PT \
    "address\n" \
    "{\n" \
    "    encoded 7AA4vX3ZmyjrQGxHEmTZaef4Smpm1PaXcqKKH3ybTbWqrwjRXZE3LLf26rCLRJdLkRDTkk2vRdtH4iEaZpVFoAboEpSh4QbgYy6Pt91Mt1UK\n" \
    "    prefix 10111010101011011111000000001101\n" \
    "    scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    signatures 1\n" \
    "    spend\n" \
    "    {\n" \
    "        public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "        public_key 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969\n" \
    "    }\n" \
    "    testnet true\n" \
    "}\n"


BOOST_AUTO_TEST_CASE(stealth_address_decode__invoke__scan_key__okay_output)
{
    BX_DECLARE_COMMAND(stealth_address_decode);
    command.set_stealth_address_argument({ STEALTH_ADDRESS_DECODE_ADDRESS_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_ADDRESS_DECODE_A);
}

BOOST_AUTO_TEST_CASE(stealth_address_decode__invoke__scan_key_spend_key__okay_output)
{
    BX_DECLARE_COMMAND(stealth_address_decode);
    command.set_stealth_address_argument({ STEALTH_ADDRESS_DECODE_ADDRESS_AB });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_ADDRESS_DECODE_AB);
}

BOOST_AUTO_TEST_CASE(stealth_address_decode__invoke__scan_key_2spend_keys_reuse__okay_output)
{
    BX_DECLARE_COMMAND(stealth_address_decode);
    command.set_stealth_address_argument({ STEALTH_ADDRESS_DECODE_ADDRESS_AAB });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_ADDRESS_DECODE_AAB);
}

BOOST_AUTO_TEST_CASE(stealth_address_decode__invoke__scan_key_2_spend_keys_reuse_1_signature__okay_output)
{
    BX_DECLARE_COMMAND(stealth_address_decode);
    command.set_stealth_address_argument({ STEALTH_ADDRESS_DECODE_ADDRESS_AAB1 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_ADDRESS_DECODE_AAB1);
}

BOOST_AUTO_TEST_CASE(stealth_address_decode__invoke__scan_key_2_spend_keys_reuse_1_signature_leading_0_prefix__okay_output)
{
    BX_DECLARE_COMMAND(stealth_address_decode);
    command.set_stealth_address_argument({ STEALTH_ADDRESS_DECODE_ADDRESS_AAB10 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_ADDRESS_DECODE_AAB10);
}

BOOST_AUTO_TEST_CASE(stealth_address_decode__invoke__scan_key_2_spend_keys_reuse_1_signature_baadf00d_prefix__okay_output)
{
    BX_DECLARE_COMMAND(stealth_address_decode);
    command.set_stealth_address_argument({ STEALTH_ADDRESS_DECODE_ADDRESS_AAB1P });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_ADDRESS_DECODE_AAB1P);
}

BOOST_AUTO_TEST_CASE(stealth_address_decode__invoke__scan_key_2_spend_keys_reuse_1_signature_baadf00d_prefix_testnet__okay_output)
{
    BX_DECLARE_COMMAND(stealth_address_decode);
    command.set_stealth_address_argument({ STEALTH_ADDRESS_DECODE_ADDRESS_AAB1PT });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_ADDRESS_DECODE_AAB1PT);
}

BOOST_AUTO_TEST_SUITE_END()