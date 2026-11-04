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
BC_AUTO_TEST_SUITE(config__group)

BC_AUTO_TEST_CASE(group__construct__default__zeros)
{
    const group::type value = group();
    BC_REQUIRE_EQUAL(value.threshold, 0u);
    BC_REQUIRE_EQUAL(value.count, 0u);
}

BC_AUTO_TEST_CASE(group__construct__token__expected)
{
    const group::type value = group("2/3");
    BC_REQUIRE_EQUAL(value.threshold, 2u);
    BC_REQUIRE_EQUAL(value.count, 3u);
}

BC_AUTO_TEST_CASE(group__construct__value__round_trips)
{
    std::stringstream text;
    text << group(group::type{ 16, 16 });
    BC_REQUIRE_EQUAL(text.str(), "16/16");
}

BC_AUTO_TEST_CASE(group__stream_out__token__round_trips)
{
    std::stringstream text;
    text << group("1/1");
    BC_REQUIRE_EQUAL(text.str(), "1/1");
}

BC_AUTO_TEST_CASE(group__construct__missing_count__throws_istream_exception)
{
    BC_REQUIRE_THROW(group("2"), istream_exception);
}

BC_AUTO_TEST_CASE(group__construct__extra_part__throws_istream_exception)
{
    BC_REQUIRE_THROW(group("2/3/4"), istream_exception);
}

BC_AUTO_TEST_CASE(group__construct__not_numeric__throws_istream_exception)
{
    BC_REQUIRE_THROW(group("a/b"), istream_exception);
}

BC_AUTO_TEST_CASE(group__construct__above_byte__throws_istream_exception)
{
    BC_REQUIRE_THROW(group("256/1"), istream_exception);
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
