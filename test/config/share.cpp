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
BC_AUTO_TEST_SUITE(config__share)

BC_AUTO_TEST_CASE(share__construct__default__invalid)
{
    const share::type value = share();
    BC_REQUIRE(!value);
}

BC_AUTO_TEST_CASE(share__construct__token__valid)
{
    const share::type value = share("duckling enlarge academic academic agency result length solution fridge kidney coal piece deal husband erode duke ajar critical decision keyboard");
    BC_REQUIRE(value);
    BC_REQUIRE_EQUAL(value.identifier(), 7945u);
}

BC_AUTO_TEST_CASE(share__stream_out__token__round_trips)
{
    std::stringstream text;
    text << share("duckling enlarge academic academic agency result length solution fridge kidney coal piece deal husband erode duke ajar critical decision keyboard");
    BC_REQUIRE_EQUAL(text.str(), "duckling enlarge academic academic agency result length solution fridge kidney coal piece deal husband erode duke ajar critical decision keyboard");
}

BC_AUTO_TEST_CASE(share__construct__invalid_checksum__throws_istream_exception)
{
    BC_REQUIRE_THROW(share("duckling enlarge academic academic agency result length solution fridge kidney coal piece deal husband erode duke ajar critical decision kidney"), istream_exception);
}

BC_AUTO_TEST_CASE(share__construct__non_dictionary__throws_istream_exception)
{
    BC_REQUIRE_THROW(share("foo bar baz"), istream_exception);
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
