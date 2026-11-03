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
BC_AUTO_TEST_SUITE(electrum_new__invoke)

BC_AUTO_TEST_CASE(electrum_new__invoke__12_word_entropy__okay_output)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "61e6a02e39bf86734b7a71e1fa10d32f30" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("giggle crush argue inflict wear defy combine evolve tiger spatial crumble fury\n");
}

BC_AUTO_TEST_CASE(electrum_new__invoke__english_standard__okay_output)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "61e6a02e39bf86734b7a71e1fa10d32f30" });
    command.set_language_option({ "en" });
    command.set_prefix_option({ "standard" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("giggle crush argue inflict wear defy combine evolve tiger spatial crumble fury\n");
}

BC_AUTO_TEST_CASE(electrum_new__invoke__spanish_standard__okay_output)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "6606a02e39bf86734b7a71e1fa10d32f30" });
    command.set_language_option({ "es" });
    command.set_prefix_option({ "standard" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("gráfico codo ámbar insecto verbo cráter celoso entrar tarjeta sala coco frito\n");
}

BC_AUTO_TEST_CASE(electrum_new__invoke__24_word_entropy__okay_output)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "3fea8be336081d7aad3cba0c1ff86e8a6ad0f8ce50a604a58d003cf042b1a0e805" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("divide february web hire limb run reject nuclear army zone brick below public ladder deer below again cluster divorce ketchup aerobic flee lonely absent\n");
}

BC_AUTO_TEST_CASE(electrum_new__invoke__ground_entropy__okay_standard_prefix)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "05e669b4270f4e25bce6fc3736170d423c" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    const auto sentence = output.str().substr(0, output.str().size() - 1);
    BC_REQUIRE(wallet::electrum::is_prefix(sentence, wallet::electrum::seed_prefix::standard));
}

BC_AUTO_TEST_CASE(electrum_new__invoke__16_byte_entropy__failure_error)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_NEW_INVALID_ENTROPY_SIZE "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
