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

BC_AUTO_TEST_SUITE(offline)
BC_AUTO_TEST_SUITE(electrum_v1_encode__invoke)

BC_AUTO_TEST_CASE(electrum_v1_encode__invoke__16_bytes__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_encode);
    command.set_entropy_argument({ "acb740e454c3134901d7c8f16497cc1c" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("powerful random nobody notice nothing important anyway look away hidden message over\n");
}

BC_AUTO_TEST_CASE(electrum_v1_encode__invoke__english__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_encode);
    command.set_language_option({ "en" });
    command.set_entropy_argument({ "acb740e454c3134901d7c8f16497cc1c" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("powerful random nobody notice nothing important anyway look away hidden message over\n");
}

BC_AUTO_TEST_CASE(electrum_v1_encode__invoke__portuguese__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_encode);
    command.set_language_option({ "pt" });
    command.set_entropy_argument({ "85bd8950a3534bf1367b98dbeafc4022" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("gear ansioso medusa bicuspide lauto ciatico jesus doping iceberg empuxo harpista feixe\n");
}

BC_AUTO_TEST_CASE(electrum_v1_encode__invoke__32_bytes__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_encode);
    command.set_entropy_argument({ "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("fail husband howl fail husband howl fail husband howl fail husband howl fail husband howl fail husband howl fail husband howl fail husband howl\n");
}

BC_AUTO_TEST_CASE(electrum_v1_encode__invoke__overflow_entropy__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_encode);
    command.set_entropy_argument({ "025d2f2d00503691003ca78900ca155c" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("hurry idiot prefer sunset mention mist ship baby bright kingdom rare squeeze\n");
}

BC_AUTO_TEST_CASE(electrum_v1_encode__invoke__17_bytes__failure_error)
{
    BX_DECLARE_COMMAND(electrum_v1_encode);
    command.set_entropy_argument({ "0000000000000000000000000000000000" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_V1_ENCODE_INVALID_ENTROPY_SIZE "\n");
}

BC_AUTO_TEST_CASE(electrum_v1_encode__invoke__spanish__failure_error)
{
    BX_DECLARE_COMMAND(electrum_v1_encode);
    command.set_language_option({ "es" });
    command.set_entropy_argument({ "00000000000000000000000000000000" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_V1_ENCODE_INVALID_LANGUAGE "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
