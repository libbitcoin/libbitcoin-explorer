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
BC_AUTO_TEST_SUITE(electrum_decode__invoke)

BC_AUTO_TEST_CASE(electrum_decode__invoke__12_words__okay_output)
{
    BX_DECLARE_COMMAND(electrum_decode);
    command.set_words_argument({ "giggle", "crush", "argue", "inflict", "wear", "defy", "combine", "evolve", "tiger", "spatial", "crumble", "fury" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("61e6a02e39bf86734b7a71e1fa10d32f30\n");
}

BC_AUTO_TEST_CASE(electrum_decode__invoke__english__okay_output)
{
    BX_DECLARE_COMMAND(electrum_decode);
    command.set_language_option({ "en" });
    command.set_words_argument({ "giggle", "crush", "argue", "inflict", "wear", "defy", "combine", "evolve", "tiger", "spatial", "crumble", "fury" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("61e6a02e39bf86734b7a71e1fa10d32f30\n");
}

BC_AUTO_TEST_CASE(electrum_decode__invoke__24_words__okay_output)
{
    BX_DECLARE_COMMAND(electrum_decode);
    command.set_words_argument({ "divide", "february", "web", "hire", "limb", "run", "reject", "nuclear", "army", "zone", "brick", "below", "public", "ladder", "deer", "below", "again", "cluster", "divorce", "ketchup", "aerobic", "flee", "lonely", "absent" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("3fea8be336081d7aad3cba0c1ff86e8a6ad0f8ce50a604a58d003cf042b1a0e805\n");
}

BC_AUTO_TEST_CASE(electrum_decode__invoke__3_words__failure_error)
{
    BX_DECLARE_COMMAND(electrum_decode);
    command.set_words_argument({ "foo", "bar", "baz" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_DECODE_INVALID_WORD_COUNT "\n");
}

BC_AUTO_TEST_CASE(electrum_decode__invoke__12_non_dictionary_words__failure_error)
{
    BX_DECLARE_COMMAND(electrum_decode);
    command.set_words_argument({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_DECODE_INVALID_WORDS "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
