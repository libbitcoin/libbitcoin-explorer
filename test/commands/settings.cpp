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
BC_AUTO_TEST_SUITE(settings__invoke)

#define BX_SETTINGS_EMPTY "\nThese are the configuration settings that can be set.\n\n[server]\n# The number of times to retry contacting a server, defaults to 0.\nconnect_retries = 0\n# The time limit for connection establishment, defaults to 5.\nconnect_timeout_seconds = 0\n# The URL of the Libbitcoin server native interface.\nurl = localhost\n\n[wallet]\n# The hierarchical deterministic (HD) public key version, defaults to 76067358.\nhd_public_version = 0\n# The hierarchical deterministic (HD) private key version, defaults to 76066276.\nhd_secret_version = 0\n# The pay-to-public-key-hash address version, defaults to 0.\npay_to_public_key_hash_version = 0\n# The pay-to-script-hash address version, defaults to 5.\npay_to_script_hash_version = 0\n# The rule fork flags, defaults to all (4294967295).\nrule_fork_flags = 0\n# The transaction version, defaults to 1.\ntransaction_version = 0\n# The wallet import format (WIF) key version, defaults to 128.\nwif_version = 0\n# The witness address prefix, defaults to 'bc'.\nwitness_address_prefix =\n# The witness version, defaults to 0.\nwitness_version = 0\n"

#define BX_SETTINGS_TEST_VALUES "\nThese are the configuration settings that can be set.\n\n[server]\n# The number of times to retry contacting a server, defaults to 0.\nconnect_retries = 21\n# The time limit for connection establishment, defaults to 5.\nconnect_timeout_seconds = 22\n# The URL of the Libbitcoin server native interface.\nurl = https://mainnet.obelisk.net:42\n\n[wallet]\n# The hierarchical deterministic (HD) public key version, defaults to 76067358.\nhd_public_version = 2\n# The hierarchical deterministic (HD) private key version, defaults to 76066276.\nhd_secret_version = 3\n# The pay-to-public-key-hash address version, defaults to 0.\npay_to_public_key_hash_version = 4\n# The pay-to-script-hash address version, defaults to 5.\npay_to_script_hash_version = 5\n# The rule fork flags, defaults to all (4294967295).\nrule_fork_flags = 4294967295\n# The transaction version, defaults to 1.\ntransaction_version = 6\n# The wallet import format (WIF) key version, defaults to 128.\nwif_version = 1\n# The witness address prefix, defaults to 'bc'.\nwitness_address_prefix = tb\n# The witness version, defaults to 0.\nwitness_version = 7\n"

BC_AUTO_TEST_CASE(settings__invoke__empty__okay_output)
{
    BX_DECLARE_COMMAND(commands::settings);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SETTINGS_EMPTY);
}

BC_AUTO_TEST_CASE(settings__invoke__test_values__okay_output)
{
    BX_DECLARE_COMMAND(commands::settings);
    command.set_wallet_witness_version_setting(7);
    command.set_wallet_witness_address_prefix_setting("tb");
    command.set_wallet_wif_version_setting(1);
    command.set_wallet_hd_public_version_setting(2);
    command.set_wallet_hd_secret_version_setting(3);
    command.set_wallet_pay_to_public_key_hash_version_setting(4);
    command.set_wallet_pay_to_script_hash_version_setting(5);
    command.set_wallet_rule_fork_flags_setting(4294967295);
    command.set_wallet_transaction_version_setting(6);
    command.set_server_url_setting({ "https://mainnet.obelisk.net:42" });
    command.set_server_connect_retries_setting(21);
    command.set_server_connect_timeout_seconds_setting(22);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SETTINGS_TEST_VALUES);
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
