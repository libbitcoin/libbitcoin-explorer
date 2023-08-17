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

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(base58_encode__invoke)

BOOST_AUTO_TEST_CASE(base58_encode__invoke__base16_value__okay_output)
{
    BX_DECLARE_COMMAND(base58_encode);
    command.set_base16_argument({ "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("vYxp6yFC7qiVtK1RcGQQt3L6EqTc8YhEDLnSMLqDvp8D\n");
}

BOOST_AUTO_TEST_CASE(base58_encode__invoke__satoshi_nakamoto__okay_output)
{
    BX_DECLARE_COMMAND(base58_encode);
    command.set_base16_argument({ "5361746f736869204e616b616d6f746f" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("BJBRbygJtzBfp4gjJG2iqL\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
