/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(ec_address__invoke)

// Wiki Examples

BOOST_AUTO_TEST_CASE(ek_address__invoke__example_1_lot_sequence__okay)
{
    BX_DECLARE_COMMAND(ek_address);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_token_argument({ "passphrasecpXbDpHuo8F7yuZqR49koDA9uQojPijjjZaxsar7Woo9pfHJbeWF3VMU9EPBqJ" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1LoMVBxYZuzZZfTckU3JRccwFCMJYP3WRg\n");
}

BOOST_AUTO_TEST_CASE(ek_address__invoke__example_2__okay)
{
    BX_DECLARE_COMMAND(ek_address);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_token_argument({ "passphraseryQXuRZZQ3Jw5rAT7m6MzxkGSSRmysq3Ayj9vuEHEnbVPJSmRQ2xYFKDKjGYrq" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1DeDt7odeJqJvquJ6obEZfH1hfJHMvnURa\n");
}

BOOST_AUTO_TEST_CASE(ek_address__invoke__example_3_piped_commands__okay)
{
    BX_DECLARE_COMMAND(ek_address);
    command.set_seed_argument({ "7113f4c2e8f67b61225c9a619cd984b63f28df434bf18217" });
    command.set_token_argument({ "passphraseryQXuRZZQ3Jw5rAT7m6MzxkGSSRmysq3Ayj9vuEHEnbVPJSmRQ2xYFKDKjGYrq" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1DS3aqzg5w8bMsyzyutxcrhKoLZGjPnC13\n");
}

BOOST_AUTO_TEST_CASE(ek_address__invoke__example_4_invalid_seed__failure_error)
{
    BX_DECLARE_COMMAND(ek_address);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_token_argument({ "passphraseryQXuRZZQ3Jw5rAT7m6MzxkGSSRmysq3Ayj9vuEHEnbVPJSmRQ2xYFKDKjGYrq" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EK_ADDRESS_SHORT_SEED "\n");
}

BOOST_AUTO_TEST_CASE(ek_address__invoke__example_5_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_address);
    command.set_uncompressed_option(true);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_token_argument({ "passphraseryQXuRZZQ3Jw5rAT7m6MzxkGSSRmysq3Ayj9vuEHEnbVPJSmRQ2xYFKDKjGYrq" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1MydksvfdWNXM1KnVTS8A78M4b78aJcL1W\n");
}

BOOST_AUTO_TEST_CASE(ek_address__invoke__example_6_testnet__okay)
{
    BX_DECLARE_COMMAND(ek_address);
    command.set_version_option(111);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_token_argument({ "passphraseryQXuRZZQ3Jw5rAT7m6MzxkGSSRmysq3Ayj9vuEHEnbVPJSmRQ2xYFKDKjGYrq" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("mtABBAtcTLGZhxNupNZcPaVLZetzHVWgAp\n");
}

BOOST_AUTO_TEST_CASE(ek_address__invoke__example_7_testnet_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_address);
    command.set_version_option(111);
    command.set_uncompressed_option(true);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_token_argument({ "passphraseryQXuRZZQ3Jw5rAT7m6MzxkGSSRmysq3Ayj9vuEHEnbVPJSmRQ2xYFKDKjGYrq" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("n2Vb3w1eSXon87oQD2QVz2LfvahqVhBXKV\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
