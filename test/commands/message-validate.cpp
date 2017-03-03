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
BOOST_AUTO_TEST_SUITE(message_validate__invoke)

#define MESSAGE_VALIDATE_ADDRESS_COMPRESSED "1PeChFbhxDD9NLbU21DfD55aQBC4ZTR3tE"
#define MESSAGE_VALIDATE_SIGNATURE_COMPRESSED "HxQp3cXgOIhBEGXks27sfeSQHVgNUeYgl5i5wG/dOUYaSIRnnzXR6NcyH+AfNAHtkWcyOD9rX4pojqmuQyH79K4="

#define MESSAGE_VALIDATE_ADDRESS_UNCOMPRESSED "1Em1SX7qQq1pTmByqLRafhL1ypx2V786tP"
#define MESSAGE_VALIDATE_SIGNATURE_UNCOMPRESSED "GxQp3cXgOIhBEGXks27sfeSQHVgNUeYgl5i5wG/dOUYaSIRnnzXR6NcyH+AfNAHtkWcyOD9rX4pojqmuQyH79K4="

BOOST_AUTO_TEST_CASE(message_validate__invoke__compressed__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(message_validate);
    command.set_message_argument({ "Nakomoto" });
    command.set_signature_argument({ MESSAGE_VALIDATE_SIGNATURE_COMPRESSED });
    command.set_payment_address_argument({ MESSAGE_VALIDATE_ADDRESS_COMPRESSED });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_MESSAGE_VALIDATE_INDEX_VALID_SIGNATURE "\n");
}

BOOST_AUTO_TEST_CASE(message_validate__invoke__uncompressed__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(message_validate);
    command.set_message_argument({ "Nakomoto" });
    command.set_signature_argument({ MESSAGE_VALIDATE_SIGNATURE_UNCOMPRESSED });
    command.set_payment_address_argument({ MESSAGE_VALIDATE_ADDRESS_UNCOMPRESSED });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_MESSAGE_VALIDATE_INDEX_VALID_SIGNATURE "\n");
}

BOOST_AUTO_TEST_CASE(message_validate__invoke__bogus__invalid_output)
{
    BX_DECLARE_CLIENT_COMMAND(message_validate);
    command.set_message_argument({ "Satoshi" });
    command.set_signature_argument({ MESSAGE_VALIDATE_SIGNATURE_COMPRESSED });
    command.set_payment_address_argument({ MESSAGE_VALIDATE_ADDRESS_COMPRESSED });
    BX_REQUIRE_INVALID(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_MESSAGE_VALIDATE_INDEX_INVALID_SIGNATURE "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
