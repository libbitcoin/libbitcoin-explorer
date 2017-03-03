/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(fetch_history__invoke)

// Vector: github.com/spesmilo/sx/blob/master/README.md
#define BX_FETCH_HISTORY_SX_DEMO1_ADDRESS "134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz"
#define BX_FETCH_HISTORY_SX_DEMO1_INFO \
"transfers\n" \
"{\n" \
"    transfer\n" \
"    {\n" \
"        received\n" \
"        {\n" \
"            hash 97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3\n" \
"            height 247683\n" \
"            index 1\n" \
"        }\n" \
"        spent\n" \
"        {\n" \
"            hash b7354b8b9cc9a856aedaa349cffa289ae9917771f4e06b2386636b3c073df1b5\n" \
"            height 247742\n" \
"            index 0\n" \
"        }\n" \
"        value 100000\n" \
"    }\n" \
"}\n"

// Vector: github.com/spesmilo/sx/blob/master/README.md
#define BX_FETCH_HISTORY_SX_DEMO2_ADDRESS "13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe"
#define BX_FETCH_HISTORY_SX_DEMO2_INFO \
"transfers\n" \
"{\n" \
"    transfer\n" \
"    {\n" \
"        received\n" \
"        {\n" \
"            hash b7354b8b9cc9a856aedaa349cffa289ae9917771f4e06b2386636b3c073df1b5\n" \
"            height 247742\n" \
"            index 0\n" \
"        }\n" \
"        value 90000\n" \
"    }\n" \
"}\n"

BOOST_AUTO_TEST_CASE(fetch_history__invoke__mainnet_sx_demo1_info__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::fetch_history);
    command.set_payment_address_argument({ BX_FETCH_HISTORY_SX_DEMO1_ADDRESS });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_HISTORY_SX_DEMO1_INFO);
}

BOOST_AUTO_TEST_CASE(fetch_history__invoke__mainnet_sx_demo2_info__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::fetch_history);
    command.set_format_option({ "info" });
    command.set_payment_address_argument({ BX_FETCH_HISTORY_SX_DEMO2_ADDRESS });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_HISTORY_SX_DEMO2_INFO);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
