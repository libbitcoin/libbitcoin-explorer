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

#define NOISE_CERT_AUTHORITY "8db036afbf4962033bf40ab365acbff06ff97557748ec0bfcc73bdaa9f93c10f"
#define NOISE_CERT_SERVER "0291bd579c76a31b32915c07b4d300f64e33094c325b319c5f170b668de459526f"
#define NOISE_CERT_AUXILIARY "55ecfd017c7b5ddc8cb19c6af2891e9f56206be5e704e49e05acc9bd0407279f"
#define NOISE_CERT_ZERO_AUXILIARY "000000f1536500a03e7140b8cd07c4ecb4868ab34d5a0601b7ad489e08101385509240d3a5a158ff37368d79c4b898ef149087e2e3a7b08cdff99e8ef1e0842dcf3367c206f061200d0d"
#define NOISE_CERT_WITH_AUXILIARY "000000f1536500a03e71d9a7d0e2f0420514b3f6ae198d6097e05c6eaa9ea74e22a164ad9b6ae20b2883a6d7ca14036b939eda110235e4819fdfbe60316a55bdd6cf8e3d8baea4bfde11"

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

BC_AUTO_TEST_CASE(noise_cert__invoke__odd_server_key__same_output)
{
    BX_DECLARE_COMMAND(noise_cert);
    command.set_valid_from_option(1700000000);
    command.set_days_option(2314);
    command.set_server_public_key_argument({ "0391bd579c76a31b32915c07b4d300f64e33094c325b319c5f170b668de459526f" });
    command.set_authority_private_key_argument({ NOISE_CERT_AUTHORITY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(NOISE_CERT_ZERO_AUXILIARY "\n");
}

BC_AUTO_TEST_CASE(noise_cert__invoke__default_valid_from__current_window)
{
    BX_DECLARE_COMMAND(noise_cert);
    command.set_days_option(1);
    command.set_server_public_key_argument({ NOISE_CERT_SERVER });
    command.set_authority_private_key_argument({ NOISE_CERT_AUTHORITY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    network::noise::certificate::data certificate{};
    BC_REQUIRE(decode_base16(certificate, system::trim_copy(output.str())));
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

BC_AUTO_TEST_CASE(noise_cert__invoke__zero_secret__failure_error)
{
    BX_DECLARE_COMMAND(noise_cert);
    command.set_valid_from_option(1700000000);
    command.set_server_public_key_argument({ NOISE_CERT_SERVER });
    command.set_authority_private_key_argument(explorer::config::ec_private{ ec_secret{} });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_NOISE_CERT_INVALID_KEY "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
