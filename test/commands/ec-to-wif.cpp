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
BOOST_AUTO_TEST_SUITE(ec_to_wif__invoke)

BOOST_AUTO_TEST_CASE(ec_to_wif__invoke__mainnet_compressed_key__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_wif);
    command.set_version_option(128);
    command.set_uncompressed_option(false);
    command.set_ec_private_key_argument({ "8ed1d17dabce1fccbbe5e9bf008b318334e5bcc78eb9e7c1ea850b7eb0ddb9c8" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("L21LJEeJwK35wby1BeTjwWssrhrgQE2MZrpTm2zbMC677czAHHu3\n");
}

BOOST_AUTO_TEST_CASE(ec_to_wif__invoke__mainnet_uncompressed_key__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_wif);
    command.set_version_option(128);
    command.set_uncompressed_option(true);
    command.set_ec_private_key_argument({ "8ed1d17dabce1fccbbe5e9bf008b318334e5bcc78eb9e7c1ea850b7eb0ddb9c8" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("5JuBiWpsjfXNxsWuc39KntBAiAiAP2bHtrMGaYGKCppq4MuVcQL\n");
}

// vectors: en.bitcoin.it/wiki/Wallet_import_format

BOOST_AUTO_TEST_CASE(ec_to_wif__invoke__wiki_uncompressed_key__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_wif);
    command.set_version_option(128);
    command.set_uncompressed_option(true);
    command.set_ec_private_key_argument({ "0C28FCA386C7A227600B2FE50B7CAE11EC86D3BF1FBE471BE89827E19D72AA1D" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("5HueCGU8rMjxEXxiPuD5BDku4MkFqeZyd4dZ1jvhTVqvbTLvyTJ\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
