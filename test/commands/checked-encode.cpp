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
BC_AUTO_TEST_SUITE(checked_encode__invoke)

BC_AUTO_TEST_CASE(checked_encode__invoke__version_0__okay_output)
{
    BX_DECLARE_COMMAND(checked_encode);
    command.set_version_option(0);
    command.set_payload_argument({ "b472a266d0bd89c13706a4132ccfb16f7c3b9fcb" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("00b472a266d0bd89c13706a4132ccfb16f7c3b9fcb527686a3\n");
}

BC_AUTO_TEST_CASE(checked_encode__invoke__version_111__okay_output)
{
    BX_DECLARE_COMMAND(checked_encode);
    command.set_version_option(111);
    command.set_payload_argument({ "b472a266d0bd89c13706a4132ccfb16f7c3b9fcb" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6fb472a266d0bd89c13706a4132ccfb16f7c3b9fcb6192f257\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
