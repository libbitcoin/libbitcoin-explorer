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
BC_AUTO_TEST_SUITE(slip39_combine__invoke)

BC_AUTO_TEST_CASE(slip39_combine__invoke__single_share__okay_output)
{
    BX_DECLARE_COMMAND(slip39_combine);
    command.set_passphrase_option("TREZOR");
    command.set_shares_argument({ { "duckling enlarge academic academic agency result length solution fridge kidney coal piece deal husband erode duke ajar critical decision keyboard" } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bb54aac4b89dc868ba37d9cc21b2cece\n");
}

BC_AUTO_TEST_CASE(slip39_combine__invoke__two_of_three__okay_output)
{
    BX_DECLARE_COMMAND(slip39_combine);
    command.set_passphrase_option("TREZOR");
    command.set_shares_argument({ { "shadow pistol academic always adequate wildlife fancy gross oasis cylinder mustang wrist rescue view short owner flip making coding armed" }, { "shadow pistol academic acid actress prayer class unknown daughter sweater depict flip twice unkind craft early superior advocate guest smoking" } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("b43ceb7e57a0ea8766221624d01b0864\n");
}

BC_AUTO_TEST_CASE(slip39_combine__invoke__groups__okay_output)
{
    BX_DECLARE_COMMAND(slip39_combine);
    command.set_passphrase_option("TREZOR");
    command.set_shares_argument({ { "eraser senior decision roster beard treat identify grumpy salt index fake aviation theater cubic bike cause research dragon emphasis counter" }, { "eraser senior ceramic snake clay various huge numb argue hesitate auction category timber browser greatest hanger petition script leaf pickup" }, { "eraser senior ceramic shaft dynamic become junior wrist silver peasant force math alto coal amazing segment yelp velvet image paces" }, { "eraser senior ceramic round column hawk trust auction smug shame alive greatest sheriff living perfect corner chest sled fumes adequate" }, { "eraser senior decision smug corner ruin rescue cubic angel tackle skin skunk program roster trash rumor slush angel flea amazing" } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("7c3397a292a5941682d7a4ae2d898d11\n");
}

BC_AUTO_TEST_CASE(slip39_combine__invoke__single_share_256_bits__okay_output)
{
    BX_DECLARE_COMMAND(slip39_combine);
    command.set_passphrase_option("TREZOR");
    command.set_shares_argument({ { "theory painting academic academic armed sweater year military elder discuss acne wildlife boring employer fused large satoshi bundle carbon diagnose anatomy hamster leaves tracks paces beyond phantom capital marvel lips brave detect luck" } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("989baf9dcaad5b10ca33dfd8cc75e42477025dce88ae83e75a230086a0e00e92\n");
}

BC_AUTO_TEST_CASE(slip39_combine__invoke__two_of_three_256_bits__okay_output)
{
    BX_DECLARE_COMMAND(slip39_combine);
    command.set_passphrase_option("TREZOR");
    command.set_shares_argument({ { "humidity disease academic always aluminum jewelry energy woman receiver strategy amuse duckling lying evidence network walnut tactics forget hairy rebound impulse brother survive clothes stadium mailman rival ocean reward venture always armed unwrap" }, { "humidity disease academic agency actress jacket gross physics cylinder solution fake mortgage benefit public busy prepare sharp friar change work slow purchase ruler again tricycle involve viral wireless mixture anatomy desert cargo upgrade" } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("c938b319067687e990e05e0da0ecce1278f75ff58d9853f19dcaeed5de104aae\n");
}

BC_AUTO_TEST_CASE(slip39_combine__invoke__extendable_single_share__okay_output)
{
    BX_DECLARE_COMMAND(slip39_combine);
    command.set_passphrase_option("TREZOR");
    command.set_shares_argument({ { "testify swimming academic academic column loyalty smear include exotic bedroom exotic wrist lobe cover grief golden smart junior estimate learn" } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1679b4516e0ee5954351d288a838f45e\n");
}

BC_AUTO_TEST_CASE(slip39_combine__invoke__extendable_two_of_three__okay_output)
{
    BX_DECLARE_COMMAND(slip39_combine);
    command.set_passphrase_option("TREZOR");
    command.set_shares_argument({ { "enemy favorite academic acid cowboy phrase havoc level response walnut budget painting inside trash adjust froth kitchen learn tidy punish" }, { "enemy favorite academic always academic sniff script carpet romp kind promise scatter center unfair training emphasis evening belong fake enforce" } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("48b1a4b80b8c209ad42c33672bdaa428\n");
}

BC_AUTO_TEST_CASE(slip39_combine__invoke__no_passphrase__okay_output)
{
    BX_DECLARE_COMMAND(slip39_combine);
    command.set_shares_argument({ { "shadow pistol academic always adequate wildlife fancy gross oasis cylinder mustang wrist rescue view short owner flip making coding armed" }, { "shadow pistol academic acid actress prayer class unknown daughter sweater depict flip twice unkind craft early superior advocate guest smoking" } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("61cf4d6c0d8a07d8c2fd3cff22432664\n");
}

BC_AUTO_TEST_CASE(slip39_combine__invoke__insufficient__failure_error)
{
    BX_DECLARE_COMMAND(slip39_combine);
    command.set_passphrase_option("TREZOR");
    command.set_shares_argument({ { "shadow pistol academic always adequate wildlife fancy gross oasis cylinder mustang wrist rescue view short owner flip making coding armed" } });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_COMBINE_INVALID "\n");
}

BC_AUTO_TEST_CASE(slip39_combine__invoke__different_identifiers__failure_error)
{
    BX_DECLARE_COMMAND(slip39_combine);
    command.set_passphrase_option("TREZOR");
    command.set_shares_argument({ { "adequate smoking academic acid debut wine petition glen cluster slow rhyme slow simple epidemic rumor junk tracks treat olympic tolerate" }, { "adequate stay academic agency agency formal party ting frequent learn upstairs remember smear leaf damage anatomy ladle market hush corner" } });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_COMBINE_INVALID "\n");
}

BC_AUTO_TEST_CASE(slip39_combine__invoke__no_shares__failure_error)
{
    BX_DECLARE_COMMAND(slip39_combine);
    command.set_shares_argument({});
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_COMBINE_INVALID "\n");
}

BC_AUTO_TEST_CASE(slip39_combine__invoke__non_ascii_passphrase__failure_error)
{
    BX_DECLARE_COMMAND(slip39_combine);
    command.set_passphrase_option("café");
    command.set_shares_argument({ { "duckling enlarge academic academic agency result length solution fridge kidney coal piece deal husband erode duke ajar critical decision keyboard" } });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_COMBINE_INVALID "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
