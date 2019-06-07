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

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(ec_to_witness__invoke)

BOOST_AUTO_TEST_CASE(ec_to_witness__invoke__p2wpkh_key__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_witness);
    command.set_ec_public_key_argument({ "0279be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bc1qw508d6qejxtdg4y5r3zarvary0c5xw7kv8f3t4\n");
}

BOOST_AUTO_TEST_CASE(ec_to_witness__invoke__p2wpkh_key_prefix_tb__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_witness);
    command.set_prefix_option({ "tb" });
    command.set_ec_public_key_argument({ "0279be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("tb1qw508d6qejxtdg4y5r3zarvary0c5xw7kxpjzsx\n");
}

BOOST_AUTO_TEST_CASE(ec_to_witness__invoke__key__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_witness);
    command.set_ec_public_key_argument({ "038262a6c6cec93c2d3ecd6c6072efea86d02ff8e3328bbd0242b20af3425990ac" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bc1qr47dd36u96r0fjle36hdygdnp0v6pwfg2lppam\n");
}

BOOST_AUTO_TEST_CASE(ec_to_witness__invoke__key_prefix_tb__okay_output)
{
    BX_DECLARE_COMMAND(ec_to_witness);
    command.set_ec_public_key_argument({ "038262a6c6cec93c2d3ecd6c6072efea86d02ff8e3328bbd0242b20af3425990ac" });
    command.set_prefix_option({ "tb" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("tb1qr47dd36u96r0fjle36hdygdnp0v6pwfgqe6jxg\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
