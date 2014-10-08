/**
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
#ifndef SETUP_HPP
#define SETUP_HPP

#include <iostream>
#include <locale>
#include <string>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <bitcoin/explorer.hpp>

#define BX_USING_NAMESPACES()
using namespace bc; \
using namespace bc::client; \
using namespace bc::explorer; \
using namespace bc::explorer::commands; \
using namespace bc::explorer::primitives;

// Server error messsages.
#define BX_TIMEOUT_MESSAGE "timed out"
#define BX_BAD_STREAM_MESSAGE "Bad stream"
#define BX_SERVICE_STOPPED_MESSAGE "Service stopped"
#define BX_SPENT_INPUT_NOT_FOUND_MESSAGE "Spent input not found"
#define BX_TX_NOT_FOUND_MESSAGE "Transaction inputs or outputs are empty"
#define BX_MEMPOOL_COINBASE_TX_MESSAGE "Memory pool coinbase transaction"
#define BX_MATCHING_PREVIOUS_OBJECT_MESSAGE "Matching previous object found"
#define BX_VALIDATION_OF_INPUTS_FAILED "Validation of inputs failed"

// Genesis block hash, transaction, address.
#define BX_FIRST_ADDRESS \
"1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa"
#define BX_GENESIS_BLOCK_HASH \
"000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"
#define BX_SATOSHIS_WORDS_TX_HASH \
"4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"
#define BX_SATOSHIS_WORDS_TX_BASE16 \
"01000000010000000000000000000000000000000000000000000000000000000000000000ffffffff4d04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73ffffffff0100f2052a01000000434104678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5fac00000000"

// Default network parameters.
#define BX_NETWORK_RETRY 0
#define BX_NETWORK_WAIT 2000
#define BX_MAINNET_HOST "72.74.150.204"
#define BX_MAINNET_PORT 8333
//#define BX_TESTNET_HOST ""
//#define BX_TESTNET_PORT 18333

// Development
//#define BX_MAINNET_SERVER "tcp://obelisk.unsystem.net:9091"       // timeout
//#define BX_MAINNET_SERVER "tcp://obelisk.unsystem.net:8081"       // timeout

// Production
//#define BX_MAINNET_SERVER "tcp://obelisk.coinkite.com:9091"       // alive
//#define BX_MAINNET_SERVER "tcp://obelisk.bysh.me:9091"            // timeout
//#define BX_MAINNET_SERVER "tcp://obelisk.ottrbutt.com:9091"       // timeout
#define BX_MAINNET_SERVER "tcp://obelisk-baltic.airbitz.co:9091"    // alive
//#define BX_MAINNET_SERVER "tcp://obelisk-crate.airbitz.co:9091"   // alive
//#define BX_MAINNET_SERVER "tcp://obelisk-sol.airbitz.co:9091"     // alive
//#define BX_MAINNET_SERVER "tcp://obelisk-virpus.airbitz.co:9091"  // alive

// Testing
//#define BX_MAINNET_SERVER "tcp://37.139.11.99:9091"               // timeout

// Testnet
//#define BX_TESTNET_SERVER "tcp://178.79.185.162:9091"             // timeout
//#define BX_TESTNET_SERVER "tcp://85.25.198.97:10091"              // alive
#define BX_TESTNET_SERVER "tcp://obelisk-testnet.airbitz.co:9091"   // alive
//#define BX_TESTNET_SERVER "tcp://preacher.veox.pw:9091"           // alive

#define BX_DECLARE_COMMAND(extension) \
    std::stringstream output, error; \
    extension command

#define BX_DECLARE_NETWORK_COMMAND(extension) \
    BX_DECLARE_COMMAND(extension); \
    command.set_general_retries_setting(BX_NETWORK_RETRY); \
    command.set_general_wait_setting(BX_NETWORK_WAIT); \
    command.set_server_address_setting(BX_MAINNET_SERVER)

// serializer results
#define BX_SERIALIZE_COPY_ROUND_TRIP(serializer, value) \
    serializer original; \
    stringstream output, input(value); \
    input >> original; \
    serializer copy(original); \
    output << copy; \
    BOOST_REQUIRE_EQUAL(output.str(), value)

// console results
#define BX_REQUIRE_OKAY(value) \
    BOOST_REQUIRE_EQUAL(value, console_result::okay)
#define BX_REQUIRE_FAILURE(value) \
    BOOST_REQUIRE_EQUAL(value, console_result::failure)
#define BX_REQUIRE_INVALID(value) \
    BOOST_REQUIRE_EQUAL(value, console_result::invalid)

// stream results
#define BX_REQUIRE_ERROR(value) \
    BOOST_REQUIRE_EQUAL(error.str(), value); \
    BOOST_REQUIRE_EQUAL(output.str(), "")
#define BX_REQUIRE_OUTPUT(value) \
    BOOST_REQUIRE_EQUAL(output.str(), value); \
    BOOST_REQUIRE_EQUAL(error.str(), "")

// exceptions
#define BX_REQUIRE_THROW_INVALID_OPTION_VALUE(expression) \
    BOOST_REQUIRE_THROW(expression, po::invalid_option_value)

#endif