/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
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

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__standard__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_passphrase_option("TREZOR");
    command.set_words_argument(
    {
        "legal", "winner", "thank", "year", "wave", "sausage", "worth", "useful", "legal", "winner", "thank", "yellow"
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2e8905819b8723fe2c1d161860e5ee1830318dbf49a83bd451cfb8440c28bd6fa457fe1296106559a3c80937a1c1069be3a3a5bd381ee6260e8d9739fce1f607\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__non_ascii_passphrase__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_passphrase_option("博 肉 地 危 惜 多 陪 荒 因 患 伊 基");
    command.set_words_argument(
    {
        "legal", "winner", "thank", "year", "wave", "sausage", "worth", "useful", "legal", "winner", "thank", "yellow"
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("3e52585ea1275472a82fa0dcd84121e742140f64a302eca7c390832ba428c707a7ebf449267ae592c51f1740259226e31520de39fd8f33e08788fd21221c6f4e\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__non_ascii_passphrase_and_words__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_passphrase_option("博 肉 地 危 惜 多 陪 荒 因 患 伊 基");
    command.set_words_argument(
    {
        "previo", "humilde", "actuar", "jarabe", "tabique", "ahorro", "tope", "pulpo", "anís", "señal", "lavar", "bahía"
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("e72505021b97e15171fe09e996898888579c4196c445d7629762c5b09586e3fb3d68380120b8d8a6ed6f9a73306dab7bf54127f3a610ede2a2d5b4e59916ac73\n");
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
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("e72505021b97e15171fe09e996898888579c4196c445d7629762c5b09586e3fb3d68380120b8d8a6ed6f9a73306dab7bf54127f3a610ede2a2d5b4e59916ac73\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_to_seed__invoke__non_ascii_passphrase_and_words_any__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_to_seed);
    command.set_language_option({ "any" });
    command.set_passphrase_option("博 肉 地 危 惜 多 陪 荒 因 患 伊 基");
    command.set_words_argument(
    {
        "previo", "humilde", "actuar", "jarabe", "tabique", "ahorro", "tope", "pulpo", "anís", "señal", "lavar", "bahía"
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("e72505021b97e15171fe09e996898888579c4196c445d7629762c5b09586e3fb3d68380120b8d8a6ed6f9a73306dab7bf54127f3a610ede2a2d5b4e59916ac73\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
