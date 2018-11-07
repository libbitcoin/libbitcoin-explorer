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
BOOST_AUTO_TEST_SUITE(embed_address__invoke)

// vectors
#define BX_ADDRESS_EMBED_A "Satoshi Nakamoto"

// expectations
#define BX_ADDRESS_EMBED_A_V0 "168LnUjqoJLie1PW5dTaF2vKUU9Jf6Fe4a"
#define BX_ADDRESS_EMBED_A_V111 "mkeJ5XppcKmyR7s7oCRx4x8eLTk1Xrso8t"

BOOST_AUTO_TEST_CASE(address_embed__invoke__mainnet__okay_output)
{
    BX_DECLARE_COMMAND(address_embed);
    command.set_data_argument({ BX_ADDRESS_EMBED_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_EMBED_A_V0 "\n");
}

BOOST_AUTO_TEST_CASE(address_embed__invoke__testnet__okay_output)
{
    BX_DECLARE_COMMAND(address_embed);
    command.set_version_option(111);
    command.set_data_argument({ BX_ADDRESS_EMBED_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_EMBED_A_V111 "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
