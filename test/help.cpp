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
#include <iostream>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <sx/sx.hpp>
#include "command.hpp"

SX_USING_NAMESPACES()

// This is a namespace for tests by class/file__method/function.
BOOST_AUTO_TEST_SUITE(help__invoke)

BOOST_AUTO_TEST_CASE(help__invoke__no_command__failure_error)
{
    // $ sx help
    SX_DECLARE_COMMAND(help);
    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
    SX_REQUIRE_ERROR("");
}

// TODO: generate this test and use localized symbol.
BOOST_AUTO_TEST_CASE(help__invoke__bogus_command__failure_error)
{
    // $ sx help booger
    SX_DECLARE_COMMAND(help);
    command.set_command_argument("booger");
    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
    SX_REQUIRE_ERROR("The word 'booger' is not a sx command. All commands:\n" \
        "addr\n" \
        "addr-decode\n" \
        "addr-embed\n" \
        "addr-encode\n" \
        "addr-validate\n" \
        "balance\n" \
        "base58-decode\n" \
        "base58-encode\n" \
        "base58check-decode\n" \
        "base58check-encode\n" \
        "bci-fetch-last-height\n" \
        "bci-history\n" \
        "bci-send-transaction\n" \
        "be-fetch-transaction\n" \
        "bitcoin160\n" \
        "bitcoin256\n" \
        "brainwallet\n" \
        "btc\n" \
        "ec-add\n" \
        "ec-add-secrets\n" \
        "ec-multiply\n" \
        "ec-multiply-secrets\n" \
        "ec-new\n" \
        "ec-to-pub\n" \
        "ec-to-wif\n" \
        "fetch-header\n" \
        "fetch-last-height\n" \
        "fetch-public-key\n" \
        "fetch-stealth\n" \
        "fetch-transaction\n" \
        "fetch-transaction-index\n" \
        "fetch-utxo\n" \
        "genaddr\n" \
        "genpriv\n" \
        "genpub\n" \
        "hd-new\n" \
        "hd-priv\n" \
        "hd-pub\n" \
        "hd-to-address\n" \
        "hd-to-wif\n" \
        "help\n" \
        "history\n" \
        "initchain\n" \
        "monitor\n" \
        "mpk\n" \
        "newseed\n" \
        "qrcode\n" \
        "ripemd160\n" \
        "satoshi\n" \
        "sha160\n" \
        "sha256\n" \
        "sha512\n" \
        "stealth-addr\n" \
        "unwrap\n" \
        "wallet\n" \
        "watchtx\n" \
        "wif-to-ec\n" \
        "wrap\n");
}

BOOST_AUTO_TEST_CASE(help__invoke__valid_command__okay_output)
{
    // $ sx help addr
    SX_DECLARE_COMMAND(help);
    command.set_command_argument("addr");
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("");
}

BOOST_AUTO_TEST_SUITE_END()