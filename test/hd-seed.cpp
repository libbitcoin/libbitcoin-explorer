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
#include <iostream>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <sx/sx.hpp>
#include "command.hpp"

SX_USING_NAMESPACES()

// This is a namespace for tests by class/file__method/function.
BOOST_AUTO_TEST_SUITE(hd_seed__invoke)

// private

BOOST_AUTO_TEST_CASE(hd_seed__invoke__default__okay_output)
{
    // $ sx hd-seed 900df00d
    SX_DECLARE_COMMAND(hd_seed);
    command.set_pubkey_option(false);
    command.set_seed_argument({ "900df00d" });
    command.set_general_testnet_setting(false);
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xprv9s21ZrQH143K27rVid1zpeyqZygAX7W7AQ4cctwrSB4A2EoPNT22nR2FCm42oc6UmTNGnjwLscDdkof6dyRVwoG8nU6uY8XTGNHiNzAx3TD\n");
}

// This particular command supports testnet without the need for recompilation.
BOOST_AUTO_TEST_CASE(hd_seed__invoke__testnet__okay_output)
{
    // $ sx hd-seed 900df00d
    SX_DECLARE_COMMAND(hd_seed);
    command.set_pubkey_option(false);
    command.set_seed_argument({ "900df00d" });
    command.set_general_testnet_setting(true);
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("tprv8ZgxMBicQKsPcw62PBsVzJbpt76NkdY7VwyjVKNJv9YdoqYUMpMnJAPh7wDgoyUo8tu3nqZ72xoSDfCqmBmSkrXjK7KDCVFWBU38pfSTUZ9\n");
}

// Random fill is not currently virtualized so test is limited.
BOOST_AUTO_TEST_CASE(hd_seed__invoke__random_testnet__okay)
{
    // $ sx hd-seed
    SX_DECLARE_COMMAND(hd_seed);
    command.set_pubkey_option(false);
    command.set_general_testnet_setting(true);
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
}

// Random fill is not currently virtualized so test is limited.
BOOST_AUTO_TEST_CASE(hd_seed__invoke__random__okay)
{
    // $ sx hd-seed
    SX_DECLARE_COMMAND(hd_seed);
    command.set_pubkey_option(false);
    command.set_general_testnet_setting(false);
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
}

// public

BOOST_AUTO_TEST_CASE(hd_seed__invoke__pubkey__okay_output)
{
    // $ sx hd-seed 900df00d -p
    SX_DECLARE_COMMAND(hd_seed);
    command.set_pubkey_option(true);
    command.set_seed_argument({ "900df00d" });
    command.set_general_testnet_setting(false);
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub661MyMwAqRbcEbvxpeZ1Bnva81WevaDxXczDRHMTzWb8u38XuzLHLDLj44q4Ssf3DJPC5cUN5ShTzh1o2zUhZwErn1j4HdJvZsQE8iD9vrB\n");
}

// This particular command supports testnet without the need for recompilation.
BOOST_AUTO_TEST_CASE(hd_seed__invoke__testnet_pubkey__okay_output)
{
    // $ sx hd-seed 900df00d -p
    SX_DECLARE_COMMAND(hd_seed);
    command.set_pubkey_option(true);
    command.set_seed_argument({ "900df00d" });
    command.set_general_testnet_setting(true);
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("tpubD6NzVbkrYhZ4WQ7pGqY6PiFwT8cJuxj25FaWmqQcLRM2eKoEzDBNUf1ZJ6uqyNcH1Cv6hBzEcYXWgsWQRrKwTNh9qcUMy9yA9pzdtj6wLax\n");
}

// Random fill is not currently virtualized so test is limited.
BOOST_AUTO_TEST_CASE(hd_seed__invoke__random_testnet_pubkey__okay)
{
    // $ sx hd-seed -p
    SX_DECLARE_COMMAND(hd_seed);
    command.set_pubkey_option(true);
    command.set_general_testnet_setting(true);
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
}

// Random fill is not currently virtualized so test is limited.
BOOST_AUTO_TEST_CASE(hd_seed__invoke__random_pubkey__okay)
{
    // $ sx hd-seed -p
    SX_DECLARE_COMMAND(hd_seed);
    command.set_pubkey_option(true);
    command.set_general_testnet_setting(false);
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
}

BOOST_AUTO_TEST_SUITE_END()