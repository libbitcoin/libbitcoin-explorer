/*
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include "precompile.hpp"
#include "command.hpp"

SX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(stealth_address_decode__invoke)

BOOST_AUTO_TEST_CASE(stealth_address_decode__invoke__mainnet__okay_output)
{
    // $ sx stealth-address-decode hf2YiTUPjjFRvDw98ksxEgU7s8o8aDYsKuehLL68FsmnoQnU8ys8T1tX7
    SX_DECLARE_COMMAND(stealth_address_decode);
    command.set_stealth_address_argument({ "hf2YiTUPjjFRvDw98ksxEgU7s8o8aDYsKuehLL68FsmnoQnU8ys8T1tX7" });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n");
}

BOOST_AUTO_TEST_CASE(stealth_address_decode__invoke__testnet__okay_output)
{
    // $ sx stealth-address-decode idAsD84ZtoQdgfgDVmSitbYsJjrfUH4hB8j1ZMLvu2SeaLY4GDbAWrz9f
    SX_DECLARE_COMMAND(stealth_address_decode);
    command.set_stealth_address_argument({ "idAsD84ZtoQdgfgDVmSitbYsJjrfUH4hB8j1ZMLvu2SeaLY4GDbAWrz9f" });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n");
}

BOOST_AUTO_TEST_SUITE_END()