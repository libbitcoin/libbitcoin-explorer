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
using namespace bc::system;

BC_AUTO_TEST_SUITE(utility_tests)

BC_AUTO_TEST_CASE(utility__write_stream__number__serialized_with_terminator)
{
    std::stringstream text;
    write_stream(text, system::json::value{ 42 });
    BC_REQUIRE_EQUAL(text.str(), "42\n");
}

BC_AUTO_TEST_CASE(utility__write_stream__string__quoted)
{
    std::stringstream text;
    write_stream(text, system::json::value{ "baadf00d" });
    BC_REQUIRE_EQUAL(text.str(), "\"baadf00d\"\n");
}

BC_AUTO_TEST_SUITE_END()
