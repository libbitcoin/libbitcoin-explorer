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
BC_AUTO_TEST_SUITE(noise_cert__invoke)

#define NOISE_CERT_AUTHORITY "25QEpmYFaFWYQjKgNAWXYx1kbRTedtf5vHjDME7odqyYC8H6ND"
#define NOISE_CERT_SERVER "9bjktHscc8646ByxhrhYvbmU53kJCCNDjdtj4UBr6BE9WeJDyjF"
#define NOISE_CERT_AUXILIARY "55ecfd017c7b5ddc8cb19c6af2891e9f56206be5e704e49e05acc9bd0407279f"
#define NOISE_CERT_ZERO_AUXILIARY "1116HHrouQpWCg1ukz7WAxKhEJUNBnryHvvbp35SfdcMLBbZrc9biGDfTrQn95wMZAzHkYrnWH94pKyDJKaQmwutGqPiJYo3vpm7uXgFyJ"
#define NOISE_CERT_WITH_AUXILIARY "1116HHrouQpWD22NviaNRfWxKcikV6Hn5dPW3wtUxXNcMPXcHbR5KJacQNnKDtmdrKYHAtEgToywcN8cJcwukPi3BYGdhCNehngXAxoE3z"

BC_AUTO_TEST_CASE(noise_cert__invoke__zero_auxiliary__okay_output)
{
    BX_DECLARE_COMMAND(noise_cert);
    command.set_valid_from_option(1700000000);
    command.set_days_option(2314);
    command.set_server_public_key_argument({ NOISE_CERT_SERVER });
    command.set_authority_private_key_argument({ NOISE_CERT_AUTHORITY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(NOISE_CERT_ZERO_AUXILIARY "\n");
}

BC_AUTO_TEST_CASE(noise_cert__invoke__auxiliary__okay_output)
{
    BX_DECLARE_COMMAND(noise_cert);
    command.set_valid_from_option(1700000000);
    command.set_days_option(2314);
    command.set_auxiliary_option({ NOISE_CERT_AUXILIARY });
    command.set_server_public_key_argument({ NOISE_CERT_SERVER });
    command.set_authority_private_key_argument({ NOISE_CERT_AUTHORITY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(NOISE_CERT_WITH_AUXILIARY "\n");
}

BC_AUTO_TEST_CASE(noise_cert__invoke__default_valid_from__current_window)
{
    BX_DECLARE_COMMAND(noise_cert);
    command.set_days_option(1);
    command.set_server_public_key_argument({ NOISE_CERT_SERVER });
    command.set_authority_private_key_argument({ NOISE_CERT_AUTHORITY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    const data_chunk decoded = system::config::base58check{ system::trim_copy(output.str()) };
    constexpr auto size = std::tuple_size_v<network::noise::certificate::data>;
    BC_REQUIRE_EQUAL(decoded.size(), size);
    const auto certificate = data_slice{ decoded }.to_array<size>();
    const auto from = network::noise::certificate::valid_from(certificate);
    BC_REQUIRE_GT(from, 1700000000u);
    BC_REQUIRE_EQUAL(network::noise::certificate::not_valid_after(certificate), from + 86400u);
}

BC_AUTO_TEST_CASE(noise_cert__invoke__short_auxiliary__failure_error)
{
    BX_DECLARE_COMMAND(noise_cert);
    command.set_valid_from_option(1700000000);
    command.set_auxiliary_option({ "00" });
    command.set_server_public_key_argument({ NOISE_CERT_SERVER });
    command.set_authority_private_key_argument({ NOISE_CERT_AUTHORITY });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_NOISE_CERT_INVALID_AUXILIARY "\n");
}

BC_AUTO_TEST_CASE(noise_cert__invoke__validity_after_2106__failure_error)
{
    BX_DECLARE_COMMAND(noise_cert);
    command.set_valid_from_option(4294967295);
    command.set_days_option(1);
    command.set_server_public_key_argument({ NOISE_CERT_SERVER });
    command.set_authority_private_key_argument({ NOISE_CERT_AUTHORITY });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_NOISE_CERT_INVALID_VALIDITY "\n");
}

BC_AUTO_TEST_CASE(noise_cert__invoke__server_key_prefix__failure_error)
{
    BX_DECLARE_COMMAND(noise_cert);
    command.set_valid_from_option(1700000000);
    command.set_server_public_key_argument({ "JBNL3emnm3E2cCkWnFbM6hFiWFQ8cU6PBG2HWpHLZvwRqmueP3t" });
    command.set_authority_private_key_argument({ NOISE_CERT_AUTHORITY });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_NOISE_CERT_INVALID_SERVER "\n");
}

BC_AUTO_TEST_CASE(noise_cert__invoke__short_secret__failure_error)
{
    BX_DECLARE_COMMAND(noise_cert);
    command.set_valid_from_option(1700000000);
    command.set_server_public_key_argument({ NOISE_CERT_SERVER });
    command.set_authority_private_key_argument({ "F8z47vJMDoZwmUo5LpvbRhVufAfS8AzJWcr1xXzh4r6bhyNZ" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_NOISE_CERT_INVALID_KEY "\n");
}

BC_AUTO_TEST_CASE(noise_cert__invoke__zero_secret__failure_error)
{
    BX_DECLARE_COMMAND(noise_cert);
    command.set_valid_from_option(1700000000);
    command.set_server_public_key_argument({ NOISE_CERT_SERVER });
    command.set_authority_private_key_argument({ "11111111111111111111111111111111273Yts" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_NOISE_CERT_INVALID_KEY "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
