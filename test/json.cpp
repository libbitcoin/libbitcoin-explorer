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
using namespace bc::explorer;
using namespace bc::system;

#define JSON_URI "bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L?amount=0.42&label=l&message=m&r=https://x"

BC_AUTO_TEST_SUITE(json_tests)

BC_AUTO_TEST_CASE(json__to_json__flat_setting__expected)
{
    const settings_list list{ { "version", "42" } };
    const auto expected = "{\"settings\":{\"version\":\"42\"}}";
    BC_REQUIRE_EQUAL(system::json::serialize(to_json(list)), expected);
}

BC_AUTO_TEST_CASE(json__to_json__sectioned_setting__nested)
{
    const settings_list list{ { "wallet.version", "42" } };
    const auto expected = "{\"settings\":{\"wallet\":{\"version\":\"42\"}}}";
    BC_REQUIRE_EQUAL(system::json::serialize(to_json(list)), expected);
}

BC_AUTO_TEST_CASE(json__to_json__empty_uri__scheme_only)
{
    const auto expected = "{\"uri\":{\"scheme\":\"bitcoin\"}}";
    BC_REQUIRE_EQUAL(system::json::serialize(to_json(wallet::bitcoin_uri{})), expected);
}

BC_AUTO_TEST_CASE(json__to_json__populated_uri__all_properties)
{
    const auto value = system::json::serialize(to_json(wallet::bitcoin_uri{ JSON_URI }));
    BC_REQUIRE_NE(value.find("address"), std::string::npos);
    BC_REQUIRE_NE(value.find("amount"), std::string::npos);
    BC_REQUIRE_NE(value.find("label"), std::string::npos);
    BC_REQUIRE_NE(value.find("message"), std::string::npos);
    BC_REQUIRE_NE(value.find("scheme"), std::string::npos);
}

BC_AUTO_TEST_SUITE_END()
