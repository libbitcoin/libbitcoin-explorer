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
BC_AUTO_TEST_SUITE(slip39_split__invoke)

BC_AUTO_TEST_CASE(slip39_split__invoke__unextendable_single_share__okay_output)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece" });
    command.set_groups_option({ { "1/1" } });
    command.set_threshold_option(1);
    command.set_identifier_option(7945);
    command.set_exponent_option(0);
    command.set_unextendable_option(true);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("duckling enlarge academic academic agency result length solution fridge kidney coal piece deal husband erode duke ajar critical decision keyboard\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__unextendable_single_share_256_bits__okay_output)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "989baf9dcaad5b10ca33dfd8cc75e42477025dce88ae83e75a230086a0e00e92" });
    command.set_groups_option({ { "1/1" } });
    command.set_threshold_option(1);
    command.set_identifier_option(29172);
    command.set_exponent_option(0);
    command.set_unextendable_option(true);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("theory painting academic academic armed sweater year military elder discuss acne wildlife boring employer fused large satoshi bundle carbon diagnose anatomy hamster leaves tracks paces beyond phantom capital marvel lips brave detect luck\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__single_share__okay_output)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "1679b4516e0ee5954351d288a838f45e" });
    command.set_groups_option({ { "1/1" } });
    command.set_threshold_option(1);
    command.set_identifier_option(29019);
    command.set_exponent_option(3);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("testify swimming academic academic column loyalty smear include exotic bedroom exotic wrist lobe cover grief golden smart junior estimate learn\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__single_share_256_bits__okay_output)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "8340611602fe91af634a5f4608377b5235fa2d757c51d720c0c7656249a3035f" });
    command.set_groups_option({ { "1/1" } });
    command.set_threshold_option(1);
    command.set_identifier_option(14691);
    command.set_exponent_option(3);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("impulse calcium academic academic alcohol sugar lyrics pajamas column facility finance tension extend space birthday rainbow swimming purple syndrome facility trial warn duration snapshot shadow hormone rhyme public spine counter easy hawk album\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__15_byte_secret__failure_error)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2ce" });
    command.set_groups_option({ { "1/1" } });
    command.set_threshold_option(1);
    command.set_identifier_option(0);
    command.set_exponent_option(1);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_SPLIT_INVALID_SECRET "\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__17_byte_secret__failure_error)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece00" });
    command.set_groups_option({ { "1/1" } });
    command.set_threshold_option(1);
    command.set_identifier_option(0);
    command.set_exponent_option(1);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_SPLIT_INVALID_SECRET "\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__one_of_two__failure_error)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece" });
    command.set_groups_option({ { "1/2" } });
    command.set_threshold_option(1);
    command.set_identifier_option(0);
    command.set_exponent_option(1);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_SPLIT_INVALID_GROUPS "\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__three_of_two__failure_error)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece" });
    command.set_groups_option({ { "3/2" } });
    command.set_threshold_option(1);
    command.set_identifier_option(0);
    command.set_exponent_option(1);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_SPLIT_INVALID_GROUPS "\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__threshold_above_groups__failure_error)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece" });
    command.set_groups_option({ { "1/1" } });
    command.set_threshold_option(2);
    command.set_identifier_option(0);
    command.set_exponent_option(1);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_SPLIT_INVALID_GROUPS "\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__zero_threshold__failure_error)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece" });
    command.set_groups_option({ { "1/1" } });
    command.set_threshold_option(0);
    command.set_identifier_option(0);
    command.set_exponent_option(1);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_SPLIT_INVALID_GROUPS "\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__no_groups__failure_error)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece" });
    command.set_groups_option({});
    command.set_threshold_option(1);
    command.set_identifier_option(0);
    command.set_exponent_option(1);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_SPLIT_INVALID_GROUPS "\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__identifier_above_maximum__failure_error)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece" });
    command.set_groups_option({ { "1/1" } });
    command.set_threshold_option(1);
    command.set_identifier_option(32768);
    command.set_exponent_option(1);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_SPLIT_INVALID_IDENTIFIER "\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__exponent_above_maximum__failure_error)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece" });
    command.set_groups_option({ { "1/1" } });
    command.set_threshold_option(1);
    command.set_identifier_option(0);
    command.set_exponent_option(16);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_SPLIT_INVALID_EXPONENT "\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__non_ascii_passphrase__failure_error)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece" });
    command.set_groups_option({ { "1/1" } });
    command.set_threshold_option(1);
    command.set_identifier_option(0);
    command.set_exponent_option(1);
    command.set_passphrase_option("café");
    command.set_entropy_argument({ "" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_SPLIT_INVALID_PASSPHRASE "\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__single_share_with_entropy__failure_error)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece" });
    command.set_groups_option({ { "1/1" } });
    command.set_threshold_option(1);
    command.set_identifier_option(0);
    command.set_exponent_option(1);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "00" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_SPLIT_INVALID_ENTROPY_SIZE " 0\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__unextendable_two_of_two_groups__okay_output)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece" });
    command.set_groups_option({ { "2/3" }, { "3/5" } });
    command.set_threshold_option(2);
    command.set_identifier_option(1234);
    command.set_exponent_option(1);
    command.set_unextendable_option(true);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f30313233" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("analysis merit acrobat echo distance pecan process object dish grant smug filter lizard endorse scroll window ugly paper lips glimpse\nanalysis merit acrobat email drove vocal adjust plastic grumpy silent acrobat recall miracle mental hamster pregnant visual dive crunch belong\nanalysis merit acrobat entrance deal acquire numb withdraw lobe charity carbon merchant plunge smell order timber stilt antenna lend pancake\nanalysis merit beard eclipse alarm broken guilt puny alpha capital kind adequate envelope chubby method family maiden obesity gasoline intimate\nanalysis merit beard emerald counter decrease radar profile obesity goat taxi floral ajar ultimate genius findings vocal escape secret diet\nanalysis merit beard envelope anatomy chemical anatomy level hush deal square story guard agree lawsuit cards group auction example segment\nanalysis merit beard exact coding angel spine olympic undergo excuse escape length cricket silver maximum broken branch system true lunar\nanalysis merit beard eyebrow aviation stay peaceful observe symbolic earth gums agree skin spark shaped gross sister merchant single pulse\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__one_of_two_groups_256_bits__okay_output)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece0011223344556677889900aabbccddee" });
    command.set_groups_option({ { "2/3" }, { "1/1" } });
    command.set_threshold_option(1);
    command.set_identifier_option(2345);
    command.set_exponent_option(0);
    command.set_entropy_argument({ "000102030405060708090a0b0c0d0e0f101112131415161718191a1b" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("being evil academic echo airline salon belong daisy scout dance withdraw ancient email forget jewelry kidney verify carpet slice hazard gravity guitar dream makeup season username switch grin empty capture impact loud earth\nbeing evil academic email artwork dilemma genre race silent cinema response software enemy endless flame fiction station thumb twice lair yoga short grownup depend romantic genuine enjoy skunk mixed render teammate ancestor beard\nbeing evil academic entrance airport profile veteran carbon jerky viral kind remind valid glasses clock curious rescue promise legal either either prayer mailman wavy coding behavior vanish forward fortune away quantity kidney sniff\nbeing evil away easy amount glen arcade erode august exceed elephant simple fancy orbit clothes arcade liquid discuss critical curious health physics epidemic violence distance spill material sidewalk enemy chest recover phrase sympathy\n");
}

BC_AUTO_TEST_CASE(slip39_split__invoke__two_of_two_groups_short_entropy__failure_error)
{
    BX_DECLARE_COMMAND(slip39_split);
    command.set_secret_option({ "bb54aac4b89dc868ba37d9cc21b2cece" });
    command.set_groups_option({ { "2/3" }, { "3/5" } });
    command.set_threshold_option(2);
    command.set_identifier_option(1234);
    command.set_exponent_option(1);
    command.set_passphrase_option("TREZOR");
    command.set_entropy_argument({ "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f303132" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SLIP39_SPLIT_INVALID_ENTROPY_SIZE " 52\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
