/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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
#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(ek_to_address__invoke)

#ifdef WITH_ICU

// BIP-38 vectors (with address derived for 0-5)

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__vector_0_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PRVWUbkzzsbcVac2qwfssoUJAN1Xhrg6bNk8J7Nzm5H7kxEbn2Nh2ZoGg" });
    command.set_passphrase_argument("TestingOneTwoThree");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1Jq6MksXQVWzrznvZzxkV6oY57oWXD9TXB\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__vector_1_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PRNFFkZc2NZ6dJqFfhRoFNMR9Lnyj7dYGrzdgXXVMXcxoKTePPX1dWByq" });
    command.set_passphrase_argument("Satoshi");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1AvKt49sui9zfzGeo8EyL8ypvAhtR2KwbL\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__vector_2__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PYNKZ1EAgYgmQfmNVamxyXVWHzK5s6DGhwP4J5o44cvXdoY7sRzhtpUeo" });
    command.set_passphrase_argument("TestingOneTwoThree");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("164MQi977u9GUteHr4EPH27VkkdxmfCvGW\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__vector_3__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PYLtMnXvfG3oJde97zRyLYFZCYizPU5T3LwgdYJz1fRhh16bU7u6PPmY7" });
    command.set_passphrase_argument("Satoshi");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1HmPbwsvG5qJ3KJfxzsZRZWhbm1xBMuS8B\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__vector_4_uncompressed_multiplied__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PfQu77ygVyJLZjfvMLyhLMQbYnu5uguoJJ4kMCLqWwPEdfpwANVS76gTX" });
    command.set_passphrase_argument("TestingOneTwoThree");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1PE6TQi6HTVNz5DLwB1LcpMBALubfuN2z2\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__vector_5_uncompressed_multiplied__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PfLGnQs6VZnrNpmVKfjotbnQuaJK4KZoPFrAjx1JMJUa1Ft8gnf5WxfKd" });
    command.set_passphrase_argument("Satoshi");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1CqzrtZC6mXSAhoxtFwVjz8LtwLJjDYU3V\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__vector_6_uncompressed_multiplied_lot__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PgNBNNzDkKdhkT6uJntUXwwzQV8Rr2tZcbkDcuC9DZRsS6AtHts4Ypo1j" });
    command.set_passphrase_argument({ "MOLON LABE" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1Jscj8ALrYu2y9TD8NrpvDBugPedmbj4Yh\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__vector_7_uncompressed_multiplied_lot__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PgGWtx25kUg8QWvwuJAgorN6k9FbE25rv5dMRwu5SKMnfpfVe5mar2ngH" });
    command.set_passphrase_argument("ΜΟΛΩΝ ΛΑΒΕ");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1Lurmih3KruL4xDB5FmHof38yawNtP9oGf\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__vector_8_uncompressed_multiplied__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PfPAw5HErFdzMyBvGMwSfSWjKmzgm3jDg7RxQyVCSSBJFZLAZ6hVupmpn" });
    command.set_passphrase_argument("libbitcoin test");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1NQgLnFz1ZzF6KkCJ4SM3xz3Jy1q2hEEax\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__vector_9_uncompressed_multiplied__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PfU2yS6DUHjgH8wmsJRT1rHWXRofmDV5UJ3dypocew56BDcw5TQJXFYfm" });
    command.set_passphrase_argument("Libbitcoin BIP38 Test Vector");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1NjjvGqXDrx1DvrhjYJxzrpyopk1ygHTSJ\n");
}

// Wiki Examples

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__example_1_mainnet__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PYXCdvtrs4NN1TjUYbGS5Sd2gjsVsDm7GttqERRWvRjWDsrhQfJeEHrg5" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1z5KLQyPycih1Tpx9jTYfuhHQkNsP7fd4\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__example_2_incorrect_passphrase__failure_error)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PYXCdvtrs4NN1TjUYbGS5Sd2gjsVsDm7GttqERRWvRjWDsrhQfJeEHrg5" });
    command.set_passphrase_argument("i forgot");
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EK_TO_EC_INVALID_PASSPHRASE "\n");
}

