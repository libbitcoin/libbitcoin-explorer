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

#define SECRET_VALID "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475"
#define SECRET_MAXIMUM "fffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364140"
#define SECRET_ZERO "0000000000000000000000000000000000000000000000000000000000000000"
#define SECRET_CURVE_ORDER "fffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141"
#define SECRET_ABOVE_CURVE_ORDER "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"

BC_AUTO_TEST_SUITE(config)
BC_AUTO_TEST_SUITE(config__ec_private)

BC_AUTO_TEST_CASE(ec_private__constructor__default__does_not_throw)
{
    BC_REQUIRE_NO_THROW(ec_private());
}

BC_AUTO_TEST_CASE(ec_private__constructor__valid_secret__round_trips)
{
    std::stringstream text;
    text << ec_private(SECRET_VALID);
    BC_REQUIRE_EQUAL(text.str(), SECRET_VALID);
}

BC_AUTO_TEST_CASE(ec_private__constructor__maximum_secret__round_trips)
{
    std::stringstream text;
    text << ec_private(SECRET_MAXIMUM);
    BC_REQUIRE_EQUAL(text.str(), SECRET_MAXIMUM);
}

BC_AUTO_TEST_CASE(ec_private__constructor__zero_secret__throws_istream_exception)
{
    BC_REQUIRE_THROW(ec_private(SECRET_ZERO), istream_exception);
}

BC_AUTO_TEST_CASE(ec_private__constructor__curve_order_secret__throws_istream_exception)
{
    BC_REQUIRE_THROW(ec_private(SECRET_CURVE_ORDER), istream_exception);
}

BC_AUTO_TEST_CASE(ec_private__constructor__secret_above_curve_order__throws_istream_exception)
{
    BC_REQUIRE_THROW(ec_private(SECRET_ABOVE_CURVE_ORDER), istream_exception);
}

BC_AUTO_TEST_CASE(ec_private__constructor__short_secret__throws_istream_exception)
{
    BC_REQUIRE_THROW(ec_private("baadf00d"), istream_exception);
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
