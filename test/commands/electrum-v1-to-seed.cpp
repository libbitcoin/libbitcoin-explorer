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
BC_AUTO_TEST_SUITE(electrum_v1_to_seed__invoke)

BC_AUTO_TEST_CASE(electrum_v1_to_seed__invoke__12_words__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_to_seed);
    command.set_words_argument({ "powerful", "random", "nobody", "notice", "nothing", "important", "anyway", "look", "away", "hidden", "message", "over" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("21b880fda2fd30081834683a7049ac9e3941a42adbc3a4616c9a9275aa960c0d\n");
}

BC_AUTO_TEST_CASE(electrum_v1_to_seed__invoke__portuguese__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_to_seed);
    command.set_language_option({ "pt" });
    command.set_words_argument({ "gear", "ansioso", "medusa", "bicuspide", "lauto", "ciatico", "jesus", "doping", "iceberg", "empuxo", "harpista", "feixe" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0c0fec78e9290ea97d893e7aa5196016c5a54d40087c93b09fef4e2242311c21\n");
}

BC_AUTO_TEST_CASE(electrum_v1_to_seed__invoke__24_words__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_to_seed);
    command.set_words_argument({ "fail", "husband", "howl", "fail", "husband", "howl", "fail", "husband", "howl", "fail", "husband", "howl", "fail", "husband", "howl", "fail", "husband", "howl", "fail", "husband", "howl", "fail", "husband", "howl" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("7c15e23142b67b412207789c8873153b7cebaae523b621845234cfa248891971\n");
}

BC_AUTO_TEST_CASE(electrum_v1_to_seed__invoke__overflow__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_to_seed);
    command.set_words_argument({ "hurry", "idiot", "prefer", "sunset", "mention", "mist", "jaw", "inhale", "impossible", "kingdom", "rare", "squeeze" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2c92470385815ff25e412f923a59f22d29a5d1f64f8542541328e099a6164d37\n");
}

BC_AUTO_TEST_CASE(electrum_v1_to_seed__invoke__double_overflow__okay_output)
{
    BX_DECLARE_COMMAND(electrum_v1_to_seed);
    command.set_words_argument({ "alone", "body", "father", "children", "lead", "goodbye", "phone", "twist", "exist", "grass", "kick", "join" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ae6c43a691f12da4594c7b1838decda56a811d8d0236132d9c7169648ce743be\n");
}

BC_AUTO_TEST_CASE(electrum_v1_to_seed__invoke__wrong_language__failure_error)
{
    BX_DECLARE_COMMAND(electrum_v1_to_seed);
    command.set_language_option({ "pt" });
    command.set_words_argument({ "powerful", "random", "nobody", "notice", "nothing", "important", "anyway", "look", "away", "hidden", "message", "over" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_V1_TO_SEED_INVALID_WORDS "\n");
}

BC_AUTO_TEST_CASE(electrum_v1_to_seed__invoke__3_words__failure_error)
{
    BX_DECLARE_COMMAND(electrum_v1_to_seed);
    command.set_words_argument({ "foo", "bar", "baz" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_V1_TO_SEED_INVALID_WORD_COUNT "\n");
}

BC_AUTO_TEST_CASE(electrum_v1_to_seed__invoke__12_non_dictionary_words__failure_error)
{
    BX_DECLARE_COMMAND(electrum_v1_to_seed);
    command.set_words_argument({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_V1_TO_SEED_INVALID_WORDS "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
