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

BOOST_AUTO_TEST_SUITE(hd_to_wif__invoke)

BOOST_AUTO_TEST_CASE(hd_to_wif__invoke__mainnet_key__okay_output)
{
    // $ sx hd-to-wif xprv9s21ZrQH143K27rVid1zpeyqZygAX7W7AQ4cctwrSB4A2EoPNT22nR2FCm42oc6UmTNGnjwLscDdkof6dyRVwoG8nU6uY8XTGNHiNzAx3TD
    SX_DECLARE_COMMAND(hd_to_wif);
    command.set_hd_private_key_argument({ "xprv9s21ZrQH143K27rVid1zpeyqZygAX7W7AQ4cctwrSB4A2EoPNT22nR2FCm42oc6UmTNGnjwLscDdkof6dyRVwoG8nU6uY8XTGNHiNzAx3TD" });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("KxL385uvhm2PhgTjk6gvHPE81xNwCDd1WeQXPMR4DMZfVNJRSvwF\n");
}

BOOST_AUTO_TEST_SUITE_END()