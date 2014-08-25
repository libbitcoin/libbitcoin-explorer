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

BOOST_AUTO_TEST_SUITE(stealth_uncover_public__invoke)

// vectors
#define SX_STEALTH_UNCOVER_PUBLIC_SCAN_SECRET "af4afaeb40810e5f8abdbb177c31a2d310913f91cf556f5350bca10cbfe8b9ec"
#define SX_STEALTH_UNCOVER_PUBLIC_SPEND_PUBKEY "024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969"
#define SX_STEALTH_UNCOVER_PUBLIC_EPHEMERAL_PUBKEY "0247140d2811498679fe9a0467a75ac7aa581476c102d27377bc0232635af8ad36"

// expecatations (from SX_STEALTH_NEW_PUBLIC_KEY)
#define SX_STEALTH_UNCOVER_PUBLIC_STEALTH_PUBLIC_KEY "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5"

BOOST_AUTO_TEST_CASE(stealth_uncover_public__invoke__scenario__okay_output)
{
    SX_DECLARE_COMMAND(stealth_uncover_public);
    command.set_scan_secret_argument({ SX_STEALTH_UNCOVER_PUBLIC_SCAN_SECRET });
    command.set_spend_pubkey_argument({ SX_STEALTH_UNCOVER_PUBLIC_SPEND_PUBKEY });
    command.set_ephemeral_pubkey_argument({ SX_STEALTH_UNCOVER_PUBLIC_EPHEMERAL_PUBKEY });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT(SX_STEALTH_UNCOVER_PUBLIC_STEALTH_PUBLIC_KEY "\n");
}

BOOST_AUTO_TEST_SUITE_END()