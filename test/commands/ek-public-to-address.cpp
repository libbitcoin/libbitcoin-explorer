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
BOOST_AUTO_TEST_SUITE(ek_public_to_address__invoke)

#ifdef WITH_ICU

BOOST_AUTO_TEST_CASE(ek_public_to_address__invoke__bogus_passphrase__failure_error)
{
    BX_DECLARE_COMMAND(ek_public_to_address);
    command.set_ek_public_key_argument({ "cfrm38V8aXBn7JWA1ESmFMUn6erxeBGZGAxJPY4e36S9QWkzZKtaVqLNMgnifETYw7BPwWC9aPD" });
    command.set_passphrase_argument("bogus");
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EK_PUBLIC_TO_ADDRESS_INVALID_PASSPHRASE "\n");
}

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
