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

// A found command swaps the process stdio streams, which breaks the test
// runner on Windows, so only the unfound paths are dispatched here.
BC_AUTO_TEST_SUITE(dispatch_tests)

BC_AUTO_TEST_CASE(dispatch__dispatch__process_only__okay_usage)
{
    std::stringstream input, output, error;
    const char* argv[]{ "bx" };
    BC_REQUIRE_EQUAL(dispatch(1, argv, input, output, error), console_result::okay);
    BC_REQUIRE_NE(output.str().find("address-decode"), std::string::npos);
}

BC_AUTO_TEST_CASE(dispatch__dispatch__unknown_command__failure_error)
{
    std::stringstream input, output, error;
    const char* argv[]{ "bx", "baadf00d" };
    BC_REQUIRE_EQUAL(dispatch(2, argv, input, output, error), console_result::failure);
    BC_REQUIRE_NE(error.str().find("baadf00d"), std::string::npos);
}

BC_AUTO_TEST_CASE(dispatch__dispatch_command__unknown_command__failure_error)
{
    std::stringstream input, output, error;
    const char* argv[]{ "baadf00d" };
    BC_REQUIRE_EQUAL(dispatch_command(1, argv, input, output, error), console_result::failure);
    BC_REQUIRE(output.str().empty());
}

BC_AUTO_TEST_CASE(dispatch__dispatch_command__formerly_named__failure_names_superseding)
{
    std::stringstream input, output, error;
    const char* argv[]{ "pubkey" };
    BC_REQUIRE_EQUAL(dispatch_command(1, argv, input, output, error), console_result::failure);
    BC_REQUIRE_NE(error.str().find("ec-to-public"), std::string::npos);
}

// A dispatched command swaps the process stdio streams on Windows, which
// breaks the test runner, so these run only where that code is absent.
#if !defined(HAVE_WINDOWS)

BC_AUTO_TEST_CASE(dispatch__dispatch_command__found_command__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "btc-to-satoshi", "1" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE_EQUAL(output.str(), "100000000\n");
}

BC_AUTO_TEST_CASE(dispatch__dispatch_command__help_option__okay_help)
{
    std::stringstream input, output, error;
    const char* argv[]{ "btc-to-satoshi", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
}

BC_AUTO_TEST_CASE(dispatch__dispatch_command__invalid_parameter__failure_error)
{
    std::stringstream input, output, error;
    const char* argv[]{ "btc-to-satoshi", "--baadf00d" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::failure);
    BC_REQUIRE(!error.str().empty());
}

BC_AUTO_TEST_CASE(dispatch__dispatch_command__raw_input_command__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "base16-encode", "abc" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE_EQUAL(output.str(), "616263\n");
}

#endif


BC_AUTO_TEST_SUITE_END()
