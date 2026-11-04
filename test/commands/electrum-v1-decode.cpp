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
BC_AUTO_TEST_SUITE(electrum_v1_decode__invoke)

BC_AUTO_TEST_CASE(electrum_v1_decode__invoke__12_words__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_decode);
    command.set_words_argument({ "powerful", "random", "nobody", "notice", "nothing", "important", "anyway", "look", "away", "hidden", "message", "over" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("acb740e454c3134901d7c8f16497cc1c\n");
}

BC_AUTO_TEST_CASE(electrum_v1_decode__invoke__english__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_decode);
    command.set_language_option({ "en" });
    command.set_words_argument({ "powerful", "random", "nobody", "notice", "nothing", "important", "anyway", "look", "away", "hidden", "message", "over" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("acb740e454c3134901d7c8f16497cc1c\n");
}

BC_AUTO_TEST_CASE(electrum_v1_decode__invoke__portuguese__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_decode);
    command.set_language_option({ "pt" });
    command.set_words_argument({ "gear", "ansioso", "medusa", "bicuspide", "lauto", "ciatico", "jesus", "doping", "iceberg", "empuxo", "harpista", "feixe" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("85bd8950a3534bf1367b98dbeafc4022\n");
}

BC_AUTO_TEST_CASE(electrum_v1_decode__invoke__24_words__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_decode);
    command.set_words_argument({ "fail", "husband", "howl", "fail", "husband", "howl", "fail", "husband", "howl", "fail", "husband", "howl", "fail", "husband", "howl", "fail", "husband", "howl", "fail", "husband", "howl", "fail", "husband", "howl" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n");
}

BC_AUTO_TEST_CASE(electrum_v1_decode__invoke__trimmed_overflow_words__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_decode);
    command.set_words_argument({ "hurry", "idiot", "prefer", "sunset", "mention", "mist", "ship", "baby", "bright", "kingdom", "rare", "squeeze" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("025d2f2d00503691003ca78900ca155c\n");
}

BC_AUTO_TEST_CASE(electrum_v1_decode__invoke__overflow__failure_error)
{
    BX_DECLARE_COMMAND(electrum_v1_decode);
    command.set_words_argument({ "hurry", "idiot", "prefer", "sunset", "mention", "mist", "jaw", "inhale", "impossible", "kingdom", "rare", "squeeze" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_V1_DECODE_OVERFLOW "\n");
}

BC_AUTO_TEST_CASE(electrum_v1_decode__invoke__wrong_language__failure_error)
{
    BX_DECLARE_COMMAND(electrum_v1_decode);
    command.set_language_option({ "pt" });
    command.set_words_argument({ "powerful", "random", "nobody", "notice", "nothing", "important", "anyway", "look", "away", "hidden", "message", "over" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_V1_DECODE_INVALID_WORDS "\n");
}

BC_AUTO_TEST_CASE(electrum_v1_decode__invoke__3_words__failure_error)
{
    BX_DECLARE_COMMAND(electrum_v1_decode);
    command.set_words_argument({ "foo", "bar", "baz" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_V1_DECODE_INVALID_WORD_COUNT "\n");
}

BC_AUTO_TEST_CASE(electrum_v1_decode__invoke__15_words__failure_error)
{
    BX_DECLARE_COMMAND(electrum_v1_decode);
    command.set_words_argument({ "powerful", "random", "nobody", "notice", "nothing", "important", "anyway", "look", "away", "hidden", "message", "over", "like", "like", "like" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_V1_DECODE_INVALID_WORD_COUNT "\n");
}

BC_AUTO_TEST_CASE(electrum_v1_decode__invoke__12_non_dictionary_words__failure_error)
{
    BX_DECLARE_COMMAND(electrum_v1_decode);
    command.set_words_argument({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_V1_DECODE_INVALID_WORDS "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
