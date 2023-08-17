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
BOOST_AUTO_TEST_SUITE(token_new__invoke)

#ifdef WITH_ICU

BOOST_AUTO_TEST_CASE(token_new__invoke__empty_salt__failure_error)
{
    BX_DECLARE_COMMAND(token_new);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TOKEN_NEW_SHORT_SALT "\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__max_lot_4_byte_salt__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_lot_option(1048575);
    command.set_salt_argument({ "baadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("passphrasecpXbDpHuo8FGWjkFCxTEYSaekfi45D88ad5DVReNLhCTbnETGLfYfcrV4vwx3Q\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__max_sequence_4_byte_salt__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_sequence_option(4095);
    command.set_salt_argument({ "baadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("passphrasecpXbDpHuo8FGWjkFCxTEYSaekfi45D88ad5DVReNLhCTbnETGLfYfcrV4vwx3Q\n");
}

// Wiki Examples

BOOST_AUTO_TEST_CASE(token_new__invoke__example_1_lot_sequence_defaults__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_salt_argument({ "baadf00d" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("passphrasecpXbDpHuo8F7yuZqR49koDA9uQojPijjjZaxsar7Woo9pfHJbeWF3VMU9EPBqJ\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__example_2_lot_sequence__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_lot_option(7);
    command.set_sequence_option(42);
    command.set_salt_argument({ "baadf00d" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("passphrasecpXbDpHuo8FGWy2zdpFXvmsu31YuLU5peBAqzJifHjeaHfePVW45ptrh3NqD3Z\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__example_3_invalid_salt__failure_error)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_salt_argument({ "baadf0" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TOKEN_NEW_SHORT_SALT "\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__example_4_invalid_lot__failure_error)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_lot_option(1048575 + 1);
    command.set_salt_argument({ "baadf00d" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TOKEN_NEW_MAXIMUM_LOT "\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__example_5_invalid_sequence__failure_error)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_sequence_option(4095 + 1);
    command.set_salt_argument({ "baadf00d" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TOKEN_NEW_MAXIMUM_SEQUENCE "\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__example_6_piped_input_lot_sequence__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_lot_option(7);
    command.set_sequence_option(42);
    command.set_salt_argument({ "f6af40a01b79c95f" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("passphraseeJe8PsbqqTpXKHHL5CupNg3hf396MFAHUeFf1k74zFs2pqxM9ARwjKLh4Px1sB\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__example_7_unused_salt_bits__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_lot_option(7);
    command.set_sequence_option(42);
    command.set_salt_argument({ "f6af40a01b79c95fef5e397eca05e27d7a3d1c35b01108db" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("passphraseeJe8PsbqqTpXKHHL5CupNg3hf396MFAHUeFf1k74zFs2pqxM9ARwjKLh4Px1sB\n");
}

BOOST_AUTO_TEST_CASE(token_new__invoke__example_8_piped_commands__okay)
{
    BX_DECLARE_COMMAND(token_new);
    command.set_salt_argument({ "f6af40a01b79c95fef5e397eca05e27d7a3d1c35b01108db" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("passphraseryQXuRZZQ3Jw5rAT7m6MzxkGSSRmysq3Ayj9vuEHEnbVPJSmRQ2xYFKDKjGYrq\n");
}

#else // WITH_ICU

BOOST_AUTO_TEST_CASE(token_new__invoke__not_icu__failure_error)
{
    BX_DECLARE_COMMAND(token_new);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TOKEN_NEW_REQUIRES_ICU "\n");
}

#endif // !WITH_ICU

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
