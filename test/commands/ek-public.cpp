/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(ek_public__invoke)

// Wiki Examples

BOOST_AUTO_TEST_CASE(ek_public__invoke__example_1_lot_sequence__okay)
{
    BX_DECLARE_COMMAND(ek_public);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_token_argument({ "passphrasecpXbDpHuo8F7yuZqR49koDA9uQojPijjjZaxsar7Woo9pfHJbeWF3VMU9EPBqJ" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("cfrm38VXASNzNjsak8pLc3ZtyPnBNDxAAbB18KMMCSjf8ZhW3FVTeuw2r9J3tyAUNyhfM7VMZuP\n");
}

BOOST_AUTO_TEST_CASE(ek_public__invoke__example_2__okay)
{
    BX_DECLARE_COMMAND(ek_public);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_token_argument({ "passphraseryQXuRZZQ3Jw5rAT7m6MzxkGSSRmysq3Ayj9vuEHEnbVPJSmRQ2xYFKDKjGYrq" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("cfrm38VUVm4ZGXku7wWGiLfAJNoeDHConFb9CugfTnR1SQC1jf3uwyKULmCMk4SUhsXasMyPcA9\n");
}

BOOST_AUTO_TEST_CASE(ek_public__invoke__example_3_piped_commands__okay)
{
    BX_DECLARE_COMMAND(ek_public);
    command.set_seed_argument({ "7113f4c2e8f67b61225c9a619cd984b63f28df434bf18217" });
    command.set_token_argument({ "passphraseryQXuRZZQ3Jw5rAT7m6MzxkGSSRmysq3Ayj9vuEHEnbVPJSmRQ2xYFKDKjGYrq" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("cfrm38VURwDvZXxV2AfWnHe6GwDxSG4FkrK4en7VdaxLPMxMnU8BaLneNVAwf19TAkbmAptNNaH\n");
}

BOOST_AUTO_TEST_CASE(ek_public__invoke__example_4_invalid_seed__failure_error)
{
    BX_DECLARE_COMMAND(ek_public);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_token_argument({ "passphraseryQXuRZZQ3Jw5rAT7m6MzxkGSSRmysq3Ayj9vuEHEnbVPJSmRQ2xYFKDKjGYrq" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EK_PUBLIC_SHORT_SEED "\n");
}

BOOST_AUTO_TEST_CASE(ek_public__invoke__example_5_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_public);
    command.set_uncompressed_option(true);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_token_argument({ "passphraseryQXuRZZQ3Jw5rAT7m6MzxkGSSRmysq3Ayj9vuEHEnbVPJSmRQ2xYFKDKjGYrq" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("cfrm38V5FtqpFoBNE9wpKjp5Fe97tM7YX6brNPCjpb9uLiqENKfeHHUKLd2VrvQhuHVUwgNVaSt\n");
}

BOOST_AUTO_TEST_CASE(ek_public__invoke__example_6_testnet__okay)
{
    BX_DECLARE_COMMAND(ek_public);
    command.set_version_option(111);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_token_argument({ "passphraseryQXuRZZQ3Jw5rAT7m6MzxkGSSRmysq3Ayj9vuEHEnbVPJSmRQ2xYFKDKjGYrq" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("cfrm2zc7BCp4KwhEE6HzSSxVhUyj2ky8bzvSLEqmAPcakQXb49uFQ87UEg8EhbuwA33t8db2fYW\n");
}

BOOST_AUTO_TEST_CASE(ek_public__invoke__example_7_testnet_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_public);
    command.set_version_option(111);
    command.set_uncompressed_option(true);
    command.set_seed_argument({ "baadf00dbaadf00dbaadf00dbaadf00dbaadf00dbaadf00d" });
    command.set_token_argument({ "passphraseryQXuRZZQ3Jw5rAT7m6MzxkGSSRmysq3Ayj9vuEHEnbVPJSmRQ2xYFKDKjGYrq" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("cfrm2zbi4iuQJ7cY69uJZsxhYLk4wLY7UWQiZ1wH5b3pEnzczSH3GHY3hAyV5AiWmU7mpk2Bqqc\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
