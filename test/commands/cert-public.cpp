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
BC_AUTO_TEST_SUITE(cert_public__invoke)

BC_AUTO_TEST_CASE(cert_public__invoke__private_key__okay_output)
{
    BX_DECLARE_COMMAND(cert_public);
    command.set_private_key_argument({ "Cl.%(A#p:4jqL+Nql<!5?+kXU(+F]rV3l8w9L0ZJ" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("G=]<>I7>&bBC>O5V{aj/4zK}kco8}o(.HIuS*=:#\n");
}

BC_AUTO_TEST_CASE(cert_public__invoke__short_private_key__failure_error)
{
    BX_DECLARE_COMMAND(cert_public);
    command.set_private_key_argument({ "HelloWorld" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_CERT_PUBLIC_INVALID "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
