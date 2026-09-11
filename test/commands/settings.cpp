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

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(settings__invoke)

#define BX_SETTINGS_EMPTY "{\"settings\":{\"server\":{\"block_url\":\"localhost\",\"connect_retries\":\"0\",\"connect_timeout_seconds\":\"0\",\"socks_proxy\":\"[::]\",\"transaction_url\":\"localhost\",\"url\":\"localhost\"},\"wallet\":{\"hd_public_version\":\"0\",\"hd_secret_version\":\"0\",\"pay_to_public_key_hash_version\":\"0\",\"pay_to_script_hash_version\":\"0\",\"rule_fork_flags\":\"0\",\"transaction_version\":\"0\",\"wif_version\":\"0\"}}}\n"

#define BX_SETTINGS_TEST_VALUES "{\"settings\":{\"server\":{\"block_url\":\"https://mainnet.obelisk.net:43\",\"connect_retries\":\"21\",\"connect_timeout_seconds\":\"22\",\"socks_proxy\":\"127.0.0.42:4242\",\"transaction_url\":\"https://mainnet.obelisk.net:44\",\"url\":\"https://mainnet.obelisk.net:42\"},\"wallet\":{\"hd_public_version\":\"2\",\"hd_secret_version\":\"3\",\"pay_to_public_key_hash_version\":\"4\",\"pay_to_script_hash_version\":\"5\",\"rule_fork_flags\":\"4294967295\",\"transaction_version\":\"6\",\"wif_version\":\"1\"}}}\n"

BOOST_AUTO_TEST_CASE(settings__invoke__empty__okay_output)
{
    BX_DECLARE_COMMAND(commands::settings);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SETTINGS_EMPTY);
}

BOOST_AUTO_TEST_CASE(settings__invoke__test_values__okay_output)
{
    BX_DECLARE_COMMAND(commands::settings);
    command.set_wallet_wif_version_setting(1);
    command.set_wallet_hd_public_version_setting(2);
    command.set_wallet_hd_secret_version_setting(3);
    command.set_wallet_pay_to_public_key_hash_version_setting(4);
    command.set_wallet_pay_to_script_hash_version_setting(5);
    command.set_wallet_rule_fork_flags_setting(4294967295);
    command.set_wallet_transaction_version_setting(6);
    command.set_server_url_setting({ "https://mainnet.obelisk.net:42" });
    command.set_server_block_url_setting({ "https://mainnet.obelisk.net:43" });
    command.set_server_transaction_url_setting({ "https://mainnet.obelisk.net:44" });
    command.set_server_socks_proxy_setting({ "127.0.0.42:4242" });
    command.set_server_connect_retries_setting(21);
    command.set_server_connect_timeout_seconds_setting(22);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SETTINGS_TEST_VALUES);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
