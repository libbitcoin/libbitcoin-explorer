/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(token_new__invoke)

BOOST_AUTO_TEST_CASE(token_new__invoke__empty_salt__failure_error)
{
    BX_DECLARE_COMMAND(token_new);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TOKEN_NEW_SHORT_SALT "\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__3_byte_salt__failure_error)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_salt_argument({ "baadf0" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TOKEN_NEW_SHORT_SALT "\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__4_byte_salt__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_salt_argument({ "baadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("passphrasecpXbDpHuo8F7yQVcg1eQKPuX7rzGwBtEH1YSZnKbyk75x3rugZu1ci4RyF4rEn\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__passphrase_8_byte_salt__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_salt_argument({ "baadf00dbaadf00d" });
    command.set_passphrase_argument("passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("passphraseqVHzjN9paya9Fpe22QRCzqLhBiobhtgHd1e7T4QP6kqTtNeKA5jaYBcD4U2V23\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__excess_lot_4_byte_salt__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_lot_option(1048575 + 1);
    command.set_salt_argument({ "baadf00d" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TOKEN_NEW_MAXIMUM_LOT "\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__lot_4_byte_salt__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_lot_option(1048575);
    command.set_salt_argument({ "baadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("passphrasecpXbDpHuo8FGWjkFCxTEYSaekfi45D88ad5DVReNLhCTbnETGLfYfcrV4vwx3Q\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__excess_sequence_4_byte_salt__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_sequence_option(4095 + 1);
    command.set_salt_argument({ "baadf00d" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TOKEN_NEW_MAXIMUM_SEQUENCE "\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__sequence_4_byte_salt__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_sequence_option(4095);
    command.set_salt_argument({ "baadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("passphrasecpXbDpHuo8FGWjkFCxTEYSaekfi45D88ad5DVReNLhCTbnETGLfYfcrV4vwx3Q\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__lot_sequence_passphrase_4_byte_salt__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_lot_option(1048575);
    command.set_sequence_option(4095);
    command.set_salt_argument({ "baadf00d" });
    command.set_passphrase_argument("passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("passphrasecpXbDpHuo8FGWnwMTnTFiHSDnqyARArE2YSFQzMHtCZvM2oWg2K3Ua2crKyc11\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
