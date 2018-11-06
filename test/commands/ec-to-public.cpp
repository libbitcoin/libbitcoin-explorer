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
BOOST_AUTO_TEST_SUITE(ec_to_public__invoke)

// The keys are derived in the stealth scenario, confirm here that they are properly related.
#define BX_STEALTH_SCENARIO_PRIVATE_KEY "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475"
#define BX_STEALTH_SCENARIO_PUBLIC_KEY "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5"

BOOST_AUTO_TEST_CASE(ec_to_public__invoke__stealth_scenario__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_public);
    command.set_ec_private_key_argument({ BX_STEALTH_SCENARIO_PRIVATE_KEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_STEALTH_SCENARIO_PUBLIC_KEY "\n");
}

BOOST_AUTO_TEST_CASE(ec_to_public__invoke__compressed__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_public);
    command.set_uncompressed_option(false);
    command.set_ec_private_key_argument({ "8ed1d17dabce1fccbbe5e9bf008b318334e5bcc78eb9e7c1ea850b7eb0ddb9c8" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0247140d2811498679fe9a0467a75ac7aa581476c102d27377bc0232635af8ad36\n");
}

BOOST_AUTO_TEST_CASE(ec_to_public__invoke__uncompressed__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_public);
    command.set_uncompressed_option(true);
    command.set_ec_private_key_argument({ "8ed1d17dabce1fccbbe5e9bf008b318334e5bcc78eb9e7c1ea850b7eb0ddb9c8" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0447140d2811498679fe9a0467a75ac7aa581476c102d27377bc0232635af8ad36e87bb04f401be3b770a0f3e2267a6c3b14a3074f6b5ce4419f1fcdc1ca4b1cb6\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
