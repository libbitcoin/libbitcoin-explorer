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
BOOST_AUTO_TEST_SUITE(script_decode__invoke)

BOOST_AUTO_TEST_CASE(script_decode__invoke__basic__okay_output)
{
    BX_DECLARE_COMMAND(script_decode);
    command.set_base16_argument({ "76a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("dup hash160 [18c0bd8d1818f1bf99cb1df2269c645318ef7b73] equalverify checksig\n");
}

BOOST_AUTO_TEST_CASE(script_decode__invoke__data__okay_output)
{
    BX_DECLARE_COMMAND(script_decode);
    command.set_base16_argument({ "04cf2e5b02d6f02340f5a9defbbf710c388b8451c82145b1419fe9696837b1cdefc569a2a79baa6da2f747c3b25a102a081dfd5e799abc41262103e0d17114770b" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("[cf2e5b02] 0xd6 0xf0 [40f5a9defbbf710c388b8451c82145b1419fe9696837b1cdefc569a2a79baa6da2f747] 0xc3 nop3 10 [2a081dfd5e799abc41262103e0d17114] nip <invalid>\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
