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
#include "command.hpp"

SX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(qrcode__invoke)

BOOST_AUTO_TEST_CASE(qrcode__invoke__invoke__always__failure_error)
{
    // $ sx qrcode
    SX_DECLARE_COMMAND(qrcode);
    SX_REQUIRE_FAILURE(command.invoke(output, error));
    SX_REQUIRE_ERROR(SX_QRCODE_NOT_IMPLEMENTED "\n");
}

BOOST_AUTO_TEST_SUITE_END()