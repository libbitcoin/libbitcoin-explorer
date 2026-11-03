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
BC_AUTO_TEST_SUITE(config__byte)

BC_AUTO_TEST_CASE(byte__stream_out__token__round_trips)
{
    std::stringstream text;
    text << explorer::config::byte("42");
    BC_REQUIRE_EQUAL(text.str(), "42");
}

BC_AUTO_TEST_CASE(byte__stream_out__value__round_trips)
{
    const explorer::config::byte::type& value = explorer::config::byte("255");
    std::stringstream text;
    text << explorer::config::byte(value);
    BC_REQUIRE_EQUAL(text.str(), "255");
}

BC_AUTO_TEST_CASE(byte__constructor__non_numeric__throws_istream_exception)
{
    BC_REQUIRE_THROW(explorer::config::byte("baadf00d"), istream_exception);
}

BC_AUTO_TEST_CASE(byte__constructor__above_maximum__throws_istream_exception)
{
    BC_REQUIRE_THROW(explorer::config::byte("256"), istream_exception);
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
