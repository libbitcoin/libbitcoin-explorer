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
#include "precompile.hpp"
#include "command.hpp"

SX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(stealth_addr_encode__invoke)

// mainnet

BOOST_AUTO_TEST_CASE(stealth_addr_encode__invoke__scan_key_mainnet__okay_output)
{
    // $ sx stealth-addr-encode 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(stealth_addr_encode);
    command.set_scan_key_argument({ "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("hf2YiTUPjjFRvDw98ksxEgU7s8o8aDYsKuehLL68FsmnoQnU8ys8T1tX7\n");
}

BOOST_AUTO_TEST_CASE(stealth_addr_encode__invoke__scan_key_signatures_four_mainnet__okay_output)
{
    // $ sx stealth-addr-encode -s 4 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(stealth_addr_encode);
    command.set_signatures_option(4);
    command.set_scan_key_argument({ "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("hf2YiTUPjjFRvDw98ksxEgU7s8o8aDYsKuehLL68FsmnoQnU91raMWbWq\n");
}

BOOST_AUTO_TEST_CASE(stealth_addr_encode__invoke__scan_key_reuse_key_mainnet__okay_output)
{
    // $ sx stealth-addr-encode -r true 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(stealth_addr_encode);
    command.set_reuse_key_option(true);
    command.set_scan_key_argument({ "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i\n");
}

BOOST_AUTO_TEST_CASE(stealth_addr_encode__invoke__scan_key_reuse_key_signatures_mainnet__okay_output)
{
    // $ sx stealth-addr-encode -r true -s 4 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(stealth_addr_encode);
    command.set_reuse_key_option(true);
    command.set_signatures_option(4);
    command.set_scan_key_argument({ "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7exZGU8BmV\n");
}

// sx.dyne.org/stealth.html#further-understanding
BOOST_AUTO_TEST_CASE(stealth_addr_encode__invoke__scan_key_one_spend_keys_mainnet__okay_output)
{
    // $ sx stealth-addr-encode 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969
    SX_DECLARE_COMMAND(stealth_addr_encode);
    command.set_scan_key_argument({ "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    command.set_spend_keys_argument({{ "024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969" }});
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("vJmwY32eS5VDC2C4GaZyXt7i4iCjzSMZ1XSd6KbkA7QbGE492akT2eZZMjCwWDqKRSYhnSA8Bgp78KeAYFVCi8ke5mELdoYMBNep7L\n");
}

// testnet

BOOST_AUTO_TEST_CASE(stealth_addr_encode__invoke__scan_key_testnet__okay_output)
{
    // $ sx stealth-addr-encode 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(stealth_addr_encode);
    command.set_general_testnet_setting(true);
    command.set_scan_key_argument({ "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("idAsD84ZtoQdgfgDVmSitbYsJjrfUH4hB8j1ZMLvu2SeaLY4GDbAWrz9f\n");
}

BOOST_AUTO_TEST_CASE(stealth_addr_encode__invoke__scan_key_signatures_four_testnet__okay_output)
{
    // $ sx stealth-addr-encode -s 4 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(stealth_addr_encode);
    command.set_general_testnet_setting(true);
    command.set_signatures_option(4);
    command.set_scan_key_argument({ "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("idAsD84ZtoQdgfgDVmSitbYsJjrfUH4hB8j1ZMLvu2SeaLY4GFaiRf1u2\n");
}

BOOST_AUTO_TEST_CASE(stealth_addr_encode__invoke__scan_key_reuse_key_testnet__okay_output)
{
    // $ sx stealth-addr-encode -r true 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(stealth_addr_encode);
    command.set_general_testnet_setting(true);
    command.set_reuse_key_option(true);
    command.set_scan_key_argument({ "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("idPayBqZUpZH7Y5GTaoEyGxDsEmU377JUmhtqG8yoHCkfGfhnAHmGUJbL\n");
}

BOOST_AUTO_TEST_CASE(stealth_addr_encode__invoke__scan_key_reuse_key_signatures_testnet__okay_output)
{
    // $ sx stealth-addr-encode -r true -s 4 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    SX_DECLARE_COMMAND(stealth_addr_encode);
    command.set_general_testnet_setting(true);
    command.set_reuse_key_option(true);
    command.set_signatures_option(4);
    command.set_scan_key_argument({ "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("idPayBqZUpZH7Y5GTaoEyGxDsEmU377JUmhtqG8yoHCkfGfhnCHERr48Q\n");
}

// sx.dyne.org/stealth.html#further-understanding
BOOST_AUTO_TEST_CASE(stealth_addr_encode__invoke__scan_key_one_spend_keys_testnet__okay_output)
{
    // $ sx stealth-addr-encode 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969
    SX_DECLARE_COMMAND(stealth_addr_encode);
    command.set_general_testnet_setting(true);
    command.set_scan_key_argument({ "031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006" });
    command.set_spend_keys_argument({ { "024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969" } });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("waPXhQwQE9tDugfgLkvpDs3dnkPx1RsfDjFt4zBq7EeWeATRHpyQpYrFZR8T4BQy91Vpvshm2TDER8b9ZryuZ8VSzz8ywzNzX8NqF4\n");
}

BOOST_AUTO_TEST_SUITE_END()