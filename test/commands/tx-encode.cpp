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
BOOST_AUTO_TEST_SUITE(tx_encode__invoke)

BOOST_AUTO_TEST_CASE(tx_encode__invoke__locktime_conflict__locktime_conflict_error)
{
    BX_DECLARE_COMMAND(tx_encode);
    command.set_version_option(1);
    command.set_lock_time_option(42);
    command.set_script_version_option(5);
    command.set_inputs_option({ { "97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1" } });
    command.set_outputs_option({ { "13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe:90000" } });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TX_ENCODE_LOCKTIME_CONFLICT "\n");
}

BOOST_AUTO_TEST_CASE(tx_encode__invoke__example1__expected_output)
{
    BX_DECLARE_COMMAND(tx_encode);
    command.set_version_option(1);
    command.set_script_version_option(5);
    command.set_inputs_option({ { "97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:0" } });
    command.set_outputs_option({ { "1966U1pjj15tLxPXZ19U48c99EJDkdXeqb:45000" } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970000000000ffffffff01c8af0000000000001976a91458b7a60f11a904feef35a639b6048de8dd4d9f1c88ac00000000" "\n");
}

// Vector: from stealth-encode tests.
BOOST_AUTO_TEST_CASE(tx_encode__invoke__example2__okay_output)
{
    BX_DECLARE_COMMAND(tx_encode);
    command.set_version_option(1);
    command.set_script_version_option(5);
    command.set_inputs_option({ { "97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1:7" } });
    command.set_outputs_option({ { "hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i:42:baadf00dbaadf00dbaadf00dbaadf00d" } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000070000000200000000000000003a6a3814576f496f20b0befe21f39f765e81543ebd1790ec4a03d1b5a1c2e912749d90d0fd7b16322749e301a2b0dbfe278509011564590412b2772a000000000000001976a914cc04492c12d0ddeb4cf88cfccb0d6d78d0fcd39d88ac00000000" "\n");
}

// Vector: script from script-decode
BOOST_AUTO_TEST_CASE(tx_encode__invoke__example3__okay_output)
{
    BX_DECLARE_COMMAND(tx_encode);
    command.set_version_option(1);
    command.set_script_version_option(5);
    command.set_inputs_option({ { "97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1:7" } });
    command.set_outputs_option({ { "76a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac:500" } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee09701000000000700000001f4010000000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000" "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
