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
BC_AUTO_TEST_SUITE(config__sighash)

BC_AUTO_TEST_CASE(sighash__stream_out__default__expected)
{
    std::stringstream text;
    text << sighash();
    BC_REQUIRE_EQUAL(text.str(), "all");
}

BC_AUTO_TEST_CASE(sighash__stream_out__all__expected)
{
    std::stringstream text;
    text << sighash("all");
    BC_REQUIRE_EQUAL(text.str(), "all");
}

BC_AUTO_TEST_CASE(sighash__stream_out__none__expected)
{
    std::stringstream text;
    text << sighash("none");
    BC_REQUIRE_EQUAL(text.str(), "none");
}

BC_AUTO_TEST_CASE(sighash__stream_out__single__expected)
{
    std::stringstream text;
    text << sighash("single");
    BC_REQUIRE_EQUAL(text.str(), "single");
}

BC_AUTO_TEST_CASE(sighash__constructor__unknown_token__throws_istream_exception)
{
    BC_REQUIRE_THROW(sighash("baadf00d"), istream_exception);
}

BC_AUTO_TEST_CASE(sighash__constructor__value__round_trips)
{
    std::stringstream text;
    text << sighash(sighash::type::hash_none);
    BC_REQUIRE_EQUAL(text.str(), "none");
}

BC_AUTO_TEST_CASE(sighash__cast__value__expected)
{
    const sighash::type& value = sighash("none");
    BC_REQUIRE(value == sighash::type::hash_none);
}


BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
