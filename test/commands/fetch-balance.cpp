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

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(fetch_balance__invoke)

// BUGBUG: There is a summation error in
// ptree prop_tree(const std::vector<balance_row>

// These amounts may change at any time.
// If these change, notice whether Satoshi is spending or receiving.
#define BX_FETCH_BALANCE_FIRST_ADDRESS_INFO \
"address 1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa\n" \
"paid 0\n" \
"pending 6537136009\n" \
"received 1537136009\n"

// Vector: github.com/spesmilo/sx/blob/master/README.md
#define BX_FETCH_BALANCE_SX_DEMO1_ADDRESS "134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz"
#define BX_FETCH_BALANCE_SX_DEMO1_XML \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" \
"<address>134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz</address><paid>0</paid><pending>0</pending><received>100000</received>"

// Vector: github.com/spesmilo/sx/blob/master/README.md
#define BX_FETCH_BALANCE_SX_DEMO2_ADDRESS "13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe"
#define BX_FETCH_BALANCE_SX_DEMO2_XML \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" \
"<address>13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe</address><paid>0</paid><pending>90000</pending><received>90000</received>"

BOOST_AUTO_TEST_CASE(fetch_balance__invoke__mainnet_first_address_info__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_balance);
    command.set_format_option({ "info" });
    command.set_bitcoin_addresss_argument({ { BX_FIRST_ADDRESS } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_BALANCE_FIRST_ADDRESS_INFO);
}

BOOST_AUTO_TEST_CASE(fetch_balance__invoke__mainnet_sx_demo1_xml__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_balance);
    command.set_format_option({ "xml" });
    command.set_bitcoin_addresss_argument({ { BX_FETCH_BALANCE_SX_DEMO1_ADDRESS } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_BALANCE_SX_DEMO1_XML);
}

BOOST_AUTO_TEST_CASE(fetch_balance__invoke__mainnet_sx_demo2_xml__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(fetch_balance);
    command.set_format_option({ "xml" });
    command.set_bitcoin_addresss_argument({ { BX_FETCH_BALANCE_SX_DEMO2_ADDRESS } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_BALANCE_SX_DEMO2_XML);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()