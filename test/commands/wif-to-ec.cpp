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
BOOST_AUTO_TEST_SUITE(wif_to_ec__invoke)

#ifndef ENABLE_TESTNET

BOOST_AUTO_TEST_CASE(wif_to_ec__invoke__mainnet_compressed_wif__okay_output)
{
    BX_DECLARE_COMMAND(wif_to_ec);
    command.set_wif_argument({ "L21LJEeJwK35wby1BeTjwWssrhrgQE2MZrpTm2zbMC677czAHHu3" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("8ed1d17dabce1fccbbe5e9bf008b318334e5bcc78eb9e7c1ea850b7eb0ddb9c8\n");
}

BOOST_AUTO_TEST_CASE(wif_to_ec__invoke__mainnet_uncompressed_wif__okay_output)
{
    BX_DECLARE_COMMAND(wif_to_ec);
    command.set_wif_argument({ "5JuBiWpsjfXNxsWuc39KntBAiAiAP2bHtrMGaYGKCppq4MuVcQL" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("8ed1d17dabce1fccbbe5e9bf008b318334e5bcc78eb9e7c1ea850b7eb0ddb9c8\n");
}

// vectors: en.bitcoin.it/wiki/Wallet_import_format

BOOST_AUTO_TEST_CASE(wif_to_ec__invoke__wiki__okay_output)
{
    BX_DECLARE_COMMAND(wif_to_ec);
    command.set_wif_argument({ "5HueCGU8rMjxEXxiPuD5BDku4MkFqeZyd4dZ1jvhTVqvbTLvyTJ" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0c28fca386c7a227600b2fe50b7cae11ec86d3bf1fbe471be89827e19d72aa1d\n");
}

#endif

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
