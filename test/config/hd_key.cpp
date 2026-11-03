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
#include <bitcoin/explorer.hpp>

using namespace bc;
using namespace bc::explorer::config;
using namespace bc::system;

#define HD_KEY_MAINNET "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi"

BC_AUTO_TEST_SUITE(config)
BC_AUTO_TEST_SUITE(config__hd_key)

BC_AUTO_TEST_CASE(hd_key__stream_out__token__round_trips)
{
    std::stringstream text;
    text << hd_key(HD_KEY_MAINNET);
    BC_REQUIRE_EQUAL(text.str(), HD_KEY_MAINNET);
}

BC_AUTO_TEST_CASE(hd_key__stream_out__value__round_trips)
{
    const hd_key::type value = hd_key(HD_KEY_MAINNET);
    std::stringstream text;
    text << hd_key(value);
    BC_REQUIRE_EQUAL(text.str(), HD_KEY_MAINNET);
}

BC_AUTO_TEST_CASE(hd_key__constructor__not_base58__throws_istream_exception)
{
    BC_REQUIRE_THROW(hd_key("baadf00d0"), istream_exception);
}

BC_AUTO_TEST_CASE(hd_key__constructor__short_key__throws_istream_exception)
{
    BC_REQUIRE_THROW(hd_key("baadf00d"), istream_exception);
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
