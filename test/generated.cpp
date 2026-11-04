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

BC_AUTO_TEST_SUITE(generated_tests)

BC_AUTO_TEST_CASE(generated__find__unknown_symbol__nullptr)
{
    BC_REQUIRE(find("baadf00d") == nullptr);
}

BC_AUTO_TEST_CASE(generated__formerly__unknown_name__empty)
{
    BC_REQUIRE(formerly("baadf00d").empty());
}

BC_AUTO_TEST_CASE(generated__formerly__former_name__superseding_symbol)
{
    BC_REQUIRE_EQUAL(formerly("pubkey"), "ec-to-public");
}

BC_AUTO_TEST_CASE(generated__broadcast__always__visits_every_command)
{
    size_t count{};
    const auto accumulate = [&count](std::shared_ptr<command>) { ++count; };
    broadcast(accumulate);
    BC_REQUIRE_EQUAL(count, 121u);
}

BC_AUTO_TEST_SUITE_END()
