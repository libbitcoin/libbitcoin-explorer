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

BC_AUTO_TEST_CASE(utility__load_input__shares__one_per_line)
{
    std::vector<explorer::config::share> shares;
    po::variables_map variables;
    std::stringstream input{ "shadow pistol academic always adequate wildlife fancy gross oasis cylinder mustang wrist rescue view short owner flip making coding armed\n\n  shadow pistol academic acid actress prayer class unknown daughter sweater depict flip twice unkind craft early superior advocate guest smoking  \n" };
    load_input(shares, "SHARE", variables, input);
    BC_REQUIRE_EQUAL(shares.size(), 2u);
    BC_REQUIRE_EQUAL(static_cast<const wallet::slip39&>(shares.front()).member_index(), 2u);
    BC_REQUIRE_EQUAL(static_cast<const wallet::slip39&>(shares.back()).member_index(), 0u);
}

BC_AUTO_TEST_CASE(utility__load_input__shares_loaded__unchanged)
{
    std::vector<explorer::config::share> shares;
    po::variables_map variables;
    variables.emplace("SHARE", po::variable_value{});
    std::stringstream input{ "shadow pistol academic always adequate wildlife fancy gross oasis cylinder mustang wrist rescue view short owner flip making coding armed\n" };
    load_input(shares, "SHARE", variables, input);
    BC_REQUIRE(shares.empty());
}

BC_AUTO_TEST_CASE(utility__load_input__invalid_share__throws_istream_exception)
{
    std::vector<explorer::config::share> shares;
    po::variables_map variables;
    std::stringstream input{ "foo bar baz\n" };
    BC_REQUIRE_THROW(load_input(shares, "SHARE", variables, input), istream_exception);
}

BC_AUTO_TEST_SUITE_END()
