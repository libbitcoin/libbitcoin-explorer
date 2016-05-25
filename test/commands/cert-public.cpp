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
BOOST_AUTO_TEST_SUITE(cert_public__invoke)

BOOST_AUTO_TEST_CASE(cert_public__invoke__valid_private_key1__success_output)
{
    BX_DECLARE_COMMAND(cert_public);
    command.set_private_key_argument({ "JTKVSB%%)wK0E.X)V>+}o?pNmC{O&4W4b!Ni{Lh6" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("rq:rM>}U?@Lns47E1%kR.o@n%FcmmsL/@{H8]yf7" "\n");
}

BOOST_AUTO_TEST_CASE(cert_public__invoke__valid_private_key2__success_output)
{
    BX_DECLARE_COMMAND(cert_public);
    command.set_private_key_argument({ "v=Y(Y-lrKbs[DwQ.Po.y*(5PQ]-!u*naPPVq8/15" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(")^^(VJ98$c[i?z%>R0=0?}>M/L)Tu/{g@yyFrcED" "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
