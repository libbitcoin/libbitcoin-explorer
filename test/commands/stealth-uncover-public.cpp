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
BOOST_AUTO_TEST_SUITE(stealth_uncover_public__invoke)

// vectors

#define BX_STEALTH_UNCOVER_PUBLIC_SPEND_PUBKEY "024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969"

// receiver scenario
#define BX_STEALTH_UNCOVER_PUBLIC_SCAN_SECRET "af4afaeb40810e5f8abdbb177c31a2d310913f91cf556f5350bca10cbfe8b9ec"
#define BX_STEALTH_UNCOVER_PUBLIC_EPHEMERAL_PUBKEY "0247140d2811498679fe9a0467a75ac7aa581476c102d27377bc0232635af8ad36"

// payer scenario
#define BX_STEALTH_UNCOVER_PUBLIC_SCAN_PUBKEY "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006"
#define BX_STEALTH_UNCOVER_PUBLIC_EPHEMERAL_SECRET "8ed1d17dabce1fccbbe5e9bf008b318334e5bcc78eb9e7c1ea850b7eb0ddb9c8"

// expecatations (from BX_STEALTH_NEW_PUBLIC_KEY)
#define BX_STEALTH_UNCOVER_PUBLIC_STEALTH_PUBLIC_KEY "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5"

BOOST_AUTO_TEST_CASE(stealth_uncover_public__invoke__scenario_receiver__okay_output)
{
    BX_DECLARE_COMMAND(stealth_uncover_public);
    command.set_scan_secret_argument({ BX_STEALTH_UNCOVER_PUBLIC_SCAN_SECRET });
    command.set_spend_pubkey_argument({ BX_STEALTH_UNCOVER_PUBLIC_SPEND_PUBKEY });
    command.set_ephemeral_pubkey_argument({ BX_STEALTH_UNCOVER_PUBLIC_EPHEMERAL_PUBKEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_STEALTH_UNCOVER_PUBLIC_STEALTH_PUBLIC_KEY "\n");
}

BOOST_AUTO_TEST_CASE(stealth_uncover_public__invoke__scenario_payer__okay_output)
{
    BX_DECLARE_COMMAND(stealth_uncover_public);
    command.set_scan_secret_argument({ BX_STEALTH_UNCOVER_PUBLIC_EPHEMERAL_SECRET });
    command.set_spend_pubkey_argument({ BX_STEALTH_UNCOVER_PUBLIC_SPEND_PUBKEY });
    command.set_ephemeral_pubkey_argument({ BX_STEALTH_UNCOVER_PUBLIC_SCAN_PUBKEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_STEALTH_UNCOVER_PUBLIC_STEALTH_PUBLIC_KEY "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()