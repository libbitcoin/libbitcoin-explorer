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
#include "precompile.hpp"
#include "command.hpp"

SX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(hd_new__invoke)

BOOST_AUTO_TEST_CASE(hd_new__invoke__128_bit_seed_mainnet__okay_output)
{
    SX_DECLARE_COMMAND(hd_new);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_general_testnet_setting(false);
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("xprv9s21ZrQH143K3bJ7oEuyFtvSpSHmdsmfiPcDXX2RpArAvnuBwcUo8KbeNXLvdbBPgjeFdEpQCAuxLaAP3bJRiiTdw1Kx4chf9zSGp95KBBR\n");
}

// This particular command supports testnet without the need for recompilation.
BOOST_AUTO_TEST_CASE(hd_new__invoke__128_bit_seed_testnet__okay_output)
{
    SX_DECLARE_COMMAND(hd_new);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_general_testnet_setting(true);
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("tprv8ZgxMBicQKsPeQXeTomURYYS8ZhysPog3wXLPwStJ9LeiPeGvypYe4y6HhWadxZi4BB2dLSAMXVkoRi8AoeNXmjETeYFiyRi56BhFnkm9uh\n");
}

BOOST_AUTO_TEST_CASE(hd_new__invoke__64_bit_seed_mainnet__failure_error)
{
    SX_DECLARE_COMMAND(hd_new);
    command.set_seed_argument({ "baadf00dbaadf00db" });
    command.set_general_testnet_setting(false);
    SX_REQUIRE_FAILURE(command.invoke(output, error));
    SX_REQUIRE_ERROR(SX_HD_NEW_SHORT_SEED "\n");
}

// This particular command supports testnet without the need for recompilation.
BOOST_AUTO_TEST_CASE(hd_new__invoke__64_bit_seed_testnet__failure_error)
{
    SX_DECLARE_COMMAND(hd_new);
    command.set_seed_argument({ "baadf00dbaadf00db" });
    command.set_general_testnet_setting(true);
    SX_REQUIRE_FAILURE(command.invoke(output, error));
    SX_REQUIRE_ERROR(SX_HD_NEW_SHORT_SEED "\n");
}

// TODO: what seed generates an invalid key so we can cover this code path?

//BOOST_AUTO_TEST_CASE(hd_new__invoke_128_bit_bad_seed__failure_error)
//{
//    SX_DECLARE_COMMAND(hd_new);
//    command.set_seed_argument({ "00000000000000000000000000000000" });
//    SX_REQUIRE_FAILURE(command.invoke(output, error));
//    SX_REQUIRE_ERROR(SX_HD_NEW_INVALID_KEY "\n");
//}

BOOST_AUTO_TEST_SUITE_END()