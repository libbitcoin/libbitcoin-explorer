/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
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
#include <boost/test/unit_test.hpp>

#include <bitcoin/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace bc::explorer;
using namespace bc::explorer::commands;

BOOST_AUTO_TEST_SUITE(generated)
BOOST_AUTO_TEST_SUITE(generated__formerly)

BOOST_AUTO_TEST_CASE(generated__formerly__address_decode_was_decode_addr__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("decode-addr"), address_decode::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__address_embed_was_embed_addr__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("embed-addr"), address_embed::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__address_encode_was_encode_addr__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("encode-addr"), address_encode::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__address_validate_was_validaddr__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("validaddr"), address_validate::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__btc_to_satoshi_was_satoshi__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("satoshi"), btc_to_satoshi::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__ec_add_secrets_was_ec_add_modp__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("ec-add-modp"), ec_add_secrets::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__ec_multiply_secrets_was_ec_tweak_add__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("ec-tweak-add"), ec_multiply_secrets::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__ec_new_was_newkey__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("newkey"), ec_new::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__ec_to_address_was_addr__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("addr"), ec_to_address::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__ec_to_ek_was_brainwallet__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("brainwallet"), ec_to_ek::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__ec_to_public_was_pubkey__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("pubkey"), ec_to_public::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__fetch_height_was_fetch_last_height__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("fetch-last-height"), fetch_height::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__fetch_public_key_was_get_pubkey__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("get-pubkey"), fetch_public_key::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__fetch_tx_was_fetch_transaction__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("fetch-transaction"), fetch_tx::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__fetch_tx_index_was_fetch_transaction_index__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("fetch-transaction-index"), fetch_tx_index::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__fetch_utxo_was_get_utxo__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("get-utxo"), fetch_utxo::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__hd_new_was_hd_seed__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("hd-seed"), hd_new::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__input_set_was_set_input__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("set-input"), input_set::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__input_sign_was_sign_input__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("sign-input"), input_sign::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__input_validate_was_validsig__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("validsig"), input_validate::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__mnemonic_encode_was_mnemonic__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("mnemonic"), mnemonic_encode::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__ripemd160_was_ripemd_hash__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("ripemd-hash"), ripemd160::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__satoshi_to_btc_was_btc__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("btc"), satoshi_to_btc::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__script_decode_was_showscript__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("showscript"), script_decode::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__script_encode_was_rawscript__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("rawscript"), script_encode::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__script_to_address_was_scripthash__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("scripthash"), script_to_address::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__send_tx_was_sendtx_obelisk__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("sendtx-obelisk"), send_tx::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__send_tx_node_was_sendtx_node__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("sendtx-node"), send_tx_node::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__send_tx_p2p_was_sendtx_p2p__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("sendtx-p2p"), send_tx_p2p::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__stealth_decode_was_stealth_show_addr__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("stealth-show-addr"), stealth_decode::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__stealth_public_was_stealth_uncover__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("stealth-uncover"), stealth_public::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__stealth_secret_was_stealth_uncover_secret__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("stealth-uncover-secret"), stealth_secret::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__tx_sign_was_signtx__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("signtx"), tx_sign::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__validate_tx_was_validtx__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("validtx"), validate_tx::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__watch_address_was_monitor__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("monitor"), watch_address::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__watch_tx_was_watchtx__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("watchtx"), watch_tx::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__wrap_decode_was_unwrap__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("unwrap"), wrap_decode::symbol());
}

BOOST_AUTO_TEST_CASE(generated__formerly__wrap_encode_was_wrap__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("wrap"), wrap_encode::symbol());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
