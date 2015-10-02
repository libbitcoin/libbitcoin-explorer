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
BOOST_AUTO_TEST_SUITE(tx_encode__invoke)

// Vector: from script-decode
#define TX_ENCODE_OUTPUT_SCRIPT "76a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac:500"
#define TX_ENCODE_TX_SCRIPT "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee09701000000000700000001f4010000000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"

// Vector: sx.dyne.org/offlinetx.html
#define TX_ENCODE_INPUT_A "97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1:7"
#define TX_ENCODE_INPUT_B "97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1"
#define TX_ENCODE_PAYMENT_ADDRESS_OUTPUT "13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe:90000"
#define TX_ENCODE_TX_BV1_BASE16 "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff0000000000"
#define TX_ENCODE_TX_BCV1_BASE16 "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"
#define TX_ENCODE_TX_BCV42_BASE16 "2a00000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"
#define TX_ENCODE_TX_ACV1L42_BASE16 "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee09701000000000700000001905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac2a000000"

// Vector: from stealth-encode tests.
#define TX_ENCODE_SEED "baadf00dbaadf00dbaadf00dbaadf00d"
#define TX_ENCODE_STEALTH_ADDRESS_A "hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i"
#define TX_ENCODE_STEALTH_OUTPUT_A TX_ENCODE_STEALTH_ADDRESS_A ":42:" TX_ENCODE_SEED
#define TX_ENCODE_TX_STEALTH_A "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000070000000200000000000000003a6a3814576f496f20b0befe21f39f765e81543ebd1790ec4a03d1b5a1c2e912749d90d0fd7b16322749e301a2b0dbfe27850901156459000000002a000000000000001976a914cc04492c12d0ddeb4cf88cfccb0d6d78d0fcd39d88ac00000000"

BOOST_AUTO_TEST_SUITE(tx_encode__invoke__no_output)

BOOST_AUTO_TEST_CASE(tx_encode__invoke__one_input_no_output_version_1__okay_output)
{
    BX_DECLARE_COMMAND(tx_encode);
    command.set_version_option(1);
    command.set_script_version_option(5);
    command.set_inputs_option({ { TX_ENCODE_INPUT_B } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_ENCODE_TX_BV1_BASE16 "\n");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(tx_encode__invoke__script_output)

BOOST_AUTO_TEST_CASE(tx_encode__invoke__one_input_script_output_version_1__okay_output)
{
    BX_DECLARE_COMMAND(tx_encode);
    command.set_version_option(1);
    command.set_script_version_option(43);
    command.set_inputs_option({ { TX_ENCODE_INPUT_A } });
    command.set_outputs_option({ { TX_ENCODE_OUTPUT_SCRIPT } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_ENCODE_TX_SCRIPT "\n");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(tx_encode__invoke__payment_address_output)

BOOST_AUTO_TEST_CASE(tx_encode__invoke__one_input_payment_address_output_version_1__okay_output)
{
    BX_DECLARE_COMMAND(tx_encode);
    command.set_version_option(1);
    command.set_script_version_option(5);
    command.set_inputs_option({ { TX_ENCODE_INPUT_B } });
    command.set_outputs_option({ { TX_ENCODE_PAYMENT_ADDRESS_OUTPUT } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_ENCODE_TX_BCV1_BASE16 "\n");
}

BOOST_AUTO_TEST_CASE(tx_encode__invoke__one_input_payment_address__output_version_42__okay_output)
{
    BX_DECLARE_COMMAND(tx_encode);
    command.set_version_option(42);
    command.set_script_version_option(5);
    command.set_inputs_option({ { TX_ENCODE_INPUT_B } });
    command.set_outputs_option({ { TX_ENCODE_PAYMENT_ADDRESS_OUTPUT } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_ENCODE_TX_BCV42_BASE16 "\n");
}

BOOST_AUTO_TEST_CASE(tx_encode__invoke__one_input_payment_address__output_version_1_locktime_42__failure_error)
{
    BX_DECLARE_COMMAND(tx_encode);
    command.set_version_option(1);
    command.set_script_version_option(5);
    command.set_lock_time_option(42);
    command.set_inputs_option({ { TX_ENCODE_INPUT_B } });
    command.set_outputs_option({ { TX_ENCODE_PAYMENT_ADDRESS_OUTPUT } });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TX_ENCODE_LOCKTIME_CONFLICT "\n");
}

BOOST_AUTO_TEST_CASE(tx_encode__invoke__one_input_payment_address__output_version_1_locktime_42_sequence_7__okay_output)
{
    BX_DECLARE_COMMAND(tx_encode);
    command.set_version_option(1);
    command.set_script_version_option(5);
    command.set_lock_time_option(42);
    command.set_inputs_option({ { TX_ENCODE_INPUT_A } });
    command.set_outputs_option({ { TX_ENCODE_PAYMENT_ADDRESS_OUTPUT } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_ENCODE_TX_ACV1L42_BASE16 "\n");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(tx_encode__invoke__stealth_address_output)

// TODO: add prefix test

BOOST_AUTO_TEST_CASE(tx_encode__invoke__one_input_stealth_output_no_filter_version_1__okay_output)
{
    BX_DECLARE_COMMAND(tx_encode);
    command.set_version_option(1);
    command.set_script_version_option(43);
    command.set_inputs_option({ { TX_ENCODE_INPUT_A } });
    command.set_outputs_option({ { TX_ENCODE_STEALTH_OUTPUT_A } });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TX_ENCODE_TX_STEALTH_A "\n");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
