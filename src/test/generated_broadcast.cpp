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
#include <memory>
#include <boost/test/unit_test.hpp>
#include <sx/sx.hpp>

using namespace sx::extensions;

BOOST_AUTO_TEST_SUITE(test_suite)

BOOST_AUTO_TEST_CASE(broadcast_returns_true)
{
    // TODO: mocks and dependency injection required to test proper execution.
    auto func = [](std::shared_ptr<sx::command> sx_command) -> void {};
    BOOST_REQUIRE(broadcast(func));
}

BOOST_AUTO_TEST_SUITE_END()