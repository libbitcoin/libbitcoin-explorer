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
BOOST_AUTO_TEST_SUITE(hd_new__invoke)

// github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-1
BOOST_AUTO_TEST_CASE(hd_new__invoke__vector_1_master__okay_output)
{
    BX_DECLARE_COMMAND(hd_new);
    command.set_seed_argument({ "000102030405060708090a0b0c0d0e0f" });
    command.set_general_testnet_setting(false);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi\n");
}

// github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-2
BOOST_AUTO_TEST_CASE(hd_new__invoke__vector_2_master__okay_output)
{
    BX_DECLARE_COMMAND(hd_new);
    command.set_seed_argument({ "fffcf9f6f3f0edeae7e4e1dedbd8d5d2cfccc9c6c3c0bdbab7b4b1aeaba8a5a29f9c999693908d8a8784817e7b7875726f6c696663605d5a5754514e4b484542" });
    command.set_general_testnet_setting(false);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprv9s21ZrQH143K31xYSDQpPDxsXRTUcvj2iNHm5NUtrGiGG5e2DtALGdso3pGz6ssrdK4PFmM8NSpSBHNqPqm55Qn3LqFtT2emdEXVYsCzC2U\n");
}

BOOST_AUTO_TEST_CASE(hd_new__invoke__128_bit_seed_mainnet__okay_output)
{
    BX_DECLARE_COMMAND(hd_new);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_general_testnet_setting(false);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprv9s21ZrQH143K3bJ7oEuyFtvSpSHmdsmfiPcDXX2RpArAvnuBwcUo8KbeNXLvdbBPgjeFdEpQCAuxLaAP3bJRiiTdw1Kx4chf9zSGp95KBBR\n");
}

// This particular command supports testnet without the need for recompilation.
BOOST_AUTO_TEST_CASE(hd_new__invoke__128_bit_seed_testnet__okay_output)
{
    BX_DECLARE_COMMAND(hd_new);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_general_testnet_setting(true);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("tprv8ZgxMBicQKsPeQXeTomURYYS8ZhysPog3wXLPwStJ9LeiPeGvypYe4y6HhWadxZi4BB2dLSAMXVkoRi8AoeNXmjETeYFiyRi56BhFnkm9uh\n");
}

BOOST_AUTO_TEST_CASE(hd_new__invoke__64_bit_seed_mainnet__failure_error)
{
    BX_DECLARE_COMMAND(hd_new);
    command.set_seed_argument({ "baadf00dbaadf00d" });
    command.set_general_testnet_setting(false);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_HD_NEW_SHORT_SEED "\n");
}

// This particular command supports testnet without the need for recompilation.
BOOST_AUTO_TEST_CASE(hd_new__invoke__64_bit_seed_testnet__failure_error)
{
    BX_DECLARE_COMMAND(hd_new);
    command.set_seed_argument({ "baadf00dbaadf00d" });
    command.set_general_testnet_setting(true);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_HD_NEW_SHORT_SEED "\n");
}

// TODO: what seed generates an invalid key so we can cover this code path?

//BOOST_AUTO_TEST_CASE(hd_new__invoke_128_bit_bad_seed__failure_error)
//{
//    BX_DECLARE_COMMAND(hd_new);
//    command.set_seed_argument({ "00000000000000000000000000000000" });
//    BX_REQUIRE_FAILURE(command.invoke(output, error));
//    BX_REQUIRE_ERROR(BX_HD_NEW_INVALID_KEY "\n");
//}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()