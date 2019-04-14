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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(fetch_balance__invoke)

// These amounts may change at any time, making these particular tests fragile.

// Vector: github.com/spesmilo/sx/blob/master/README.md
#define BX_FETCH_BALANCE_SX_DEMO1_KEY "a0e0be1350a3d3eaa3f381e3aa78f64d16e712c1bfffc7d7ca3b9b5f7409adf8" // 134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz
#define BX_FETCH_BALANCE_SX_DEMO1_KEY_XML \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"    \
"<balance><script_hash>a0e0be1350a3d3eaa3f381e3aa78f64d16e712c1bfffc7d7ca3b9b5f7409adf8</script_hash><received>100000</received><spent>100000</spent></balance>\n"

// Vector: github.com/spesmilo/sx/blob/master/README.md
#define BX_FETCH_BALANCE_SX_DEMO2_KEY "0550bf9055a9a10e453f7ee6cf584ab61307f64a62aa0b3dba11068cf4ac7efe" // 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe
#define BX_FETCH_BALANCE_SX_DEMO2_KEY_XML \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" \
"<balance><script_hash>0550bf9055a9a10e453f7ee6cf584ab61307f64a62aa0b3dba11068cf4ac7efe</script_hash><received>90000</received><spent>0</spent></balance>\n"

#define BX_FETCH_BALANCE_TESTNET_DEMO_KEY "1abf6c34c4370673aee3ce1c1e6c16de549cc6baa065ff3e4b23414b1dc2eca7" // n3GNqMveyvaPvUbH469vDRadqpJMPc84JA
#define BX_FETCH_BALANCE_TESTNET_DEMO_KEY_XML \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" \
"<balance><script_hash>1abf6c34c4370673aee3ce1c1e6c16de549cc6baa065ff3e4b23414b1dc2eca7</script_hash><received>5066930771</received><spent>5000000000</spent></balance>\n"

BOOST_AUTO_TEST_CASE(fetch_balance__invoke__mainnet_sx_demo1_xml__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_balance);
    command.set_format_option({ "xml" });
    command.set_hash_argument({ BX_FETCH_BALANCE_SX_DEMO1_KEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_BALANCE_SX_DEMO1_KEY_XML);
}

BOOST_AUTO_TEST_CASE(fetch_balance__invoke__mainnet_sx_demo2_xml__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_balance);
    command.set_format_option({ "xml" });
    command.set_hash_argument({ BX_FETCH_BALANCE_SX_DEMO2_KEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_BALANCE_SX_DEMO2_KEY_XML);
}

BOOST_AUTO_TEST_CASE(fetch_balance__invoke__testnet_demo_xml__okay_output)
{
    BX_DECLARE_CLIENT_TESTNET_COMMAND(fetch_balance);
    command.set_format_option({ "xml" });
    command.set_hash_argument({ BX_FETCH_BALANCE_TESTNET_DEMO_KEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_BALANCE_TESTNET_DEMO_KEY_XML);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
