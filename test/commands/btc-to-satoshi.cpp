/**
 * Copyright (c) 2011-2018 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(btc_to_satoshi__invoke)

BOOST_AUTO_TEST_CASE(btc_to_satoshi__invoke__0_btc__okay_output)
{
    BX_DECLARE_COMMAND(commands::btc_to_satoshi);
    command.set_btc_argument({ "0" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0\n");
}

BOOST_AUTO_TEST_CASE(btc_to_satoshi__invoke__42_btc__okay_output)
{
    BX_DECLARE_COMMAND(commands::btc_to_satoshi);
    command.set_btc_argument({ "42" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("4200000000\n");
}

BOOST_AUTO_TEST_CASE(btc_to_satoshi__invoke__max_money_btc__okay_output)
{
    BX_DECLARE_COMMAND(commands::btc_to_satoshi);
    command.set_btc_argument({ "20999999.9769" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2099999997690000\n");
}

BOOST_AUTO_TEST_CASE(btc_to_satoshi__invoke__max_uint64_btc__okay_output)
{
    BX_DECLARE_COMMAND(commands::btc_to_satoshi);
    command.set_btc_argument({ "184467440737.09551615" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("18446744073709551615\n");
}

BOOST_AUTO_TEST_CASE(btc_to_satoshi__invoke__max_precision_btc__okay_output)
{
    BX_DECLARE_COMMAND(commands::btc_to_satoshi);
    command.set_btc_argument({ "1.99999999" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("199999999\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
