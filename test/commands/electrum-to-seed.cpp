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
BOOST_AUTO_TEST_SUITE(electrum_to_seed__invoke)

BOOST_AUTO_TEST_CASE(electrum_to_seed__invoke__okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_seed);
    command.set_words_argument({ "foo", "bar", "baz" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("c4033901dd61ba26cfd0a1cf1ceb4b347606635aa3cb951eb6e819d58beedc04dd400a2e600d783c83c75879d6538abeecc7bb1b292b2a4d775d348d5d686427\n");
}

BOOST_AUTO_TEST_CASE(electrum_to_seed__invoke__dictionary_prefix_okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_seed);
    command.set_language_option({ "en" });
    command.set_prefix_option({ "standard" });
    command.set_words_argument({ "foobar" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("741b72fd15effece6bfe5a26a52184f66811bd2be363190e07a42cca442b1a5bb22b3ad0eb338197287e6d314866c7fba863ac65d3f156087a5052ebc7157fce\n");
}

BOOST_AUTO_TEST_CASE(electrum_to_seed__invoke__okay_output2)
{
    BX_DECLARE_COMMAND(electrum_to_seed);
    command.set_language_option({ "en" });
    command.set_prefix_option({ "standard" });
    command.set_words_argument({ "giggle", "crush", "argue", "inflict", "wear", "defy", "combine", "evolve", "tiger", "spatial", "crumble", "fury" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("eb095e70f0eb8d24f2cef276c75b136c2ff41eb72a9291eb22ba45d11fbb875a965bd6ae09873543eea98bf3ae05067203cd56388e0978aebc3a511932704d80\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
