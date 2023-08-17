/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(bitcoin256__invoke)

BOOST_AUTO_TEST_CASE(bitcoin256__invoke__always__okay_output)
{
    BX_DECLARE_COMMAND(bitcoin256);
    command.set_base16_argument({ "900df00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("23429b4cc436b2ebd4aa33b904a1e08f195715c34d275e9088ea7b12af3872cd\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
