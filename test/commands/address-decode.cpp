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

#include "command.hpp"

BX_USING_NAMESPACES()

BC_AUTO_TEST_SUITE(offline)
BC_AUTO_TEST_SUITE(address_decode__invoke)

BC_AUTO_TEST_CASE(address_decode__invoke__mainnet__okay_output)
{
    BX_DECLARE_COMMAND(address_decode);
    command.set_payment_address_argument({ "1HT7xU2Ngenf7D4yocz2SAcnNLW7rK8d4E" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("{\"wrapper\":{\"checksum\":2743498322,\"payload\":\"b472a266d0bd89c13706a4132ccfb16f7c3b9fcb\",\"version\":0}}\n");
}

BC_AUTO_TEST_CASE(address_decode__invoke__testnet__okay_output)
{
    BX_DECLARE_COMMAND(address_decode);
    command.set_payment_address_argument({ "mwy5FX7MVgDutKYbXBxQG5q7EL6pmhHT58" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("{\"wrapper\":{\"checksum\":1475514977,\"payload\":\"b472a266d0bd89c13706a4132ccfb16f7c3b9fcb\",\"version\":111}}\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
