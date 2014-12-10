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

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(message_sign__invoke)

#ifndef ENABLE_TESTNET

#define MESSAGE_SIGN_WIF_COMPRESSED "KwE19y2Ud8EUEBjeUG4Uc4qWUJUUoZJxHR3xUfTpCSsJEDv2o8fu"
#define MESSAGE_SIGN_SIGNATURE_COMPRESSED "HxQp3cXgOIhBEGXks27sfeSQHVgNUeYgl5i5wG/dOUYaSIRnnzXR6NcyH+AfNAHtkWcyOD9rX4pojqmuQyH79K4="

#define MESSAGE_SIGN_WIF_UNCOMPRESSED "5HpMRgt5u8yyU1AfPwcgLGphD5Qu4ka4v7McE4jKrGNpQPyRqXC"
#define MESSAGE_SIGN_SIGNATURE_UNCOMPRESSED "GxQp3cXgOIhBEGXks27sfeSQHVgNUeYgl5i5wG/dOUYaSIRnnzXR6NcyH+AfNAHtkWcyOD9rX4pojqmuQyH79K4="

BOOST_AUTO_TEST_CASE(message_sign__invoke__compressed__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(message_sign);
    command.set_message_argument({ "Nakomoto" });
    command.set_wif_argument({ MESSAGE_SIGN_WIF_COMPRESSED });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(MESSAGE_SIGN_SIGNATURE_COMPRESSED "\n");
}

BOOST_AUTO_TEST_CASE(message_sign__invoke__uncompressed__okay_output)
{
    BX_DECLARE_NETWORK_COMMAND(message_sign);
    command.set_message_argument({ "Nakomoto" });
    command.set_wif_argument({ MESSAGE_SIGN_WIF_UNCOMPRESSED });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(MESSAGE_SIGN_SIGNATURE_UNCOMPRESSED "\n");
}

#endif

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()