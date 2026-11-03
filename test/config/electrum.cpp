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

BC_AUTO_TEST_SUITE(config)
BC_AUTO_TEST_SUITE(config__electrum)

BC_AUTO_TEST_CASE(electrum__stream_out__default__expected)
{
    std::stringstream text;
    text << electrum();
    BC_REQUIRE_EQUAL(text.str(), "standard");
}

BC_AUTO_TEST_CASE(electrum__stream_out__standard__expected)
{
    std::stringstream text;
    text << electrum("standard");
    BC_REQUIRE_EQUAL(text.str(), "standard");
}

BC_AUTO_TEST_CASE(electrum__stream_out__witness__expected)
{
    std::stringstream text;
    text << electrum("witness");
    BC_REQUIRE_EQUAL(text.str(), "witness");
}

BC_AUTO_TEST_CASE(electrum__stream_out__two_factor_authentication__expected)
{
    std::stringstream text;
    text << electrum("2fa");
    BC_REQUIRE_EQUAL(text.str(), "2fa");
}

BC_AUTO_TEST_CASE(electrum__stream_out__two_factor_authentication_witness__expected)
{
    std::stringstream text;
    text << electrum("2faw");
    BC_REQUIRE_EQUAL(text.str(), "2faw");
}

BC_AUTO_TEST_CASE(electrum__constructor__unknown_token__throws_istream_exception)
{
    BC_REQUIRE_THROW(electrum("baadf00d"), istream_exception);
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
