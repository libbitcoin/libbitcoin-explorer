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
BC_AUTO_TEST_SUITE(mnemonic_decode__invoke)

BC_AUTO_TEST_CASE(mnemonic_decode__invoke__12_words__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_decode);
    command.set_words_argument({ "rival", "hurdle", "address", "inspire", "tenant", "almost", "turkey", "safe", "asset", "step", "lab", "boy" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("baadf00dbaadf00dbaadf00dbaadf00d\n");
}

BC_AUTO_TEST_CASE(mnemonic_decode__invoke__trezor_vector__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_decode);
    command.set_words_argument({ "legal", "winner", "thank", "year", "wave", "sausage", "worth", "useful", "legal", "winner", "thank", "yellow" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f\n");
}

BC_AUTO_TEST_CASE(mnemonic_decode__invoke__english__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_decode);
    command.set_language_option({ "en" });
    command.set_words_argument({ "legal", "winner", "thank", "year", "wave", "sausage", "worth", "useful", "legal", "winner", "thank", "yellow" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f\n");
}

BC_AUTO_TEST_CASE(mnemonic_decode__invoke__13_words__failure_error)
{
    BX_DECLARE_COMMAND(mnemonic_decode);
    command.set_words_argument({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_DECODE_INVALID_WORD_COUNT "\n");
}

BC_AUTO_TEST_CASE(mnemonic_decode__invoke__24_non_dictionary_words__failure_error)
{
    BX_DECLARE_COMMAND(mnemonic_decode);
    command.set_words_argument({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_DECODE_INVALID_WORDS "\n");
}

BC_AUTO_TEST_CASE(mnemonic_decode__invoke__spanish_words_as_english__failure_error)
{
    BX_DECLARE_COMMAND(mnemonic_decode);
    command.set_language_option({ "en" });
    command.set_words_argument({ "almíbar", "tibio", "superar", "vencer", "hacha", "peatón", "príncipe", "matar", "consejo", "polen", "vehículo", "odisea" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_DECODE_INVALID_WORDS "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
