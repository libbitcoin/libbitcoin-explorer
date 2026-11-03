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
using namespace bc::explorer::commands;

BC_AUTO_TEST_SUITE(parser_tests)

BC_AUTO_TEST_CASE(parser__parse__help__true_help)
{
    ec_to_public command;
    std::string message;
    std::stringstream input;
    const char* argv[]{ "ec-to-public", "--help" };
    explorer::parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 2, argv));
    BC_REQUIRE(metadata.help());
}

BC_AUTO_TEST_CASE(parser__parse__unknown_option__false_message)
{
    ec_to_public command;
    std::string message;
    std::stringstream input;
    const char* argv[]{ "ec-to-public", "--baadf00d" };
    explorer::parser metadata(command);
    BC_REQUIRE(!metadata.parse(message, input, 2, argv));
    BC_REQUIRE(!message.empty());
    BC_REQUIRE(!metadata.help());
}

BC_AUTO_TEST_CASE(parser__parse__stdin_fallback__loads_argument)
{
    ec_to_public command;
    std::string message;
    std::stringstream input{ "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475" };
    const char* argv[]{ "ec-to-public" };
    explorer::parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, 1, argv));
    std::stringstream text;
    text << command.get_ec_private_key_argument();
    BC_REQUIRE_EQUAL(text.str(), "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475");
}

BC_AUTO_TEST_SUITE_END()
