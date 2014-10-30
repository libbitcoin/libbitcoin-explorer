/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
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

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(stealth_encode__invoke)

// mainnet

// vectors
#define STEALTH_ENCODE_SCAN_PUBKEY_A "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006"
#define STEALTH_ENCODE_SPEND_PUBKEY_B "024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969"
#define STEALTH_ENCODE_LEADING0_PREFIX "000000001010"
#define STEALTH_ENCODE_BAADF00D_PREFIX "10111010101011011111000000001101"
#define STEALTH_ENCODE_MAX_PREFIX_LENGTH "11111111110000000000111111111100"

// expectations
#define STEALTH_ENCODE_ADDRESS_A "hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i"
#define STEALTH_ENCODE_ADDRESS_AM "5b4Xkx9DVQj5nznykpKLeoNWHes1ZHJh3aCvxNNXUTuErKTyYq8NKX3xNb3Q7xg"
#define STEALTH_ENCODE_ADDRESS_AB "vJmwY32eS5VDC2C4GaZyXt7i4iCjzSMZ1XSd6KbkA7QbGE492akT2eZZMjCwWDqKRSYhnSA8Bgp78KeAYFVCi8ke5mELdoYMBNep7L"
#define STEALTH_ENCODE_ADDRESS_AAB "vK4cs6xzzf326HyUeoJCQng6FXLVK27PyJoRbYSMyT9TzgKds8JDerKaRQ72q9kEp2tQNE2KRvabvqH5n5Rv6yv6Yht9uWNcbDGD7d"
#define STEALTH_ENCODE_ADDRESS_AAB1 "vK4cs6xzzf326HyUeoJCQng6FXLVK27PyJoRbYSMyT9TzgKds8JDerKaRQ72q9kEp2tQNE2KRvabvqH5n5Rv6yv6Yht9uWN7nyPnY7"
#define STEALTH_ENCODE_ADDRESS_AAB10 "JubEFUfmd2J3i83L9qWNr7fDSbb2bE7PY6RvEzH6wsNW8Ls7Mw3hxKZHWr3SvEz4o6NWLguFmyK9yBPrzxtC7ssTXQKJnyMUpL71mzBgd"
#define STEALTH_ENCODE_ADDRESS_AAB1P "71rNEn94Rfjj2byKuyqRzcPM4kq5Zdi4ZdEe6ZqxmjaaSz3VuUNXzhxiiXLRHnVmpzkTd8Z2KG92pUudhYqkW6DcYHVA4PRkNJEYtpfK2nML"
#define STEALTH_ENCODE_ADDRESS_AAB1PT "7AA4vX3ZmyjrQGxHEmTZaef4Smpm1PaXcqKKH3ybTbWqrwjRXZE3LLf26rCLRJdLkRDTkk2vRdtH4iEaZpVFoAboEpSh4QbgYy6Pt91Mt1UK"

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key__okay_output)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_ENCODE_ADDRESS_A "\n");
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key_spend_key__okay_output)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ENCODE_SPEND_PUBKEY_B } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(STEALTH_ENCODE_ADDRESS_AB "\n");
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key_2_spend_key__okay_output_error)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ENCODE_SPEND_PUBKEY_B } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE_EQUAL(output.str(), STEALTH_ENCODE_ADDRESS_AAB "\n");
    BOOST_REQUIRE_EQUAL(error.str(), BX_STEALTH_ENCODE_MULTISIG_NOT_SUPPORTED "\n");
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key_2_spend_key_1_signature__okay_output_error)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_signatures_option(1);
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ENCODE_SPEND_PUBKEY_B } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE_EQUAL(output.str(), STEALTH_ENCODE_ADDRESS_AAB1 "\n");
    BOOST_REQUIRE_EQUAL(error.str(), BX_STEALTH_ENCODE_MULTISIG_NOT_SUPPORTED "\n");
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key_2_spend_key_signatures_overflow__failure_error)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_signatures_option(42);
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ENCODE_SPEND_PUBKEY_B } });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_STEALTH_ENCODE_SIGNATURES_OVERFLOW "\n");
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key_max_prefix__okay_output_error)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_prefix_option({ STEALTH_ENCODE_MAX_PREFIX_LENGTH });
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE_EQUAL(output.str(), STEALTH_ENCODE_ADDRESS_AM "\n");
    /*BOOST_REQUIRE_EQUAL(error.str(), BX_STEALTH_ENCODE_PREFIX_NOT_SUPPORTED "\n");*/
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key_prefix_too_long__failure_errors)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_prefix_option({ STEALTH_ENCODE_MAX_PREFIX_LENGTH "1" });
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BOOST_REQUIRE_EQUAL(error.str(), /*BX_STEALTH_ENCODE_PREFIX_NOT_SUPPORTED "\n"*/ BX_STEALTH_ENCODE_PREFIX_TOO_LONG "\n");
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key_2_spend_key_1_signature_leading_0_prefix__okay_output_errors)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_signatures_option(1);
    command.set_prefix_option({ STEALTH_ENCODE_LEADING0_PREFIX });
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ENCODE_SPEND_PUBKEY_B } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE_EQUAL(output.str(), STEALTH_ENCODE_ADDRESS_AAB10 "\n");
    BOOST_REQUIRE_EQUAL(error.str(), BX_STEALTH_ENCODE_MULTISIG_NOT_SUPPORTED "\n" /*BX_STEALTH_ENCODE_PREFIX_NOT_SUPPORTED "\n"*/);
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key_2_spend_key_1_signaturebaadf00d_prefix__okay_output_errors)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_signatures_option(1);
    command.set_prefix_option({ STEALTH_ENCODE_BAADF00D_PREFIX });
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ENCODE_SPEND_PUBKEY_B } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE_EQUAL(output.str(), STEALTH_ENCODE_ADDRESS_AAB1P "\n");
    BOOST_REQUIRE_EQUAL(error.str(), BX_STEALTH_ENCODE_MULTISIG_NOT_SUPPORTED "\n" /*BX_STEALTH_ENCODE_PREFIX_NOT_SUPPORTED "\n"*/);
}

BOOST_AUTO_TEST_CASE(stealth_encode__invoke__scan_key_2_spend_key_1_signature_baadf00d_prefix_testnet__okay_output_errors)
{
    BX_DECLARE_COMMAND(stealth_encode);
    command.set_signatures_option(1);
    command.set_general_network_setting("testnet");
    command.set_prefix_option({ STEALTH_ENCODE_BAADF00D_PREFIX });
    command.set_scan_pubkey_argument({ STEALTH_ENCODE_SCAN_PUBKEY_A });
    command.set_spend_pubkeys_argument({ { STEALTH_ENCODE_SCAN_PUBKEY_A }, { STEALTH_ENCODE_SPEND_PUBKEY_B } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE_EQUAL(output.str(), STEALTH_ENCODE_ADDRESS_AAB1PT "\n");
    BOOST_REQUIRE_EQUAL(error.str(), BX_STEALTH_ENCODE_MULTISIG_NOT_SUPPORTED "\n" /*BX_STEALTH_ENCODE_PREFIX_NOT_SUPPORTED "\n"*/);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()