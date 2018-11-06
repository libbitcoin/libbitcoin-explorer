/**
* Copyright (c) 2011-2018 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(stealth_public__invoke)

// vector
#define BX_STEALTH_PUBLIC_SPEND_PUBKEY "024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969"
#define BX_STEALTH_PUBLIC_SHARED_SECRET "78dac4cad97b62efc67aff4890c3bc799815d144c5f93b171f559b43bca52590"

// expecatation
#define BX_STEALTH_PUBLIC_STEALTH_PUBLIC_KEY "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5"

BOOST_AUTO_TEST_CASE(stealth_public__invoke__always__okay_output)
{
    BX_DECLARE_COMMAND(stealth_public);
    command.set_shared_secret_argument({ BX_STEALTH_PUBLIC_SHARED_SECRET });
    command.set_spend_pubkey_argument({ BX_STEALTH_PUBLIC_SPEND_PUBKEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_STEALTH_PUBLIC_STEALTH_PUBLIC_KEY "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
