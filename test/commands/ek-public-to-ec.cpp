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

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(ek_public_to_ec__invoke)

#ifdef WITH_ICU

// Wiki Examples

BOOST_AUTO_TEST_CASE(ek_public_to_ec__invoke__example_1_lot_sequence__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_ec);
    command.set_passphrase_argument({ "my passphrase" });
    command.set_ek_public_key_argument({ "cfrm38VXASNzNjsak8pLc3ZtyPnBNDxAAbB18KMMCSjf8ZhW3FVTeuw2r9J3tyAUNyhfM7VMZuP" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("03d9cf7e2d52421ba735dc3aeca8a4b42e4fc272d4db6f7b311fb778bac7d4308d\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_ec__invoke__example_2__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_ec);
    command.set_passphrase_argument({ "my passphrase" });
    command.set_ek_public_key_argument({ "cfrm38VUVm4ZGXku7wWGiLfAJNoeDHConFb9CugfTnR1SQC1jf3uwyKULmCMk4SUhsXasMyPcA9" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("037b49ab1aadf965a885932451c87de4265799cb29749f5713c2f8ace9d7e83875\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_ec__invoke__example_3_piped_commands__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_ec);
    command.set_passphrase_argument({ "my passphrase" });
    command.set_ek_public_key_argument({ "cfrm38VURwDvZXxV2AfWnHe6GwDxSG4FkrK4en7VdaxLPMxMnU8BaLneNVAwf19TAkbmAptNNaH" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0355ceb3cb0c6b1294c76cb9a6ebb61035c5e7220099647ce4c2df011ee7280460\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_ec__invoke__example_4_incorrect_passphrase__failure_error)
{
    BX_DECLARE_COMMAND(ek_public_to_ec);
    command.set_passphrase_argument("i forgot");
    command.set_ek_public_key_argument({ "cfrm38VURwDvZXxV2AfWnHe6GwDxSG4FkrK4en7VdaxLPMxMnU8BaLneNVAwf19TAkbmAptNNaH" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EK_PUBLIC_TO_EC_INVALID_PASSPHRASE "\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_ec__invoke__example_5_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_ec);
    command.set_passphrase_argument({ "my passphrase" });
    command.set_ek_public_key_argument({ "cfrm38V5FtqpFoBNE9wpKjp5Fe97tM7YX6brNPCjpb9uLiqENKfeHHUKLd2VrvQhuHVUwgNVaSt" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("047b49ab1aadf965a885932451c87de4265799cb29749f5713c2f8ace9d7e838753b15f90fb4032de40029a80c45bf9d8fc8653d81b4f18d36464840ddce50a4f9\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_ec__invoke__example_6_testnet__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_ec);
    command.set_passphrase_argument({ "my passphrase" });
    command.set_ek_public_key_argument({ "cfrm2zc7BCp4KwhEE6HzSSxVhUyj2ky8bzvSLEqmAPcakQXb49uFQ87UEg8EhbuwA33t8db2fYW" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("037b49ab1aadf965a885932451c87de4265799cb29749f5713c2f8ace9d7e83875\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_ec__invoke__example_7_testnet_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_ec);
    command.set_passphrase_argument({ "my passphrase" });
    command.set_ek_public_key_argument({ "cfrm2zbi4iuQJ7cY69uJZsxhYLk4wLY7UWQiZ1wH5b3pEnzczSH3GHY3hAyV5AiWmU7mpk2Bqqc" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("047b49ab1aadf965a885932451c87de4265799cb29749f5713c2f8ace9d7e838753b15f90fb4032de40029a80c45bf9d8fc8653d81b4f18d36464840ddce50a4f9\n");
}

#else // WITH_ICU

BOOST_AUTO_TEST_CASE(ek_public_to_ec__invoke__not_icu__failure_error)
{
    BX_DECLARE_COMMAND(ek_to_ec);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EK_PUBLIC_TO_EC_REQUIRES_ICU "\n");
}

#endif // !WITH_ICU

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
