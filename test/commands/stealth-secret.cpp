/*
* Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
*
* This file is part of libbitcoin-explorer.
*
* libbitcoin-explorer is free software: you can redistribute it and/or
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

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(stealth_secret__invoke)

// vector
#define BX_STEALTH_SECRET_SPEND_SECRET "d39758028e201e8edf6d6eec6910ae4038f9b1db3f2d4e2d109ed833be94a026"
#define BX_STEALTH_SECRET_SHARED_SECRET "78dac4cad97b62efc67aff4890c3bc799815d144c5f93b171f559b43bca52590"

// expecatation
#define BX_STEALTH_SECRET_STEALTH_PRIVATE_KEY "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475"

BOOST_AUTO_TEST_CASE(stealth_secret__invoke__always__okay_output)
{
    BX_DECLARE_COMMAND(stealth_secret);
    command.set_spend_secret_argument({ BX_STEALTH_SECRET_SPEND_SECRET });
    command.set_shared_secret_argument({ BX_STEALTH_SECRET_SHARED_SECRET });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_STEALTH_SECRET_STEALTH_PRIVATE_KEY "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()