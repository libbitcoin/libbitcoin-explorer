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
BC_AUTO_TEST_SUITE(mnemonic_to_seed__invoke)

BC_AUTO_TEST_CASE(mnemonic_to_seed__invoke__empty_passphrase__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_language_option({ "en" });
    command.set_words_argument({ "rival", "hurdle", "address", "inspire", "tenant", "almost", "turkey", "safe", "asset", "step", "lab", "boy" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("020b67fd929e0eb9f963443138057ceec0d62601d69b4b2327c00d74f0fd1862d164c53d49227d9dadedbbec305236bc2149d9a5267aa7c5aa004235c3c66c29\n");
}

BC_AUTO_TEST_CASE(mnemonic_to_seed__invoke__trezor_passphrase__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_passphrase_option("TREZOR");
    command.set_words_argument({ "legal", "winner", "thank", "year", "wave", "sausage", "worth", "useful", "legal", "winner", "thank", "yellow" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2e8905819b8723fe2c1d161860e5ee1830318dbf49a83bd451cfb8440c28bd6fa457fe1296106559a3c80937a1c1069be3a3a5bd381ee6260e8d9739fce1f607\n");
}

BC_AUTO_TEST_CASE(mnemonic_to_seed__invoke__non_ascii_passphrase__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_passphrase_option("博 肉 地 危 惜 多 陪 荒 因 患 伊 基");
    command.set_words_argument({ "legal", "winner", "thank", "year", "wave", "sausage", "worth", "useful", "legal", "winner", "thank", "yellow" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("3e52585ea1275472a82fa0dcd84121e742140f64a302eca7c390832ba428c707a7ebf449267ae592c51f1740259226e31520de39fd8f33e08788fd21221c6f4e\n");
}

BC_AUTO_TEST_CASE(mnemonic_to_seed__invoke__13_words__failure_error)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_words_argument({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_TO_SEED_INVALID_WORD_COUNT "\n");
}

BC_AUTO_TEST_CASE(mnemonic_to_seed__invoke__24_non_dictionary_words_english__failure_error)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_language_option({ "en" });
    command.set_words_argument({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_TO_SEED_INVALID_WORDS "\n");
}

BC_AUTO_TEST_CASE(mnemonic_to_seed__invoke__24_non_dictionary_words__failure_error)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_words_argument({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_TO_SEED_INVALID_WORDS "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
