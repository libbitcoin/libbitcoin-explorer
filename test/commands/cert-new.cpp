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
BC_AUTO_TEST_SUITE(cert_new__invoke)

BC_AUTO_TEST_CASE(cert_new__invoke__256_bit_entropy__okay_output)
{
    BX_DECLARE_COMMAND(cert_new);
    command.set_entropy_argument({ "5dab087e624a8a4b79e17f8b83800ee66f3bb1292618b6fd1c2f8b27ff88e0eb" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("u8[lWvOhIJDeTmhGmBD]z-+iMck:h&950i$%a]R0\n");
}

BC_AUTO_TEST_CASE(cert_new__invoke__excess_entropy__okay_first_256_bits)
{
    BX_DECLARE_COMMAND(cert_new);
    command.set_entropy_argument({ "5dab087e624a8a4b79e17f8b83800ee66f3bb1292618b6fd1c2f8b27ff88e0ebff" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("u8[lWvOhIJDeTmhGmBD]z-+iMck:h&950i$%a]R0\n");
}

BC_AUTO_TEST_CASE(cert_new__invoke__128_bit_entropy__failure_error)
{
    BX_DECLARE_COMMAND(cert_new);
    command.set_entropy_argument({ "baadf00dbaadf00dbaadf00dbaadf00d" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_CERT_NEW_SHORT_ENTROPY "\n");
}

BC_AUTO_TEST_CASE(cert_new__invoke__hash_sign_encoding__failure_error)
{
    BX_DECLARE_COMMAND(cert_new);
    command.set_entropy_argument({ "77076d0a7318a57d3c16c17251b26645df4c2f87ebc0992ab177fba51db92c2a" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_CERT_NEW_INVALID_KEY "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
