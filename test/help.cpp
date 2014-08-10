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

BOOST_AUTO_TEST_SUITE(help__invoke)

BOOST_AUTO_TEST_CASE(help__invoke__no_command__failure_error)
{
    // $ sx help
    SX_DECLARE_COMMAND(help);
    SX_REQUIRE_FAILURE(command.invoke(output, error));
    SX_REQUIRE_ERROR("");
}

BOOST_AUTO_TEST_CASE(help__invoke__bogus_command__failure)
{
    // $ sx help booger
    SX_DECLARE_COMMAND(help);
    command.set_command_argument("booger");
    SX_REQUIRE_FAILURE(command.invoke(output, error));
    //SX_REQUIRE_ERROR("The word 'booger' is not a sx command. All commands:\n" \
    //    "addr-decode\n" \
    //    "addr-embed\n" \
    //    "addr-encode\n" \
    //    "addr-validate\n" \
    //    "balance\n" \
    //    "base58-decode\n" \
    //    "base58-encode\n" \
    //    "base58check-decode\n" \
    //    "base58check-encode\n" \
    //    "bci-fetch-last-height\n" \
    //    "bci-history\n" \
    //    "bci-send-transaction\n" \
    //    "be-fetch-transaction\n" \
    //    "bitcoin160\n" \
    //    "bitcoin256\n" \
    //    "btc\n" \
    //    "ec-add\n" \
    //    "ec-add-secrets\n" \
    //    "ec-lock\n" \
    //    "ec-multiply\n" \
    //    "ec-multiply-secrets\n" \
    //    "ec-new\n" \
    //    "ec-to-addr\n" \
    //    "ec-to-pub\n" \
    //    "ec-to-wif\n" \
    //    "ec-unlock\n" \
    //    "fetch-header\n" \
    //    "fetch-last-height\n" \
    //    "fetch-public-key\n" \
    //    "fetch-stealth\n" \
    //    "fetch-transaction\n" \
    //    "fetch-transaction-index\n" \
    //    "fetch-utxo\n" \
    //    "genaddr\n" \
    //    "genpriv\n" \
    //    "genpub\n" \
    //    "hd-new\n" \
    //    "hd-priv\n" \
    //    "hd-pub\n" \
    //    "hd-to-addr\n" \
    //    "hd-to-ec\n" \
    //    "hd-to-pub\n" \
    //    "hd-to-wif\n" \
    //    "help\n" \
    //    "history\n" \
    //    "initchain\n" \
    //    "mnemonic-decode\n" \
    //    "mnemonic-encode\n" \
    //    "monitor\n" \
    //    "mpk\n" \
    //    "newseed\n" \
    //    "qrcode\n" \
    //    "rawscript\n" \
    //    "ripemd160\n" \
    //    "satoshi\n" \
    //    "scripthash\n" \
    //    "seed\n" \
    //    "sendtx-node\n" \
    //    "sendtx-obelisk\n" \
    //    "sendtx-p2p\n" \
    //    "sha160\n" \
    //    "sha256\n" \
    //    "sha512\n" \
    //    "signtx\n" \
    //    "stealth-addr\n" \
    //    "unwrap\n" \
    //    "validtx\n" \
    //    "wallet\n" \
    //    "watchtx\n" \
    //    "wif-to-ec\n" \
    //    "wif-to-pub\n" \
    //    "wrap\n");
}

BOOST_AUTO_TEST_CASE(help__invoke__valid_command__okay_output)
{
    // $ sx help help
    SX_DECLARE_COMMAND(help);
    command.set_command_argument("help");
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("");
}

BOOST_AUTO_TEST_SUITE_END()