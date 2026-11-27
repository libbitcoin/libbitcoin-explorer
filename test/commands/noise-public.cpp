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

#include "command.hpp"

BX_USING_NAMESPACES()

BC_AUTO_TEST_SUITE(offline)
BC_AUTO_TEST_SUITE(noise_public__invoke)

BC_AUTO_TEST_CASE(noise_public__invoke__sri_secret__okay_output)
{
    BX_DECLARE_COMMAND(noise_public);
    command.set_private_key_argument({ "zmBEmPhqo3A92FkiLVvyCz6htc3e53ph3ZbD4ASqGaLjwnFLi" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("9bDuixKmZqAJnrmP746n8zU1wyAQRrus7th9dxnkPg6RzQvCnan\n");
}

BC_AUTO_TEST_CASE(noise_public__invoke__authority_secret__okay_output)
{
    BX_DECLARE_COMMAND(noise_public);
    command.set_private_key_argument({ "25QEpmYFaFWYQjKgNAWXYx1kbRTedtf5vHjDME7odqyYC8H6ND" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("9br3pDEyhsQoXmojoXVRsNGBa8xNw1F35npYzXM5yWDfZaxjaEo\n");
}

BC_AUTO_TEST_CASE(noise_public__invoke__short_secret__failure_error)
{
    BX_DECLARE_COMMAND(noise_public);
    command.set_private_key_argument({ "F8z47vJMDoZwmUo5LpvbRhVufAfS8AzJWcr1xXzh4r6bhyNZ" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_NOISE_PUBLIC_INVALID_KEY "\n");
}

BC_AUTO_TEST_CASE(noise_public__invoke__zero_secret__failure_error)
{
    BX_DECLARE_COMMAND(noise_public);
    command.set_private_key_argument({ "11111111111111111111111111111111273Yts" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_NOISE_PUBLIC_INVALID_KEY "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
