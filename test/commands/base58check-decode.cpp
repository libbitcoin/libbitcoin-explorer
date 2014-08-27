/*
 * Copyright (c)2011-2014 libbitcoin developers (see AUTHORS)
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
#include "precompile.hpp"
#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(base58check_decode__invoke)

// vectors
#define BX_BASE58CHECK_DECODE_WRAPPED_V0 "173RKgkk7fMbYUYBGyyAHeZ6rwfKRMn17h7DtGsmpEdab8TV6UB"
#define BX_BASE58CHECK_DECODE_WRAPPED_V42 "7DTXS6pY6a98XH2oQTZUbbd1Z7P4NzkJqfraixprPutXQVTkwBGw"

// expectations
#define BX_WRAP_DECODE_UNWRAPPED_V0 \
    "wrapper\n" \
    "{\n" \
    "    checksum 1020266843\n" \
    "    payload 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    version 0\n" \
    "}\n"
#define BX_WRAP_DECODE_UNWRAPPED_V42 \
    "wrapper\n" \
    "{\n" \
    "    checksum 3840642601\n" \
    "    payload 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
    "    version 42\n" \
    "}\n"

BOOST_AUTO_TEST_CASE(base58check_decode__invoke__version_0__okay_output)
{
    BX_DECLARE_COMMAND(base58check_decode);
    command.set_base58check_argument({ BX_BASE58CHECK_DECODE_WRAPPED_V0 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_WRAP_DECODE_UNWRAPPED_V0);
}

BOOST_AUTO_TEST_CASE(base58check_decode__invoke__version_42__okay_output)
{
    BX_DECLARE_COMMAND(base58check_decode);
    command.set_base58check_argument({ BX_BASE58CHECK_DECODE_WRAPPED_V42 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_WRAP_DECODE_UNWRAPPED_V42);
}

BOOST_AUTO_TEST_SUITE_END()