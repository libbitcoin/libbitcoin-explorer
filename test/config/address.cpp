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

#define ADDRESS_MAINNET_A "15mKKb2eos1hWa6tisdPwwDC1a5J1y9nma"

BC_AUTO_TEST_SUITE(config)
BC_AUTO_TEST_SUITE(config__address)

BC_AUTO_TEST_CASE(address__constructor__default__does_not_throw)
{
    BC_REQUIRE_NO_THROW(address());
}

BC_AUTO_TEST_CASE(address__constructor__valid_string_cast__round_trips)
{
    const wallet::payment_address address(ADDRESS_MAINNET_A);
    BC_REQUIRE_EQUAL(address.encoded(), ADDRESS_MAINNET_A);
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
