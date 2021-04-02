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
BOOST_AUTO_TEST_SUITE(mnemonic_new__invoke)

// TODO: add all Trezor vectors.

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__trezor__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_entropy_argument({ "7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("legal winner thank year wave sausage worth useful legal winner thank yellow\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__trezor_en__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_language_option({ "en" });
    command.set_entropy_argument({ "7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("legal winner thank year wave sausage worth useful legal winner thank yellow\n");
}

// Various entropy sizes.

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__0_bytes__unsafe_entropy)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_entropy_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_NEW_UNSAFE_ENTROPY "\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__1_byte__unsafe_entropy)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_entropy_argument({ "42" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_NEW_UNSAFE_ENTROPY "\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__2_bytes__unsafe_entropy)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_entropy_argument({ "baad" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_NEW_UNSAFE_ENTROPY "\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__4_bytes__unsafe_entropy)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_entropy_argument({ "baadf00d" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_NEW_UNSAFE_ENTROPY "\n");
}
BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__8_bytes__unsafe_entropy)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_entropy_argument({ "baadf00dbaadf00d" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_NEW_UNSAFE_ENTROPY "\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__16_bytes__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("rival hurdle address inspire tenant almost turkey safe asset step lab boy\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__17_bytes__failure_error)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d42" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_MNEMONIC_NEW_INVALID_ENTROPY "\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__32_bytes__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("rival hurdle address inspire tenant almost turkey safe asset step lab bread print way dad fiber useless horse problem theme sweet finger scan reject\n");
}

// Various languages.

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__16_bytes_en__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_language_option({ "en" });
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("rival hurdle address inspire tenant almost turkey safe asset step lab boy\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__16_bytes_es__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_language_option({ "es" });
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("previo humilde actuar jarabe tabique ahorro tope pulpo anís señal lavar bahía\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__16_bytes_fr__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_language_option({ "fr" });
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("placard garantir acerbe gratuit soluble affaire théorie ponctuel anguleux salon horrible bateau\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__16_bytes_it__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_language_option({ "it" });
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("rizoma lastra affabile lucidato sultano algebra tramonto rupe annuncio sonda mega bavosa\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__16_bytes_cs__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_language_option({ "cs" });
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("semeno mudrc babka nasekat uvolnit bazuka vydra skanzen broskev trefit nuget datel\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__16_bytes_pt__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_language_option({ "pt" });
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("pesquisa gabinete acetona glorioso sirene adorar tesoura plaqueta alucinar roupa hipismo auditor\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__16_bytes_ja__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_language_option({ "ja" });
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ねんかん すずしい あひる せたけ ほとんど あんまり めいあん のべる いなか ふとる ぜんりゃく えいせい\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__16_bytes_ko__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_language_option({ "ko" });
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("전체 손실 갈비 숫자 큰길 개별 프랑스 정보 계획 초등학생 식빵 귀국\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__16_bytes_zh_Hans__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_language_option({ "zh_Hans" });
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("博 肉 地 危 惜 多 陪 荒 因 患 伊 基\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_new__invoke__16_bytes_zh_Hant__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_new);
    command.set_language_option({ "zh_Hant" });
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("博 肉 地 危 惜 多 陪 荒 因 患 伊 基\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
