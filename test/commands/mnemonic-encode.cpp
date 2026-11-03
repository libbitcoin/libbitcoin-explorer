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
BC_AUTO_TEST_SUITE(mnemonic_encode__invoke)

BC_AUTO_TEST_CASE(mnemonic_encode__invoke__128_bit_entropy__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_encode);
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("rival hurdle address inspire tenant almost turkey safe asset step lab boy\n");
}

BC_AUTO_TEST_CASE(mnemonic_encode__invoke__trezor_vector__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_encode);
    command.set_entropy_argument({ "7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("legal winner thank year wave sausage worth useful legal winner thank yellow\n");
}

BC_AUTO_TEST_CASE(mnemonic_encode__invoke__english__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_encode);
    command.set_language_option({ "en" });
    command.set_entropy_argument({ "7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("legal winner thank year wave sausage worth useful legal winner thank yellow\n");
}

BC_AUTO_TEST_CASE(mnemonic_encode__invoke__any_language__okay_english_output)
{
    BX_DECLARE_COMMAND(mnemonic_encode);
    command.set_language_option({ "any" });
    command.set_entropy_argument({ "7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("legal winner thank year wave sausage worth useful legal winner thank yellow\n");
}

BC_AUTO_TEST_CASE(mnemonic_encode__invoke__64_bit_entropy__failure_error)
{
    BX_DECLARE_COMMAND(mnemonic_encode);
    command.set_entropy_argument({ "baadf00dbaadf00d" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_ENCODE_INVALID_ENTROPY_SIZE "\n");
}

BC_AUTO_TEST_CASE(mnemonic_encode__invoke__136_bit_entropy__failure_error)
{
    BX_DECLARE_COMMAND(mnemonic_encode);
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00dff" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_ENCODE_INVALID_ENTROPY_SIZE "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
