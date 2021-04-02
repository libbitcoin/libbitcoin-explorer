/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(mnemonic_to_seed__invoke)

// TODO: add all Trezor vectors.

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__trezor__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_passphrase_option("TREZOR");
    command.set_words_argument(
    {
        "legal", "winner", "thank", "year", "wave", "sausage",
        "worth", "useful", "legal", "winner", "thank", "yellow"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2e8905819b8723fe2c1d161860e5ee1830318dbf49a83bd451cfb8440c28bd6fa457fe1296106559a3c80937a1c1069be3a3a5bd381ee6260e8d9739fce1f607\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_TO_SEED_PASSPHRASE_REQUIRES_ICU "\n");
#endif
}

// Sentence length errors.

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__11_words__unsafe_sentence)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_words_argument(
    {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"
    });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_TO_SEED_UNSAFE_SENTENCE "\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__13_words__invalid_sentence)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_words_argument(
    {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"
    });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_TO_SEED_INVALID_SENTENCE "\n");
}

// Various language sentences.

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__24_invalid_en_words__invalid_languages)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_languages_option({ { "en" } });
    command.set_words_argument(
    {
        "1", "2", "3", "4", "5", "6", "7", "8",
        "1", "2", "3", "4", "5", "6", "7", "8",
        "1", "2", "3", "4", "5", "6", "7", "8"
    });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_TO_SEED_INVALID_LANGUAGES "\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__24_unverified_words__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_words_argument(
    {
        "1", "2", "3", "4", "5", "6", "7", "8",
        "1", "2", "3", "4", "5", "6", "7", "8",
        "1", "2", "3", "4", "5", "6", "7", "8"
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("4dcb7967130e59838c8aa12a61ce0fcbfd584d03885ce74f1f6775b3c881a2eeb34dca584e7ab2074cc6f0689fd1f1fb2545e35b979f1fe0aad0bbe31e0a011b\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__12_en_words_en__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_languages_option({ { "en" } });
    command.set_words_argument(
    {
        "legal", "winner", "thank", "year", "wave", "sausage",
        "worth", "useful", "legal", "winner", "thank", "yellow"
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("878386efb78845b3355bd15ea4d39ef97d179cb712b77d5c12b6be415fffeffe5f377ba02bf3f8544ab800b955e51fbff09828f682052a20faa6addbbddfb096\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__12_en_words_es_fr_it_cs_pt_ja_ko_zh_Hans_zh_Hant__invalid_languages)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_languages_option(
    {
        { "es" }, { "fr" }, { "it" }, { "cs" }, { "pt" }, { "ja" }, { "ko" }, { "zh_Hans" }, { "zh_Hant" }
    });
    command.set_words_argument(
    {
        "legal", "winner", "thank", "year", "wave", "sausage",
        "worth", "useful", "legal", "winner", "thank", "yellow"
    });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_TO_SEED_INVALID_LANGUAGES "\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__12_en_words_es_fr_it_cs_en_pt_ja_ko_zh_Hans_zh_Hant__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_languages_option(
    {
        { "es" }, { "fr" }, { "it" }, { "cs" }, { "en" }, { "pt" }, { "ja" }, { "ko" }, { "zh_Hans" }, { "zh_Hant" }
    });
    command.set_words_argument(
    {
        "legal", "winner", "thank", "year", "wave", "sausage",
        "worth", "useful", "legal", "winner", "thank", "yellow"
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("878386efb78845b3355bd15ea4d39ef97d179cb712b77d5c12b6be415fffeffe5f377ba02bf3f8544ab800b955e51fbff09828f682052a20faa6addbbddfb096\n");
}

// Various passphrases.

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__non_ascii_passphrase__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_passphrase_option("博 肉 地 危 惜 多 陪 荒 因 患 伊 基");
    command.set_words_argument(
    {
        "legal", "winner", "thank", "year", "wave", "sausage",
        "worth", "useful", "legal", "winner", "thank", "yellow"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("3e52585ea1275472a82fa0dcd84121e742140f64a302eca7c390832ba428c707a7ebf449267ae592c51f1740259226e31520de39fd8f33e08788fd21221c6f4e\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_TO_SEED_PASSPHRASE_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
