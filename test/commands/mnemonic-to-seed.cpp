/**
 * Copyright (c) 2011-2018 libbitcoin developers (see AUTHORS)
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

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__13_words__failure_error)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_words_argument({ "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_MNEMONIC_TO_SEED_LENGTH_INVALID_SENTENCE "\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__24_invalid_words_en__failure_error)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_language_option({ "en" });
    command.set_words_argument(
    {
        "1", "2", "3", "4", "5", "6", "7", "8",
        "1", "2", "3", "4", "5", "6", "7", "8",
        "1", "2", "3", "4", "5", "6", "7", "8"
    });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_MNEMONIC_TO_SEED_INVALID_IN_LANGUAGE "\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__24_invalid_words__ok_warning)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_words_argument(
    {
        "1", "2", "3", "4", "5", "6", "7", "8",
        "1", "2", "3", "4", "5", "6", "7", "8",
        "1", "2", "3", "4", "5", "6", "7", "8"
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE_EQUAL(error.str(), BX_EC_MNEMONIC_TO_SEED_INVALID_IN_LANGUAGES "\n");
    BOOST_REQUIRE_EQUAL(output.str(), "4dcb7967130e59838c8aa12a61ce0fcbfd584d03885ce74f1f6775b3c881a2eeb34dca584e7ab2074cc6f0689fd1f1fb2545e35b979f1fe0aad0bbe31e0a011b\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__empty_passphrase__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_language_option({ "en" });
    command.set_words_argument(
    {
        "rival", "hurdle", "address", "inspire", "tenant", "alone"
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("33498afc5ef71e87afd7cad1e50a9d9adb9e30d3ca4b1da5dc370d266aa7796cbc1854eebce5ab3fd3b02b6625e2a82868dbb693e988e47d74106f04c76a6263\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__standard__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_passphrase_option("TREZOR");
    command.set_words_argument(
    {
        "legal", "winner", "thank", "year", "wave", "sausage", "worth", "useful", "legal", "winner", "thank", "yellow"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2e8905819b8723fe2c1d161860e5ee1830318dbf49a83bd451cfb8440c28bd6fa457fe1296106559a3c80937a1c1069be3a3a5bd381ee6260e8d9739fce1f607\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_MNEMONIC_TO_SEED_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__non_ascii_passphrase__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_passphrase_option("博 肉 地 危 惜 多 陪 荒 因 患 伊 基");
    command.set_words_argument(
    {
        "legal", "winner", "thank", "year", "wave", "sausage", "worth", "useful", "legal", "winner", "thank", "yellow"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("3e52585ea1275472a82fa0dcd84121e742140f64a302eca7c390832ba428c707a7ebf449267ae592c51f1740259226e31520de39fd8f33e08788fd21221c6f4e\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_MNEMONIC_TO_SEED_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__non_ascii_passphrase_and_words__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_passphrase_option("博 肉 地 危 惜 多 陪 荒 因 患 伊 基");
    command.set_words_argument(
    {
        "previo", "humilde", "actuar", "jarabe", "tabique", "ahorro", "tope", "pulpo", "anís", "señal", "lavar", "bahía"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("e72505021b97e15171fe09e996898888579c4196c445d7629762c5b09586e3fb3d68380120b8d8a6ed6f9a73306dab7bf54127f3a610ede2a2d5b4e59916ac73\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_MNEMONIC_TO_SEED_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__non_ascii_passphrase_and_words_any_spanish__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_language_option({ "any" });
    command.set_passphrase_option("博 肉 地 危 惜 多 陪 荒 因 患 伊 基");
    command.set_words_argument(
    {
        "previo", "humilde", "actuar", "jarabe", "tabique", "ahorro", "tope", "pulpo", "anís", "señal", "lavar", "bahía"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("e72505021b97e15171fe09e996898888579c4196c445d7629762c5b09586e3fb3d68380120b8d8a6ed6f9a73306dab7bf54127f3a610ede2a2d5b4e59916ac73\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_MNEMONIC_TO_SEED_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__non_ascii_passphrase_and_words_es__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_language_option({ "es" });
    command.set_passphrase_option("博 肉 地 危 惜 多 陪 荒 因 患 伊 基");
    command.set_words_argument(
    {
        "previo", "humilde", "actuar", "jarabe", "tabique", "ahorro", "tope", "pulpo", "anís", "señal", "lavar", "bahía"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("e72505021b97e15171fe09e996898888579c4196c445d7629762c5b09586e3fb3d68380120b8d8a6ed6f9a73306dab7bf54127f3a610ede2a2d5b4e59916ac73\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_MNEMONIC_TO_SEED_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__non_ascii_passphrase_and_words_any_french__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_language_option({ "any" });
    command.set_passphrase_option("博 肉 地 危 惜 多 陪 荒 因 患 伊 基");
    command.set_words_argument(
    {
        "placard", "garantir", "acerbe", "gratuit", "soluble", "affaire", "théorie", "ponctuel", "anguleux", "salon", "horrible", "bateau"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("a92538e2827914d13ead2b426aa45ebd0b16590318e04b6ef78780c8eb803269f08662dd74bc4982e7cbb71f15c71f310168457d570ad5fd89c98a6095bac560\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_MNEMONIC_TO_SEED_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__non_ascii_passphrase_and_words_fr__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_language_option({ "fr" });
    command.set_passphrase_option("博 肉 地 危 惜 多 陪 荒 因 患 伊 基");
    command.set_words_argument(
    {
        "placard", "garantir", "acerbe", "gratuit", "soluble", "affaire", "théorie", "ponctuel", "anguleux", "salon", "horrible", "bateau"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("a92538e2827914d13ead2b426aa45ebd0b16590318e04b6ef78780c8eb803269f08662dd74bc4982e7cbb71f15c71f310168457d570ad5fd89c98a6095bac560\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_MNEMONIC_TO_SEED_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__non_ascii_passphrase_and_words_any_italian__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_language_option({ "any" });
    command.set_passphrase_option("博 肉 地 危 惜 多 陪 荒 因 患 伊 基");
    command.set_words_argument(
    {
        "rizoma", "lastra", "affabile", "lucidato", "sultano", "algebra", "tramonto", "rupe", "annuncio", "sonda", "mega", "bavosa"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("b145e13882dc52b64a868ba35c3a95de5f468f2963d9feca9a8b345e3a60ef02af42347f99bc35a72d88bdabe8d63a4f5b61a63d6cd549461b5dd11027b66cf7\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_MNEMONIC_TO_SEED_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__non_ascii_passphrase_and_words_it__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_language_option({ "it" });
    command.set_passphrase_option("博 肉 地 危 惜 多 陪 荒 因 患 伊 基");
    command.set_words_argument(
    {
        "rizoma", "lastra", "affabile", "lucidato", "sultano", "algebra", "tramonto", "rupe", "annuncio", "sonda", "mega", "bavosa"
    });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("b145e13882dc52b64a868ba35c3a95de5f468f2963d9feca9a8b345e3a60ef02af42347f99bc35a72d88bdabe8d63a4f5b61a63d6cd549461b5dd11027b66cf7\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_MNEMONIC_TO_SEED_REQUIRES_ICU "\n");
#endif
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
