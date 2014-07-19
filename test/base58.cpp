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
#include <iostream>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <sx/sx.hpp>
#include "command.hpp"

SX_USING_NAMESPACES()

// This is a namespace for tests by class/file__method/function.
BOOST_AUTO_TEST_SUITE(base58__invoke)

BOOST_AUTO_TEST_CASE(base58__constructor__bogus_text__throws_invalid_option_exception)
{
    SX_REQUIRE_INVALID_OPTION_VALUE_EXCEPTION(base58("*%^$&#@!"));
}

BOOST_AUTO_TEST_CASE(base58__constructor__valid_text__does_not_throw)
{
    BOOST_REQUIRE_NO_THROW(base58("vYxp6yFC7qiVtK1RcGQQt3L6EqTc8YhEDLnSMLqDvp8D"));
}

BOOST_AUTO_TEST_CASE(base58__constructor__valid_text__cast_returns_data)
{
    auto test = base58("vYxp6yFC7qiVtK1RcGQQt3L6EqTc8YhEDLnSMLqDvp8D");
    auto cast = const_cast<bc::data_chunk&>((const bc::data_chunk&)test);
    BOOST_REQUIRE(std::equal(cast.begin(), cast.end(), test.data().begin()));
}

BOOST_AUTO_TEST_CASE(base58__constructor__valid_data_chunk__round_trips_data)
{
    auto value = bc::decode_base58("vYxp6yFC7qiVtK1RcGQQt3L6EqTc8YhEDLnSMLqDvp8D");
    BOOST_REQUIRE(std::equal(value.begin(), value.end(), base58(value).data().begin()));
}

BOOST_AUTO_TEST_CASE(base58__serializers__valid_value__round_trips)
{
    SX_SERIALIZE_COPY_ROUND_TRIP(base58, "vYxp6yFC7qiVtK1RcGQQt3L6EqTc8YhEDLnSMLqDvp8D");
}

BOOST_AUTO_TEST_SUITE_END()