/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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

BOOST_AUTO_TEST_SUITE(base58check_encode__invoke)

// vectors
#define BX_BASE58CHECK_ENCODE_PAYLOAD "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006"

// expectations
#define BX_BASE58CHECK_ENCODE_ENCODED_V0 "173RKgkk7fMbYUYBGyyAHeZ6rwfKRMn17h7DtGsmpEdab8TV6UB"
#define BX_BASE58CHECK_ENCODE_ENCODED_V42 "7DTXS6pY6a98XH2oQTZUbbd1Z7P4NzkJqfraixprPutXQVTkwBGw"

BOOST_AUTO_TEST_CASE(base58check_encode__invoke__version_0__okay_output)
{
    BX_DECLARE_COMMAND(base58check_encode);
    command.set_base16_argument({ BX_BASE58CHECK_ENCODE_PAYLOAD });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_BASE58CHECK_ENCODE_ENCODED_V0 "\n");
}

BOOST_AUTO_TEST_CASE(base58check_encode__invoke__version_42__okay_output)
{
    BX_DECLARE_COMMAND(base58check_encode);
    command.set_version_option(42);
    command.set_base16_argument({ BX_BASE58CHECK_ENCODE_PAYLOAD });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_BASE58CHECK_ENCODE_ENCODED_V42 "\n");
}

BOOST_AUTO_TEST_SUITE_END()