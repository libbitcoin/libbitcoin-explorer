/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(hd_to_public__invoke)

// github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-1

BOOST_AUTO_TEST_CASE(hd_to_public__invoke__mainnet_vector_1__okay_output)
{
    BX_DECLARE_COMMAND(hd_to_public);
    command.set_version_option(76067358);
    command.set_hd_private_key_argument({ "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gZ29ESFjqJoCu1Rupje8YtGqsefD265TMg7usUDFdp6W1EGMcet8\n");
}

// github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-2

BOOST_AUTO_TEST_CASE(hd_to_public__invoke__mainnet_vector_2__okay_output)
{
    BX_DECLARE_COMMAND(hd_to_public);
    command.set_version_option(76067358);
    command.set_hd_private_key_argument({ "xprv9s21ZrQH143K31xYSDQpPDxsXRTUcvj2iNHm5NUtrGiGG5e2DtALGdso3pGz6ssrdK4PFmM8NSpSBHNqPqm55Qn3LqFtT2emdEXVYsCzC2U" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xpub661MyMwAqRbcFW31YEwpkMuc5THy2PSt5bDMsktWQcFF8syAmRUapSCGu8ED9W6oDMSgv6Zz8idoc4a6mr8BDzTJY47LJhkJ8UB7WEGuduB\n");
}

// testnet

BOOST_AUTO_TEST_CASE(hd_to_public__invoke__testnet__okay_output)
{
    BX_DECLARE_COMMAND(hd_to_public);
    command.set_version_option(70617039);
    command.set_hd_private_key_argument({ "tprv8ZgxMBicQKsPeQXeTomURYYS8ZhysPog3wXLPwStJ9LeiPeGvypYe4y6HhWadxZi4BB2dLSAMXVkoRi8AoeNXmjETeYFiyRi56BhFnkm9uh" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("tpubD6NzVbkrYhZ4XsZSMTS4pxCYhbDv2izadF87gTVBiR93Ysu3ZNe8pZaxTout4ifQXCUfp2wAChtcHNrbVka3KzfXNRM7gv9pwM57SB7AMFx\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
