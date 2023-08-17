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
BOOST_AUTO_TEST_SUITE(electrum_new__invoke)

#ifdef WITH_ICU

// TODO: add all Electrum vectors.

// Various entropy sizes.

BOOST_AUTO_TEST_CASE(electrum_new__invoke__0_bytes__unsafe_entropy)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_NEW_UNSAFE_ENTROPY "\n");
}

BOOST_AUTO_TEST_CASE(electrum_new__invoke__1_byte__unsafe_entropy)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "42" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_NEW_UNSAFE_ENTROPY "\n");
}

BOOST_AUTO_TEST_CASE(electrum_new__invoke__2_bytes__unsafe_entropy)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "baad" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_NEW_UNSAFE_ENTROPY "\n");
}

BOOST_AUTO_TEST_CASE(electrum_new__invoke__4_bytes__unsafe_entropy)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "baadf00d" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_NEW_UNSAFE_ENTROPY "\n");
}
BOOST_AUTO_TEST_CASE(electrum_new__invoke__8_bytes__unsafe_entropy)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "baadf00dbaadf00d" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_NEW_UNSAFE_ENTROPY "\n");
}

BOOST_AUTO_TEST_CASE(electrum_new__invoke__16_bytes__unsafe_entropy)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ELECTRUM_NEW_UNSAFE_ENTROPY "\n");
}

BOOST_AUTO_TEST_CASE(electrum_new__invoke__17_bytes__okay_output)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d42" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("tree scan finger sweet theme problem horse useless fiber dad way print accident\n");
}

BOOST_AUTO_TEST_CASE(electrum_new__invoke__32_bytes__okay_output)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bundle result tail absorb fossil huge lesson pupil resemble scan finger sweet theme problem horse useless fiber dad way print bread lab step absent\n");
}

// Various languages.

BOOST_AUTO_TEST_CASE(electrum_new__invoke__standard__okay_output)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "05e669b4270f4e25bce6fc3736170d423c" });
    command.set_version_option({ "standard" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("giggle crush argue inflict wear defy combine evolve tiger spatial crumble fury\n");
}

BOOST_AUTO_TEST_CASE(electrum_new__invoke__standard_en__okay_output)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "05e669b4270f4e25bce6fc3736170d423c" });
    command.set_language_option({ "en" });
    command.set_version_option({ "standard" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("giggle crush argue inflict wear defy combine evolve tiger spatial crumble fury\n");
}


BOOST_AUTO_TEST_CASE(electrum_new__invoke__standard_es__okay_output)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "05e669b4270f4e25bce6fc3736170d423c" });
    command.set_language_option({ "es" });
    command.set_version_option({ "standard" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("gráfico codo ámbar insecto verbo cráter celoso entrar tarjeta sala coco frito\n");
}

BOOST_AUTO_TEST_CASE(electrum_new__invoke__standard_ja__okay_output)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "05e669b4270f4e25bce6fc3736170d423c" });
    command.set_language_option({ "ja" });
    command.set_version_option({ "standard" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ぴんち きぬごし いちど せあぶら りそう くうかん がんか ごかい まもる ひろゆき きなが さむけ\n");
}

BOOST_AUTO_TEST_CASE(electrum_new__invoke__standard_zh_Hans__okay_output)
{
    BX_DECLARE_COMMAND(electrum_new);
    command.set_entropy_argument({ "05e669b4270f4e25bce6fc3736170d423c" });
    command.set_language_option({ "zh_Hans" });
    command.set_version_option({ "standard" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("久 团 制 抓 霞 按 记 觉 纬 羊 劳 室\n");
}

// TODO: Various versions.

#endif

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
