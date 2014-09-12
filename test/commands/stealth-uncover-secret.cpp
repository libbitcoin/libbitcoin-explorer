/*
* Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
*
* This file is part of libbitcoin_explorer.
*
* libbitcoin_explorer is free software: you can redistribute it and/or
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
// #include "precompile.hpp"
#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(stealth_uncover_secret__invoke)

// vectors
#define BX_STEALTH_UNCOVER_SECRET_SCAN_SECRET "af4afaeb40810e5f8abdbb177c31a2d310913f91cf556f5350bca10cbfe8b9ec"
#define BX_STEALTH_UNCOVER_SECRET_SPEND_SECRET "d39758028e201e8edf6d6eec6910ae4038f9b1db3f2d4e2d109ed833be94a026"
#define BX_STEALTH_UNCOVER_SECRET_EPHEMERAL_PUBKEY "0247140d2811498679fe9a0467a75ac7aa581476c102d27377bc0232635af8ad36"

// expecatations
#define BX_STEALTH_UNCOVER_SECRET_STEALTH_PRIVATE_KEY "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475"

BOOST_AUTO_TEST_CASE(stealth_uncover_secret__invoke__scenario__okay_output)
{
    BX_DECLARE_COMMAND(stealth_uncover_secret);
    command.set_scan_secret_argument({ BX_STEALTH_UNCOVER_SECRET_SCAN_SECRET });
    command.set_spend_secret_argument({ BX_STEALTH_UNCOVER_SECRET_SPEND_SECRET });
    command.set_ephemeral_pubkey_argument({ BX_STEALTH_UNCOVER_SECRET_EPHEMERAL_PUBKEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_STEALTH_UNCOVER_SECRET_STEALTH_PRIVATE_KEY "\n");
}

BOOST_AUTO_TEST_SUITE_END()