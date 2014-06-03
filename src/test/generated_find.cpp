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

/********** WARNING: This file is generated, do not edit directly. **********/

using namespace sx::extensions;

BOOST_AUTO_TEST_SUITE(test_suite)

BOOST_AUTO_TEST_CASE(find_addr_returns_object)
{
    BOOST_REQUIRE(find(addr::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_balance_returns_object)
{
    BOOST_REQUIRE(find(balance::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_base58_decode_returns_object)
{
    BOOST_REQUIRE(find(base58_decode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_base58_encode_returns_object)
{
    BOOST_REQUIRE(find(base58_encode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_base58check_decode_returns_object)
{
    BOOST_REQUIRE(find(base58check_decode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_base58check_encode_returns_object)
{
    BOOST_REQUIRE(find(base58check_encode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_bci_fetch_last_height_returns_object)
{
    BOOST_REQUIRE(find(bci_fetch_last_height::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_bci_history_returns_object)
{
    BOOST_REQUIRE(find(bci_history::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_blke_fetch_transaction_returns_object)
{
    BOOST_REQUIRE(find(blke_fetch_transaction::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_brainwallet_returns_object)
{
    BOOST_REQUIRE(find(brainwallet::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_btc_returns_object)
{
    BOOST_REQUIRE(find(btc::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_decode_addr_returns_object)
{
    BOOST_REQUIRE(find(decode_addr::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_ec_add_modp_returns_object)
{
    BOOST_REQUIRE(find(ec_add_modp::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_ec_multiply_returns_object)
{
    BOOST_REQUIRE(find(ec_multiply::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_ec_tweak_add_returns_object)
{
    BOOST_REQUIRE(find(ec_tweak_add::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_ec_add_returns_object)
{
    BOOST_REQUIRE(find(ec_add::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_embed_addr_returns_object)
{
    BOOST_REQUIRE(find(embed_addr::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_encode_addr_returns_object)
{
    BOOST_REQUIRE(find(encode_addr::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_fetch_block_header_returns_object)
{
    BOOST_REQUIRE(find(fetch_block_header::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_fetch_last_height_returns_object)
{
    BOOST_REQUIRE(find(fetch_last_height::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_fetch_stealth_returns_object)
{
    BOOST_REQUIRE(find(fetch_stealth::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_fetch_transaction_returns_object)
{
    BOOST_REQUIRE(find(fetch_transaction::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_fetch_transaction_index_returns_object)
{
    BOOST_REQUIRE(find(fetch_transaction_index::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_genaddr_returns_object)
{
    BOOST_REQUIRE(find(genaddr::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_genpriv_returns_object)
{
    BOOST_REQUIRE(find(genpriv::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_genpub_returns_object)
{
    BOOST_REQUIRE(find(genpub::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_get_pubkey_returns_object)
{
    BOOST_REQUIRE(find(get_pubkey::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_get_utxo_returns_object)
{
    BOOST_REQUIRE(find(get_utxo::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_hd_priv_returns_object)
{
    BOOST_REQUIRE(find(hd_priv::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_hd_pub_returns_object)
{
    BOOST_REQUIRE(find(hd_pub::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_hd_seed_returns_object)
{
    BOOST_REQUIRE(find(hd_seed::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_hd_to_address_returns_object)
{
    BOOST_REQUIRE(find(hd_to_address::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_hd_to_wif_returns_object)
{
    BOOST_REQUIRE(find(hd_to_wif::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_history_returns_object)
{
    BOOST_REQUIRE(find(history::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_initchain_returns_object)
{
    BOOST_REQUIRE(find(initchain::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_mktx_returns_object)
{
    BOOST_REQUIRE(find(mktx::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_mnemonic_returns_object)
{
    BOOST_REQUIRE(find(mnemonic::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_monitor_returns_object)
{
    BOOST_REQUIRE(find(monitor::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_mpk_returns_object)
{
    BOOST_REQUIRE(find(mpk::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_newkey_returns_object)
{
    BOOST_REQUIRE(find(newkey::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_newseed_returns_object)
{
    BOOST_REQUIRE(find(newseed::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_pubkey_returns_object)
{
    BOOST_REQUIRE(find(pubkey::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_qrcode_returns_object)
{
    BOOST_REQUIRE(find(qrcode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_rawscript_returns_object)
{
    BOOST_REQUIRE(find(rawscript::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_ripemd_hash_returns_object)
{
    BOOST_REQUIRE(find(ripemd_hash::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_satoshi_returns_object)
{
    BOOST_REQUIRE(find(satoshi::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_scripthash_returns_object)
{
    BOOST_REQUIRE(find(scripthash::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_secret_to_wif_returns_object)
{
    BOOST_REQUIRE(find(secret_to_wif::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_sendtx_bci_returns_object)
{
    BOOST_REQUIRE(find(sendtx_bci::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_sendtx_node_returns_object)
{
    BOOST_REQUIRE(find(sendtx_node::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_sendtx_obelisk_returns_object)
{
    BOOST_REQUIRE(find(sendtx_obelisk::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_sendtx_p2p_returns_object)
{
    BOOST_REQUIRE(find(sendtx_p2p::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_set_input_returns_object)
{
    BOOST_REQUIRE(find(set_input::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_sha256_returns_object)
{
    BOOST_REQUIRE(find(sha256::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_showblkhead_returns_object)
{
    BOOST_REQUIRE(find(showblkhead::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_showscript_returns_object)
{
    BOOST_REQUIRE(find(showscript::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_showtx_returns_object)
{
    BOOST_REQUIRE(find(showtx::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_sign_input_returns_object)
{
    BOOST_REQUIRE(find(sign_input::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_stealth_addr_returns_object)
{
    BOOST_REQUIRE(find(stealth_addr::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_stealth_initiate_returns_object)
{
    BOOST_REQUIRE(find(stealth_initiate::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_stealth_newkey_returns_object)
{
    BOOST_REQUIRE(find(stealth_newkey::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_stealth_show_addr_returns_object)
{
    BOOST_REQUIRE(find(stealth_show_addr::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_stealth_uncover_returns_object)
{
    BOOST_REQUIRE(find(stealth_uncover::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_stealth_uncover_secret_returns_object)
{
    BOOST_REQUIRE(find(stealth_uncover_secret::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_unwrap_returns_object)
{
    BOOST_REQUIRE(find(unwrap::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_validaddr_returns_object)
{
    BOOST_REQUIRE(find(validaddr::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_validsig_returns_object)
{
    BOOST_REQUIRE(find(validsig::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_validtx_returns_object)
{
    BOOST_REQUIRE(find(validtx::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_wallet_returns_object)
{
    BOOST_REQUIRE(find(wallet::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_watchtx_returns_object)
{
    BOOST_REQUIRE(find(watchtx::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_wif_to_secret_returns_object)
{
    BOOST_REQUIRE(find(wif_to_secret::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(find_wrap_returns_object)
{
    BOOST_REQUIRE(find(wrap::symbol()) != nullptr);
}
BOOST_AUTO_TEST_SUITE_END()
