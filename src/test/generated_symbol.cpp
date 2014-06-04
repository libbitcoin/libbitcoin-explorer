/*
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include <sx/sx.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace sx::extensions;

BOOST_AUTO_TEST_SUITE(generated_symbol)

BOOST_AUTO_TEST_CASE(find_addr_returns_expected_value)
{
    BOOST_REQUIRE(addr::symbol() == std::string("addr"));
}

BOOST_AUTO_TEST_CASE(find_balance_returns_expected_value)
{
    BOOST_REQUIRE(balance::symbol() == std::string("balance"));
}

BOOST_AUTO_TEST_CASE(find_base58_decode_returns_expected_value)
{
    BOOST_REQUIRE(base58_decode::symbol() == std::string("base58-decode"));
}

BOOST_AUTO_TEST_CASE(find_base58_encode_returns_expected_value)
{
    BOOST_REQUIRE(base58_encode::symbol() == std::string("base58-encode"));
}

BOOST_AUTO_TEST_CASE(find_base58check_decode_returns_expected_value)
{
    BOOST_REQUIRE(base58check_decode::symbol() == std::string("base58check-decode"));
}

BOOST_AUTO_TEST_CASE(find_base58check_encode_returns_expected_value)
{
    BOOST_REQUIRE(base58check_encode::symbol() == std::string("base58check-encode"));
}

BOOST_AUTO_TEST_CASE(find_bci_fetch_last_height_returns_expected_value)
{
    BOOST_REQUIRE(bci_fetch_last_height::symbol() == std::string("bci-fetch-last-height"));
}

BOOST_AUTO_TEST_CASE(find_bci_history_returns_expected_value)
{
    BOOST_REQUIRE(bci_history::symbol() == std::string("bci-history"));
}

BOOST_AUTO_TEST_CASE(find_blke_fetch_transaction_returns_expected_value)
{
    BOOST_REQUIRE(blke_fetch_transaction::symbol() == std::string("blke-fetch-transaction"));
}

BOOST_AUTO_TEST_CASE(find_brainwallet_returns_expected_value)
{
    BOOST_REQUIRE(brainwallet::symbol() == std::string("brainwallet"));
}

BOOST_AUTO_TEST_CASE(find_btc_returns_expected_value)
{
    BOOST_REQUIRE(btc::symbol() == std::string("btc"));
}

BOOST_AUTO_TEST_CASE(find_decode_addr_returns_expected_value)
{
    BOOST_REQUIRE(decode_addr::symbol() == std::string("decode-addr"));
}

BOOST_AUTO_TEST_CASE(find_ec_add_returns_expected_value)
{
    BOOST_REQUIRE(ec_add::symbol() == std::string("ec-add"));
}

BOOST_AUTO_TEST_CASE(find_ec_add_modp_returns_expected_value)
{
    BOOST_REQUIRE(ec_add_modp::symbol() == std::string("ec-add-modp"));
}

BOOST_AUTO_TEST_CASE(find_ec_multiply_returns_expected_value)
{
    BOOST_REQUIRE(ec_multiply::symbol() == std::string("ec-multiply"));
}

BOOST_AUTO_TEST_CASE(find_ec_tweak_add_returns_expected_value)
{
    BOOST_REQUIRE(ec_tweak_add::symbol() == std::string("ec-tweak-add"));
}

BOOST_AUTO_TEST_CASE(find_embed_addr_returns_expected_value)
{
    BOOST_REQUIRE(embed_addr::symbol() == std::string("embed-addr"));
}

BOOST_AUTO_TEST_CASE(find_encode_addr_returns_expected_value)
{
    BOOST_REQUIRE(encode_addr::symbol() == std::string("encode-addr"));
}

BOOST_AUTO_TEST_CASE(find_fetch_block_header_returns_expected_value)
{
    BOOST_REQUIRE(fetch_block_header::symbol() == std::string("fetch-block-header"));
}

BOOST_AUTO_TEST_CASE(find_fetch_last_height_returns_expected_value)
{
    BOOST_REQUIRE(fetch_last_height::symbol() == std::string("fetch-last-height"));
}

BOOST_AUTO_TEST_CASE(find_fetch_stealth_returns_expected_value)
{
    BOOST_REQUIRE(fetch_stealth::symbol() == std::string("fetch-stealth"));
}

BOOST_AUTO_TEST_CASE(find_fetch_transaction_returns_expected_value)
{
    BOOST_REQUIRE(fetch_transaction::symbol() == std::string("fetch-transaction"));
}

BOOST_AUTO_TEST_CASE(find_fetch_transaction_index_returns_expected_value)
{
    BOOST_REQUIRE(fetch_transaction_index::symbol() == std::string("fetch-transaction-index"));
}

BOOST_AUTO_TEST_CASE(find_genaddr_returns_expected_value)
{
    BOOST_REQUIRE(genaddr::symbol() == std::string("genaddr"));
}

BOOST_AUTO_TEST_CASE(find_genpriv_returns_expected_value)
{
    BOOST_REQUIRE(genpriv::symbol() == std::string("genpriv"));
}

BOOST_AUTO_TEST_CASE(find_genpub_returns_expected_value)
{
    BOOST_REQUIRE(genpub::symbol() == std::string("genpub"));
}

BOOST_AUTO_TEST_CASE(find_get_pubkey_returns_expected_value)
{
    BOOST_REQUIRE(get_pubkey::symbol() == std::string("get-pubkey"));
}

BOOST_AUTO_TEST_CASE(find_get_utxo_returns_expected_value)
{
    BOOST_REQUIRE(get_utxo::symbol() == std::string("get-utxo"));
}

BOOST_AUTO_TEST_CASE(find_hd_priv_returns_expected_value)
{
    BOOST_REQUIRE(hd_priv::symbol() == std::string("hd-priv"));
}

BOOST_AUTO_TEST_CASE(find_hd_pub_returns_expected_value)
{
    BOOST_REQUIRE(hd_pub::symbol() == std::string("hd-pub"));
}

BOOST_AUTO_TEST_CASE(find_hd_seed_returns_expected_value)
{
    BOOST_REQUIRE(hd_seed::symbol() == std::string("hd-seed"));
}

BOOST_AUTO_TEST_CASE(find_hd_to_address_returns_expected_value)
{
    BOOST_REQUIRE(hd_to_address::symbol() == std::string("hd-to-address"));
}

BOOST_AUTO_TEST_CASE(find_hd_to_wif_returns_expected_value)
{
    BOOST_REQUIRE(hd_to_wif::symbol() == std::string("hd-to-wif"));
}

BOOST_AUTO_TEST_CASE(find_history_returns_expected_value)
{
    BOOST_REQUIRE(history::symbol() == std::string("history"));
}

BOOST_AUTO_TEST_CASE(find_initchain_returns_expected_value)
{
    BOOST_REQUIRE(initchain::symbol() == std::string("initchain"));
}

BOOST_AUTO_TEST_CASE(find_mktx_returns_expected_value)
{
    BOOST_REQUIRE(mktx::symbol() == std::string("mktx"));
}

BOOST_AUTO_TEST_CASE(find_mnemonic_returns_expected_value)
{
    BOOST_REQUIRE(mnemonic::symbol() == std::string("mnemonic"));
}

BOOST_AUTO_TEST_CASE(find_monitor_returns_expected_value)
{
    BOOST_REQUIRE(monitor::symbol() == std::string("monitor"));
}

BOOST_AUTO_TEST_CASE(find_mpk_returns_expected_value)
{
    BOOST_REQUIRE(mpk::symbol() == std::string("mpk"));
}

BOOST_AUTO_TEST_CASE(find_newkey_returns_expected_value)
{
    BOOST_REQUIRE(newkey::symbol() == std::string("newkey"));
}

BOOST_AUTO_TEST_CASE(find_newseed_returns_expected_value)
{
    BOOST_REQUIRE(newseed::symbol() == std::string("newseed"));
}

BOOST_AUTO_TEST_CASE(find_pubkey_returns_expected_value)
{
    BOOST_REQUIRE(pubkey::symbol() == std::string("pubkey"));
}

BOOST_AUTO_TEST_CASE(find_qrcode_returns_expected_value)
{
    BOOST_REQUIRE(qrcode::symbol() == std::string("qrcode"));
}

BOOST_AUTO_TEST_CASE(find_rawscript_returns_expected_value)
{
    BOOST_REQUIRE(rawscript::symbol() == std::string("rawscript"));
}

BOOST_AUTO_TEST_CASE(find_ripemd_hash_returns_expected_value)
{
    BOOST_REQUIRE(ripemd_hash::symbol() == std::string("ripemd-hash"));
}

BOOST_AUTO_TEST_CASE(find_satoshi_returns_expected_value)
{
    BOOST_REQUIRE(satoshi::symbol() == std::string("satoshi"));
}

BOOST_AUTO_TEST_CASE(find_scripthash_returns_expected_value)
{
    BOOST_REQUIRE(scripthash::symbol() == std::string("scripthash"));
}

BOOST_AUTO_TEST_CASE(find_secret_to_wif_returns_expected_value)
{
    BOOST_REQUIRE(secret_to_wif::symbol() == std::string("secret-to-wif"));
}

BOOST_AUTO_TEST_CASE(find_sendtx_bci_returns_expected_value)
{
    BOOST_REQUIRE(sendtx_bci::symbol() == std::string("sendtx-bci"));
}

BOOST_AUTO_TEST_CASE(find_sendtx_node_returns_expected_value)
{
    BOOST_REQUIRE(sendtx_node::symbol() == std::string("sendtx-node"));
}

BOOST_AUTO_TEST_CASE(find_sendtx_obelisk_returns_expected_value)
{
    BOOST_REQUIRE(sendtx_obelisk::symbol() == std::string("sendtx-obelisk"));
}

BOOST_AUTO_TEST_CASE(find_sendtx_p2p_returns_expected_value)
{
    BOOST_REQUIRE(sendtx_p2p::symbol() == std::string("sendtx-p2p"));
}

BOOST_AUTO_TEST_CASE(find_set_input_returns_expected_value)
{
    BOOST_REQUIRE(set_input::symbol() == std::string("set-input"));
}

BOOST_AUTO_TEST_CASE(find_sha256_returns_expected_value)
{
    BOOST_REQUIRE(sha256::symbol() == std::string("sha256"));
}

BOOST_AUTO_TEST_CASE(find_showblkhead_returns_expected_value)
{
    BOOST_REQUIRE(showblkhead::symbol() == std::string("showblkhead"));
}

BOOST_AUTO_TEST_CASE(find_showscript_returns_expected_value)
{
    BOOST_REQUIRE(showscript::symbol() == std::string("showscript"));
}

BOOST_AUTO_TEST_CASE(find_showtx_returns_expected_value)
{
    BOOST_REQUIRE(showtx::symbol() == std::string("showtx"));
}

BOOST_AUTO_TEST_CASE(find_sign_input_returns_expected_value)
{
    BOOST_REQUIRE(sign_input::symbol() == std::string("sign-input"));
}

BOOST_AUTO_TEST_CASE(find_stealth_addr_returns_expected_value)
{
    BOOST_REQUIRE(stealth_addr::symbol() == std::string("stealth-addr"));
}

BOOST_AUTO_TEST_CASE(find_stealth_initiate_returns_expected_value)
{
    BOOST_REQUIRE(stealth_initiate::symbol() == std::string("stealth-initiate"));
}

BOOST_AUTO_TEST_CASE(find_stealth_newkey_returns_expected_value)
{
    BOOST_REQUIRE(stealth_newkey::symbol() == std::string("stealth-newkey"));
}

BOOST_AUTO_TEST_CASE(find_stealth_show_addr_returns_expected_value)
{
    BOOST_REQUIRE(stealth_show_addr::symbol() == std::string("stealth-show-addr"));
}

BOOST_AUTO_TEST_CASE(find_stealth_uncover_returns_expected_value)
{
    BOOST_REQUIRE(stealth_uncover::symbol() == std::string("stealth-uncover"));
}

BOOST_AUTO_TEST_CASE(find_stealth_uncover_secret_returns_expected_value)
{
    BOOST_REQUIRE(stealth_uncover_secret::symbol() == std::string("stealth-uncover-secret"));
}

BOOST_AUTO_TEST_CASE(find_unwrap_returns_expected_value)
{
    BOOST_REQUIRE(unwrap::symbol() == std::string("unwrap"));
}

BOOST_AUTO_TEST_CASE(find_validaddr_returns_expected_value)
{
    BOOST_REQUIRE(validaddr::symbol() == std::string("validaddr"));
}

BOOST_AUTO_TEST_CASE(find_validsig_returns_expected_value)
{
    BOOST_REQUIRE(validsig::symbol() == std::string("validsig"));
}

BOOST_AUTO_TEST_CASE(find_validtx_returns_expected_value)
{
    BOOST_REQUIRE(validtx::symbol() == std::string("validtx"));
}

BOOST_AUTO_TEST_CASE(find_wallet_returns_expected_value)
{
    BOOST_REQUIRE(wallet::symbol() == std::string("wallet"));
}

BOOST_AUTO_TEST_CASE(find_watchtx_returns_expected_value)
{
    BOOST_REQUIRE(watchtx::symbol() == std::string("watchtx"));
}

BOOST_AUTO_TEST_CASE(find_wif_to_secret_returns_expected_value)
{
    BOOST_REQUIRE(wif_to_secret::symbol() == std::string("wif-to-secret"));
}

BOOST_AUTO_TEST_CASE(find_wrap_returns_expected_value)
{
    BOOST_REQUIRE(wrap::symbol() == std::string("wrap"));
}

BOOST_AUTO_TEST_SUITE_END()
