/*
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include <iostream>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <sx/sx.hpp>
#include "command.hpp"

SX_USING_NAMESPACES()

// This is a namespace for tests by class/file__method/function.
BOOST_AUTO_TEST_SUITE(stealth_addr__invoke)

BOOST_AUTO_TEST_CASE(stealth_addr__invoke__scan_pubkey__okay_output)
{
    // $ sx stealth-addr 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(stealth_addr);
    command.set_scan_pubkey_argument(bytes("031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006"));
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("hf2YiTUPjjFRvDw98ksxEgU7s8o8aDYsKuehLL68FsmnoQnU8ys8T1tX7\n");
}

BOOST_AUTO_TEST_CASE(stealth_addr__invoke__scan_pubkey_bogus_input__okay_output)
{
    // $ echo bogus | sx stealth-addr 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND_INPUT(stealth_addr, "bogus");
    command.set_scan_pubkey_argument(bytes("031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006"));
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("hf2YiTUPjjFRvDw98ksxEgU7s8o8aDYsKuehLL68FsmnoQnU8ys8T1tX7\n");
}

BOOST_AUTO_TEST_CASE(stealth_addr__invoke__scan_pubkey_signatures_four__okay_output)
{
    // $ sx stealth-addr -s 4 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(stealth_addr);
    command.set_signatures_option(4);
    command.set_scan_pubkey_argument(bytes("031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006"));
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("hf2YiTUPjjFRvDw98ksxEgU7s8o8aDYsKuehLL68FsmnoQnU91raMWbWq\n");
}

BOOST_AUTO_TEST_CASE(stealth_addr__invoke__scan_pubkey_reuse_key__okay_output)
{
    // $ sx stealth-addr -r 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(stealth_addr);
    command.set_reuse_key_option(true);
    command.set_scan_pubkey_argument(bytes("031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006"));
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i\n");
}

BOOST_AUTO_TEST_CASE(stealth_addr__invoke__scan_pubkey_reuse_key_signatures__okay_output)
{
    // $ sx stealth-addr -r -s 4 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(stealth_addr);
    command.set_reuse_key_option(true);
    command.set_signatures_option(4);
    command.set_scan_pubkey_argument(bytes("031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006"));
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7exZGU8BmV\n");
}

// sx.dyne.org/stealth.html#further-understanding
BOOST_AUTO_TEST_CASE(stealth_addr__invoke__scan_pubkey_one_spend_pubkeys__okay_output)
{
    // $ sx stealth-addr 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969
    SX_DECLARE_COMMAND(stealth_addr);
    command.set_scan_pubkey_argument(bytes("031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006"));
    command.set_spend_pubkeys_argument({ bytes("024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969") });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("vJmwY32eS5VDC2C4GaZyXt7i4iCjzSMZ1XSd6KbkA7QbGE492akT2eZZMjCwWDqKRSYhnSA8Bgp78KeAYFVCi8ke5mELdoYMBNep7L\n");
}

BOOST_AUTO_TEST_SUITE_END()