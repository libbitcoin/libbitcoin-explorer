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

BC_AUTO_TEST_SUITE(display_tests)

BC_AUTO_TEST_CASE(display__command_names__always__lists_commands)
{
    std::stringstream text;
    display_command_names(text);
    BC_REQUIRE_NE(text.str().find("address-decode"), std::string::npos);
}

BC_AUTO_TEST_CASE(display__command_names__always__omits_obsolete)
{
    std::stringstream text;
    display_command_names(text);
    BC_REQUIRE_EQUAL(text.str().find("wrap-encode"), std::string::npos);
}

BC_AUTO_TEST_CASE(display__connection_failure__always__names_endpoint)
{
    std::stringstream text;
    display_connection_failure(text, { "127.0.0.1:8333" });
    BC_REQUIRE_NE(text.str().find("127.0.0.1:8333"), std::string::npos);
}

BC_AUTO_TEST_CASE(display__invalid_command__no_superseding__names_command)
{
    std::stringstream text;
    display_invalid_command(text, "baadf00d");
    BC_REQUIRE_NE(text.str().find("baadf00d"), std::string::npos);
}

BC_AUTO_TEST_CASE(display__invalid_command__superseding__names_both)
{
    std::stringstream text;
    display_invalid_command(text, "wrap-encode", "checked-encode");
    BC_REQUIRE_NE(text.str().find("wrap-encode"), std::string::npos);
    BC_REQUIRE_NE(text.str().find("checked-encode"), std::string::npos);
}

BC_AUTO_TEST_CASE(display__invalid_parameter__option_message__strips_for_option)
{
    std::stringstream text;
    display_invalid_parameter(text, "the argument for option is invalid");
    BC_REQUIRE_NE(text.str().find("the argument is invalid"), std::string::npos);
}

BC_AUTO_TEST_CASE(display__usage__always__includes_command_names)
{
    std::stringstream text;
    display_usage(text);
    BC_REQUIRE_NE(text.str().find("address-decode"), std::string::npos);
}

BC_AUTO_TEST_SUITE_END()
