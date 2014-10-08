/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(embed_address__invoke)

// vectors
#define BX_ADDRESS_EMBED_A "Sataoshi Nakamoto"

// expectations
#define BX_ADDRESS_EMBED_A_V0 "1D4ovciLtDDCRAnbQV2uerN8W5YoD7gYkN"
#define BX_ADDRESS_EMBED_A_V42 "J7G9HBEShnfzmNeES72J27oAwGNR4HdLrF"

BOOST_AUTO_TEST_CASE(address_embed__invoke__version_0__okay_output)
{
    BX_DECLARE_COMMAND(address_embed);
    command.set_data_argument({ BX_ADDRESS_EMBED_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_EMBED_A_V0 "\n");
}

BOOST_AUTO_TEST_CASE(aaddress_embed__invoke__version_42__okay_output)
{
    BX_DECLARE_COMMAND(address_embed);
    command.set_version_option(42);
    command.set_data_argument({ BX_ADDRESS_EMBED_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_EMBED_A_V42 "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()