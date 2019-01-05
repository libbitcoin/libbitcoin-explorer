/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(wrap_encode__invoke)

// vectors
#define BX_WRAP_ENCODE_PAYLOAD "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006"

// expectations
#define BX_WRAP_ENCODE_WRAPPED_V0 "00031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd0065b09d03c"
#define BX_WRAP_ENCODE_WRAPPED_V42 "2a031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006298eebe4"

BOOST_AUTO_TEST_CASE(wrap_encode__invoke__version_0__okay_output)
{
    BX_DECLARE_COMMAND(wrap_encode);
    command.set_payload_argument({ BX_WRAP_ENCODE_PAYLOAD });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_WRAP_ENCODE_WRAPPED_V0 "\n");
}

BOOST_AUTO_TEST_CASE(wrap_encode__invoke__version_42__okay_output)
{
    BX_DECLARE_COMMAND(wrap_encode);
    command.set_version_option(42);
    command.set_payload_argument({ BX_WRAP_ENCODE_PAYLOAD });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_WRAP_ENCODE_WRAPPED_V42 "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
