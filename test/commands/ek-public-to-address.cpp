/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(ek_public_to_address__invoke)

#ifdef WITH_ICU

// BIP-38 Vectors

BOOST_AUTO_TEST_CASE(ek_public_to_address__invoke__vector_6_uncompressed_multiplied__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_address);
    command.set_ek_public_key_argument({ "cfrm38V8aXBn7JWA1ESmFMUn6erxeBGZGAxJPY4e36S9QWkzZKtaVqLNMgnifETYw7BPwWC9aPD" });
    command.set_passphrase_argument({ "MOLON LABE" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1Jscj8ALrYu2y9TD8NrpvDBugPedmbj4Yh\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_address__invoke__vector_7_uncompressed_multiplied__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_address);
    command.set_ek_public_key_argument({ "cfrm38V8G4qq2ywYEFfWLD5Cc6msj9UwsG2Mj4Z6QdGJAFQpdatZLavkgRd1i4iBMdRngDqDs51" });
    command.set_passphrase_argument("ΜΟΛΩΝ ΛΑΒΕ");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1Lurmih3KruL4xDB5FmHof38yawNtP9oGf\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_address__invoke__vector_8_uncompressed_multiplied__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_address);
    command.set_ek_public_key_argument({ "cfrm38V5Nm1mn7GxPBAGTXawqXRwE1EbR19GqsvJ9JmF5VKLqi8nETmULpELkQvExCGkTNCH2An" });
    command.set_passphrase_argument("libbitcoin test");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1NQgLnFz1ZzF6KkCJ4SM3xz3Jy1q2hEEax\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_address__invoke__vector_9_uncompressed_multiplied__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_address);
    command.set_ek_public_key_argument({ "cfrm38V5ec4E5RKwBu46Jf5zfaE54nuB1NWHpHSpgX4GQqfzx7fvqm43mBHvr89pPgykDHts9VC" });
    command.set_passphrase_argument("Libbitcoin BIP38 Test Vector");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1NjjvGqXDrx1DvrhjYJxzrpyopk1ygHTSJ\n");
}

// Wiki Examples

BOOST_AUTO_TEST_CASE(ek_public_to_address__invoke__example_1_lot_sequence__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_address);
    command.set_passphrase_argument({ "my passphrase" });
    command.set_ek_public_key_argument({ "cfrm38VXASNzNjsak8pLc3ZtyPnBNDxAAbB18KMMCSjf8ZhW3FVTeuw2r9J3tyAUNyhfM7VMZuP" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1LoMVBxYZuzZZfTckU3JRccwFCMJYP3WRg\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_address__invoke__example_2__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_address);
    command.set_passphrase_argument({ "my passphrase" });
    command.set_ek_public_key_argument({ "cfrm38VUVm4ZGXku7wWGiLfAJNoeDHConFb9CugfTnR1SQC1jf3uwyKULmCMk4SUhsXasMyPcA9" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1DeDt7odeJqJvquJ6obEZfH1hfJHMvnURa\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_address__invoke__example_3_piped_commands__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_address);
    command.set_passphrase_argument({ "my passphrase" });
    command.set_ek_public_key_argument({ "cfrm38VURwDvZXxV2AfWnHe6GwDxSG4FkrK4en7VdaxLPMxMnU8BaLneNVAwf19TAkbmAptNNaH" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1DS3aqzg5w8bMsyzyutxcrhKoLZGjPnC13\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_address__invoke__example_4_incorrect_passphrase__failure_error)
{
    BX_DECLARE_COMMAND(ek_public_to_address);
    command.set_passphrase_argument("i forgot");
    command.set_ek_public_key_argument({ "cfrm38VURwDvZXxV2AfWnHe6GwDxSG4FkrK4en7VdaxLPMxMnU8BaLneNVAwf19TAkbmAptNNaH" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EK_PUBLIC_TO_ADDRESS_INVALID_PASSPHRASE "\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_address__invoke__example_5_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_address);
    command.set_passphrase_argument({ "my passphrase" });
    command.set_ek_public_key_argument({ "cfrm38V5FtqpFoBNE9wpKjp5Fe97tM7YX6brNPCjpb9uLiqENKfeHHUKLd2VrvQhuHVUwgNVaSt" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1MydksvfdWNXM1KnVTS8A78M4b78aJcL1W\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_address__invoke__example_6_testnet__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_address);
    command.set_passphrase_argument({ "my passphrase" });
    command.set_ek_public_key_argument({ "cfrm2zc7BCp4KwhEE6HzSSxVhUyj2ky8bzvSLEqmAPcakQXb49uFQ87UEg8EhbuwA33t8db2fYW" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("mtABBAtcTLGZhxNupNZcPaVLZetzHVWgAp\n");
}

BOOST_AUTO_TEST_CASE(ek_public_to_address__invoke__example_7_testnet_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_public_to_address);
    command.set_passphrase_argument({ "my passphrase" });
    command.set_ek_public_key_argument({ "cfrm2zbi4iuQJ7cY69uJZsxhYLk4wLY7UWQiZ1wH5b3pEnzczSH3GHY3hAyV5AiWmU7mpk2Bqqc" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("n2Vb3w1eSXon87oQD2QVz2LfvahqVhBXKV\n");
}

#else // WITH_ICU

BOOST_AUTO_TEST_CASE(ek_public_to_address__invoke__not_icu__failure_error)
{
    BX_DECLARE_COMMAND(ek_to_ec);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EK_PUBLIC_TO_ADDRESS_REQUIRES_ICU "\n");
}

#endif // !WITH_ICU

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
