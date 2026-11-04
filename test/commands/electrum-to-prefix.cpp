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
BC_AUTO_TEST_SUITE(electrum_to_prefix__invoke)

BC_AUTO_TEST_CASE(electrum_to_prefix__invoke__standard__okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_prefix);
    command.set_words_argument({ "giggle", "crush", "argue", "inflict", "wear", "defy", "combine", "evolve", "tiger", "spatial", "crumble", "fury" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("standard\n");
}

BC_AUTO_TEST_CASE(electrum_to_prefix__invoke__witness__okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_prefix);
    command.set_words_argument({ "wild", "father", "tree", "among", "universe", "such", "mobile", "favorite", "target", "dynamic", "credit", "identify" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("witness\n");
}

BC_AUTO_TEST_CASE(electrum_to_prefix__invoke__two_factor_authentication__okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_prefix);
    command.set_words_argument({ "orfano", "verbale", "vessillo", "sabato", "furbo", "dito", "gallina", "asino", "delegare", "chiedere", "alettone", "ulisse" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2fa\n");
}

BC_AUTO_TEST_CASE(electrum_to_prefix__invoke__two_factor_authentication_witness__okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_prefix);
    command.set_words_argument({ "appetito", "brindare", "sussurro", "leva", "femmina", "connesso", "nucleo", "freccetta", "leggero", "tariffa", "virologo", "roccia" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2faw\n");
}

BC_AUTO_TEST_CASE(electrum_to_prefix__invoke__electrum_v1_words__okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_prefix);
    command.set_words_argument({ "hurry", "idiot", "prefer", "sunset", "mention", "mist", "jaw", "inhale", "impossible", "kingdom", "rare", "squeeze" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("none\n");
}

BC_AUTO_TEST_CASE(electrum_to_prefix__invoke__bip39__okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_prefix);
    command.set_words_argument({ "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "abandon", "about" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bip39\n");
}

BC_AUTO_TEST_CASE(electrum_to_prefix__invoke__unprefixed__okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_prefix);
    command.set_words_argument({ "giggle", "crush", "argue", "inflict", "wear", "defy", "combine", "evolve", "tiger", "spatial", "crumble", "crush" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("none\n");
}

BC_AUTO_TEST_CASE(electrum_to_prefix__invoke__non_dictionary_words__okay_output)
{
    BX_DECLARE_COMMAND(electrum_to_prefix);
    command.set_words_argument({ "foo", "bar", "baz" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("none\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
