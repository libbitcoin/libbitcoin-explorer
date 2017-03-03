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

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(fetch_tx_index__invoke)

#define BX_FETCH_TX_INDEX_SATOSHIS_WORDS_INDEX_INFO \
"metadata\n" \
"{\n" \
"    hash 4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b\n" \
"    height 0\n" \
"    index 0\n" \
"}\n"

#define BX_FETCH_TX_SECOND_TX_HASH \
"0e3e2357e806b6cdb1f70b54c3a3a17b6714ee1f0e68bebb44a74b1efd512098"
#define BX_FETCH_TX_INDEX_SECOND_INDEX_XML \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" \
"<metadata><hash>0e3e2357e806b6cdb1f70b54c3a3a17b6714ee1f0e68bebb44a74b1efd512098</hash><height>1</height><index>0</index></metadata>\n"

BOOST_AUTO_TEST_CASE(fetch_tx_index__invoke__mainnet_satoshis_words_tx_info__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_tx_index);
    command.set_format_option({ "info" });
    command.set_hash_argument({ BX_SATOSHIS_WORDS_TX_HASH });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_TX_INDEX_SATOSHIS_WORDS_INDEX_INFO);
}

BOOST_AUTO_TEST_CASE(fetch_tx_index__invoke__mainnet_second_tx_xml__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(fetch_tx_index);
    command.set_format_option({ "xml" });
    command.set_hash_argument({ BX_FETCH_TX_SECOND_TX_HASH });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_FETCH_TX_INDEX_SECOND_INDEX_XML);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
