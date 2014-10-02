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
BOOST_AUTO_TEST_SUITE(fetch_history__invoke)

// Vector: github.com/spesmilo/sx/blob/master/README.md
#define BX_FETCH_HISTORY_SX_DEMO_ADDRESS "134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz"
#define BX_FETCH_HISTORY_SX_DEMO_INFO \
"address 134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz\n" \
"histories\n" \
"{\n" \
"    history\n" \
"    {\n" \
"        value 100000\n" \
"        output\n" \
"        {\n" \
"            height 247683\n" \
"            point 97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1\n" \
"        }\n" \
"        input\n" \
"        {\n" \
"            height 247742\n" \
"            point b7354b8b9cc9a856aedaa349cffa289ae9917771f4e06b2386636b3c073df1b5:0\n" \
"        }\n" \
"    }\n" \
"}\n"

BOOST_AUTO_TEST_CASE(fetch_history__invoke__mainnet_sx_demo_info__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(bc::explorer::commands::fetch_history);
    command.set_format_option({ "info" });
    command.set_bitcoin_addresss_argument({ { BX_FETCH_HISTORY_SX_DEMO_ADDRESS } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_HISTORY_SX_DEMO_INFO);
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()