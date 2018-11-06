/**
 * Copyright (c) 2011-2018 libbitcoin developers (see AUTHORS)
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

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(hd_to_ec__invoke)

BOOST_AUTO_TEST_CASE(hd_to_ec__invoke__mainnet_private_key__okay_output)
{
    BX_DECLARE_COMMAND(hd_to_ec);
    command.set_public_version_option(76067358);
    command.set_secret_version_option(76066276);
    command.set_hd_key_argument({ "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("e8f32e723decf4051aefac8e2c93c9c5b214313817cdb01a1494b917c8436b35\n");
}

BOOST_AUTO_TEST_CASE(hd_to_ec__invoke__mainnet_public_key__okay_output)
{
    BX_DECLARE_COMMAND(hd_to_ec);
    command.set_public_version_option(76067358);
    command.set_secret_version_option(76066276);
    command.set_hd_key_argument({ "xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gZ29ESFjqJoCu1Rupje8YtGqsefD265TMg7usUDFdp6W1EGMcet8" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0339a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c2\n");
}

// testnet

BOOST_AUTO_TEST_CASE(hd_to_ec__invoke__testnet_private_key__okay_output)
{
    BX_DECLARE_COMMAND(hd_to_ec);
    command.set_public_version_option(70617039);
    command.set_secret_version_option(70615956);
    command.set_hd_key_argument({ "tprv8ZgxMBicQKsPeQXeTomURYYS8ZhysPog3wXLPwStJ9LeiPeGvypYe4y6HhWadxZi4BB2dLSAMXVkoRi8AoeNXmjETeYFiyRi56BhFnkm9uh" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("8ed1d17dabce1fccbbe5e9bf008b318334e5bcc78eb9e7c1ea850b7eb0ddb9c8\n");
}

BOOST_AUTO_TEST_CASE(hd_to_ec__invoke__testnet_public_key__okay_output)
{
    BX_DECLARE_COMMAND(hd_to_ec);
    command.set_public_version_option(70617039);
    command.set_secret_version_option(70615956);
    command.set_hd_key_argument({ "tpubD9LPrAppw4effqYLPzG23WU3QwanZ63hVPcJXThtDrLL8NeB7qx1rZ1Lage8GLtHHjiJMNFhMS1pL6xBiM2MwpmBpZbDLXZxfUFEg9Fvh4t" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("029220af53b11605932e6101c962bdc752a234c6b0c2f0c398844e47b75503a692\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
