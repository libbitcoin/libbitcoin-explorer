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
#include <bitcoin/explorer.hpp>

using namespace bc;
using namespace bc::explorer;

BC_AUTO_TEST_SUITE(define_tests)

BC_AUTO_TEST_CASE(define__program_name__always__bx)
{
    BC_REQUIRE_EQUAL(std::string{ BX_PROGRAM_NAME }, "bx");
}

BC_AUTO_TEST_CASE(define__environment_prefix__always__expected)
{
    BC_REQUIRE_EQUAL(std::string{ BX_ENVIRONMENT_VARIABLE_PREFIX }, "BX_");
}

BC_AUTO_TEST_CASE(define__settings_list__path_values__retained)
{
    const settings_list list{ { "wallet.version", "42" } };
    BC_REQUIRE_EQUAL(list.at("wallet.version"), "42");
}

BC_AUTO_TEST_SUITE_END()
