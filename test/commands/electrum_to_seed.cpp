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
BOOST_AUTO_TEST_SUITE(electrum_to_seed__invoke)

// TODO: add all Electrum vectors.

BOOST_AUTO_TEST_CASE(electrum_to_seed__invoke__electrum_unverified_words__okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_seed);
    command.set_passphrase_option({ "araña difícil solución término cárcel" });

    // These words are not all in any dictionary.
    command.set_words_argument({ "almíbar", "tibio", "superar", "vencer", "hacha", "peatón", "príncipe", "matar", "consejo", "polen", "vehículo", "odisea" });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("363dec0e575b887cfccebee4c84fca5a3a6bed9d0e099c061fa6b85020b031f8fe3636d9af187bf432d451273c625e20f24f651ada41aae2c4ea62d87e9fa44c\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_TO_SEED_REQUIRES_ICU "\n");
#endif
}

// Sentence length errors.

BOOST_AUTO_TEST_CASE(electrum_to_seed__invoke__11_words__unsafe_sentence)
{
    BX_DECLARE_COMMAND(electrum_to_seed);
    command.set_words_argument(
    {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"
    });
#ifdef WITH_ICU
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_TO_SEED_UNSAFE_SENTENCE "\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_TO_SEED_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_CASE(electrum_to_seed__invoke__12_words__okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_seed);
    command.set_words_argument(
    {
        "giggle", "crush", "argue", "inflict", "wear", "defy",
        "combine", "evolve", "tiger", "spatial", "crumble", "fury"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("eb095e70f0eb8d24f2cef276c75b136c2ff41eb72a9291eb22ba45d11fbb875a965bd6ae09873543eea98bf3ae05067203cd56388e0978aebc3a511932704d80\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_TO_SEED_REQUIRES_ICU "\n");
#endif
}

// Various language sentences.

BOOST_AUTO_TEST_CASE(electrum_to_seed__invoke__12_invalid_en_words__invalid_languages)
{
    BX_DECLARE_COMMAND(electrum_to_seed);
    command.set_languages_option({ { "en" } });
    command.set_words_argument(
    {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"
    });
#ifdef WITH_ICU
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_TO_SEED_INVALID_LANGUAGES "\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_TO_SEED_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_CASE(electrum_to_seed__invoke__12_words_en__okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_seed);
    command.set_languages_option({ { "en" } });
    command.set_words_argument(
    {
        "giggle", "crush", "argue", "inflict", "wear", "defy",
        "combine", "evolve", "tiger", "spatial", "crumble", "fury"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("eb095e70f0eb8d24f2cef276c75b136c2ff41eb72a9291eb22ba45d11fbb875a965bd6ae09873543eea98bf3ae05067203cd56388e0978aebc3a511932704d80\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_TO_SEED_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_CASE(electrum_to_seed__invoke__12_en_words_es_ja_en_zh_Hans__okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_seed);
    command.set_languages_option({ { "es" }, { "ja" }, { "en" }, { "zh_Hans" } });
    command.set_words_argument(
    {
        "giggle", "crush", "argue", "inflict", "wear", "defy",
        "combine", "evolve", "tiger", "spatial", "crumble", "fury"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("eb095e70f0eb8d24f2cef276c75b136c2ff41eb72a9291eb22ba45d11fbb875a965bd6ae09873543eea98bf3ae05067203cd56388e0978aebc3a511932704d80\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_TO_SEED_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_CASE(electrum_to_seed__invoke__12_en_words_es_ja_zh_Hans__invalid_languages)
{
    BX_DECLARE_COMMAND(electrum_to_seed);
    command.set_languages_option({ { "es" }, { "ja" }, { "zh_Hans" } });
    command.set_words_argument(
    {
        "giggle", "crush", "argue", "inflict", "wear", "defy",
        "combine", "evolve", "tiger", "spatial", "crumble", "fury"
    });
#ifdef WITH_ICU
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_TO_SEED_INVALID_LANGUAGES "\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_TO_SEED_REQUIRES_ICU "\n");
#endif
}

// TODO: Various versions (language validation).

// TODO: Various passphrases (decoding).

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