// Redundant with #1
//BOOST_AUTO_TEST_CASE(ek_to_address__invoke__example_3_piped_input__okay)
//{
//    BX_DECLARE_COMMAND(ek_to_address);
//    command.set_ek_private_key_argument({ "6PYXCdvtrs4NN1TjUYbGS5Sd2gjsVsDm7GttqERRWvRjWDsrhQfJeEHrg5" });
//    command.set_passphrase_argument("my passphrase");
//    BX_REQUIRE_OKAY(command.invoke(output, error));
//    BX_REQUIRE_OUTPUT("1z5KLQyPycih1Tpx9jTYfuhHQkNsP7fd4\n");
//}

// Redundant with #1
//BOOST_AUTO_TEST_CASE(ek_to_address__invoke__example_4_round_trip__okay)
//{
//    BX_DECLARE_COMMAND(ek_to_address);
//    command.set_ek_private_key_argument({ "6PYXCdvtrs4NN1TjUYbGS5Sd2gjsVsDm7GttqERRWvRjWDsrhQfJeEHrg5" });
//    command.set_passphrase_argument("my passphrase");
//    BX_REQUIRE_OKAY(command.invoke(output, error));
//    BX_REQUIRE_OUTPUT("1z5KLQyPycih1Tpx9jTYfuhHQkNsP7fd4\n");
//}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__example_5_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PRPDbKfv3A45QPPfEtvcxM4oA6ShVL7t72VP74P1W3JEUHPrZXNy39FKe" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1NNhf5AifHmYXw1cJmbdjkyv9DQFGGaw57\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__example_6_testnet__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "8EzHSxX3sfZp6NjYUdt7fZAPCKByrFDS12PHfdexFLSaSAfM7wM7tw3Hof" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("mgW2cPVxD13yU7wSfihqNb829QM5iGf9PL\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__example_7_litecoin_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "7BtJaSMBHZJMgKtDp4rNLDjkoCZu2e5av1FYxMwwvdq5AN124paeds82tP" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("LgbevHUYjx1bnjhmUuaw1n3gMRmXPyM13v\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__example_8_multiplied_lot_sequence__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PoJB3hjqER7KJDeo69pfX3ttV5DPaQPEf4pZEwhNYjTjqMdvif5qfE34S" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1LoMVBxYZuzZZfTckU3JRccwFCMJYP3WRg\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__example_9_multiplied__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PnUht3dP5Jdcp1B7NGqkEoBw5Ja2wWEeQMDRHqLNrBG4Rqo59eVfMd98B" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1DeDt7odeJqJvquJ6obEZfH1hfJHMvnURa\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__example_10_multiplied_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "6PfM4jsmgX1veYaiBXqqDe3J8hFtAriohdNGjPfrbt7aQ8H53nijYN6svW" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1MydksvfdWNXM1KnVTS8A78M4b78aJcL1W\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__example_11_multiplied_testnet__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "8FEMBzS4QWPwxyzrYJxHwzSrdNzroFiQjkAnpf51xcPPXkTvqGrD8bVq68" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("mtABBAtcTLGZhxNupNZcPaVLZetzHVWgAp\n");
}

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__example_12_multiplied_litecoin_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_to_address);
    command.set_ek_private_key_argument({ "7C8LFBdEAqptMNYUNr2cgcP7bppVgsqtz1fXVeSzAPf8VkB29XMKDtF71p" });
    command.set_passphrase_argument("my passphrase");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("LgCb26EViAcabp1wfbRRS8C7GoUQffafGp\n");
}

#else // WITH_ICU

BOOST_AUTO_TEST_CASE(ek_to_address__invoke__not_icu__failure_error)
{
    BX_DECLARE_COMMAND(ek_to_address);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EK_TO_ADDRESS_REQUIRES_ICU "\n");
}

#endif // !WITH_ICU

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
