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
BC_AUTO_TEST_SUITE(tls_new__invoke)

#define TLS_NEW_KEY "-----BEGIN PRIVATE KEY-----\nMIGTAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBHkwdwIBAQQgXasIfmJKikt54X+L\ng4AO5m87sSkmGLb9HC+LJ/+I4OugCgYIKoZIzj0DAQehRANCAARI+NtMTx129/9E\nW4QLyhGU1Tx7uhrkZq2qLFks2349vOVTGxcu/SxtCaZI+8lKIIzOsbcZ4nYbU3Ot\nCKV047vP\n-----END PRIVATE KEY-----\n"

BC_AUTO_TEST_CASE(tls_new__invoke__256_bit_entropy__okay_output)
{
    BX_DECLARE_COMMAND(tls_new);
    command.set_entropy_argument({ "5dab087e624a8a4b79e17f8b83800ee66f3bb1292618b6fd1c2f8b27ff88e0eb" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TLS_NEW_KEY);
}

BC_AUTO_TEST_CASE(tls_new__invoke__excess_entropy__okay_first_256_bits)
{
    BX_DECLARE_COMMAND(tls_new);
    command.set_entropy_argument({ "5dab087e624a8a4b79e17f8b83800ee66f3bb1292618b6fd1c2f8b27ff88e0ebff" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TLS_NEW_KEY);
}

BC_AUTO_TEST_CASE(tls_new__invoke__128_bit_entropy__failure_error)
{
    BX_DECLARE_COMMAND(tls_new);
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TLS_NEW_SHORT_ENTROPY "\n");
}

BC_AUTO_TEST_CASE(tls_new__invoke__entropy_above_order__failure_error)
{
    BX_DECLARE_COMMAND(tls_new);
    command.set_entropy_argument({ "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TLS_NEW_INVALID_KEY "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
