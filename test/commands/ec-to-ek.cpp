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
BOOST_AUTO_TEST_SUITE(ec_to_ek__invoke)

#ifdef WITH_ICU

// BI-38 Vectors

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__vector_0_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    command.set_ec_private_key_argument({ "cbf4b9f70470856bb4f40f80b87edb90865997ffee6df315ab166d713af433a5" });
    command.set_passphrase_argument("TestingOneTwoThree");
    command.set_uncompressed_option(true);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PRVWUbkzzsbcVac2qwfssoUJAN1Xhrg6bNk8J7Nzm5H7kxEbn2Nh2ZoGg\n");
}

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__vector_1_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    command.set_ec_private_key_argument({ "09c2686880095b1a4c249ee3ac4eea8a014f11e6f986d0b5025ac1f39afbd9ae" });
    command.set_passphrase_argument("Satoshi");
    command.set_uncompressed_option(true);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PRNFFkZc2NZ6dJqFfhRoFNMR9Lnyj7dYGrzdgXXVMXcxoKTePPX1dWByq\n");
}

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__vector_2__okay)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    command.set_ec_private_key_argument({ "cbf4b9f70470856bb4f40f80b87edb90865997ffee6df315ab166d713af433a5" });
    command.set_passphrase_argument("TestingOneTwoThree");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PYNKZ1EAgYgmQfmNVamxyXVWHzK5s6DGhwP4J5o44cvXdoY7sRzhtpUeo\n");
}

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__vector_3__okay)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    command.set_ec_private_key_argument({ "09c2686880095b1a4c249ee3ac4eea8a014f11e6f986d0b5025ac1f39afbd9ae" });
    command.set_passphrase_argument("Satoshi");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PYLtMnXvfG3oJde97zRyLYFZCYizPU5T3LwgdYJz1fRhh16bU7u6PPmY7\n");
}

// Wiki Examples

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__example_1_mainnet__okay)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    command.set_ec_private_key_argument({ "261fc32e9f29c70e3d898aa7db028c81ede0658e8ff8ffab8160073c048ae83f" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PYXCdvtrs4NN1TjUYbGS5Sd2gjsVsDm7GttqERRWvRjWDsrhQfJeEHrg5\n");
}

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__example_2_empty_passphrase__okay)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    command.set_ec_private_key_argument({ "261fc32e9f29c70e3d898aa7db028c81ede0658e8ff8ffab8160073c048ae83f" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PYXCdvttCfzn7bo5NrhXsSE1hrYgw2oLbGQCvSLMZV4qr7FEJK7fJhN4R\n");
}

// Redundant with #1
//BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__example_3_piped_commands__okay)
//{
//    BX_DECLARE_COMMAND(ec_to_ek);
//    command.set_ec_private_key_argument({ "261fc32e9f29c70e3d898aa7db028c81ede0658e8ff8ffab8160073c048ae83f" });
//    BX_REQUIRE_OKAY(command.invoke(output, error));
//    BX_REQUIRE_OUTPUT("6PYXCdvtrs4NN1TjUYbGS5Sd2gjsVsDm7GttqERRWvRjWDsrhQfJeEHrg5\n");
//}

// Redundant with #1
//BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__example_4_round_trip__okay)
//{
//    BX_DECLARE_COMMAND(ec_to_ek);
//    command.set_ec_private_key_argument({ "261fc32e9f29c70e3d898aa7db028c81ede0658e8ff8ffab8160073c048ae83f" });
//    BX_REQUIRE_OKAY(command.invoke(output, error));
//    BX_REQUIRE_OUTPUT("6PYXCdvtrs4NN1TjUYbGS5Sd2gjsVsDm7GttqERRWvRjWDsrhQfJeEHrg5\n");
//}

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__example_5_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    command.set_ec_private_key_argument({ "261fc32e9f29c70e3d898aa7db028c81ede0658e8ff8ffab8160073c048ae83f" });
    command.set_passphrase_argument("my passphrase");
    command.set_uncompressed_option(true);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PRPDbKfv3A45QPPfEtvcxM4oA6ShVL7t72VP74P1W3JEUHPrZXNy39FKe\n");
}

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__example_6_testnet__okay)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    command.set_ec_private_key_argument({ "261fc32e9f29c70e3d898aa7db028c81ede0658e8ff8ffab8160073c048ae83f" });
    command.set_passphrase_argument("my passphrase");
    command.set_version_option(111);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("8EzHSxX3sfZp6NjYUdt7fZAPCKByrFDS12PHfdexFLSaSAfM7wM7tw3Hof\n");
}

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__example_7_testnet_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    command.set_ec_private_key_argument({ "261fc32e9f29c70e3d898aa7db028c81ede0658e8ff8ffab8160073c048ae83f" });
    command.set_passphrase_argument("my passphrase");
    command.set_uncompressed_option(true);
    command.set_version_option(111);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("8EsMUV3Z5A9m8eA28nSYECHAmKmy4YsyCYpGNvzHocFJBFhVYZARNfrfnt\n");
}

#else // WITH_ICU

BOOST_AUTO_TEST_CASE(ec_to_ek__invoke__not_icu__failure_error)
{
    BX_DECLARE_COMMAND(ec_to_ek);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_TO_EK_REQUIRES_ICU "\n");
}

#endif // !WITH_ICU

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
