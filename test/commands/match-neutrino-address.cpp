/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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

// Sponsored in part by Digital Contract Design, LLC

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(match_neutrino_address__invoke)

BOOST_AUTO_TEST_CASE(match_neutrino_address__invoke__match)
{
    BX_DECLARE_COMMAND(match_neutrino_address);
    const std::string filter(
        "006a368420a2ea3451d21bd68edc9e6176ccfdc785a707"
        "ff0424eb3cfd00000000230db414c859a07e8205876354"
        "a210a75042d0463404913d61a8e068e58a3ae2aa080026");

    command.set_compact_filter_argument({ filter });
    const std::string address("mfXcDNV1r9SPmNVziJoNG4CXFjx5Gn1BTi");
    command.set_address_argument({ address });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FILTER_MATCH_ADDRESS_SUCCESS "\n");
}

BOOST_AUTO_TEST_CASE(match_neutrino_address__invoke__no_match)
{
    BX_DECLARE_COMMAND(match_neutrino_address);
    const std::string filter(
        "006a368420a2ea3451d21bd68edc9e6176ccfdc785a707"
        "ff0424eb3cfd00000000230db414c859a07e8205876354"
        "a210a75042d0463404913d61a8e068e58a3ae2aa080026");

    command.set_compact_filter_argument({ filter });
    const std::string address("mfXcDNV1r9SPmNVEba34DG7CWrLEaRzKm3");
    command.set_address_argument({ address });
    BX_REQUIRE_INVALID(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FILTER_MATCH_ADDRESS_FAILURE "\n");
}

BOOST_AUTO_TEST_CASE(match_neutrino_address__invoke__invalid_filter_type)
{
    BX_DECLARE_COMMAND(match_neutrino_address);
    const std::string filter(
        "016a368420a2ea3451d21bd68edc9e6176ccfdc785a707"
        "ff0424eb3cfd00000000230db414c859a07e8205876354"
        "a210a75042d0463404913d61a8e068e58a3ae2aa080026");

    command.set_compact_filter_argument({ filter });
    const std::string address("mfXcDNV1r9SPmNVEba34DG7CWrLEaRzKm3");
    command.set_address_argument({ address });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FILTER_TYPE_UNRECOGNIZED "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
