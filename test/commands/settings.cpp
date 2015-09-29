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
BOOST_AUTO_TEST_SUITE(settings__invoke)

#define BX_SETTINGS_EMPTY \
"settings\n" \
"{\n" \
"    general\n" \
"    {\n" \
"        channel_handshake_seconds 0\n" \
"        connect_retries 0\n" \
"        connect_timeout_seconds 0\n" \
"        hosts_file \"\"\n" \
"        network \"\"\n" \
"    }\n" \
"    logging\n" \
"    {\n" \
"        debug_file \"\"\n" \
"        error_file \"\"\n" \
"    }\n" \
"    mainnet\n" \
"    {\n" \
"        cert_file \"\"\n" \
"        server_cert_key \"\"\n" \
"        url localhost\n" \
"    }\n" \
"    testnet\n" \
"    {\n" \
"        cert_file \"\"\n" \
"        server_cert_key \"\"\n" \
"        url localhost\n" \
"    }\n" \
"}\n"

#define BX_SETTINGS_TEST_VALUES \
"settings\n" \
"{\n" \
"    general\n" \
"    {\n" \
"        channel_handshake_seconds 9\n" \
"        connect_retries 42\n" \
"        connect_timeout_seconds 7\n" \
"        hosts_file my.hosts\n" \
"        network testnet\n" \
"    }\n" \
"    logging\n" \
"    {\n" \
"        debug_file debug.log\n" \
"        error_file error.log\n" \
"    }\n" \
"    mainnet\n" \
"    {\n" \
"        cert_file mainnet.certificate.zpl\n" \
"        server_cert_key \"CrWu}il)+MbqD60BV)v/xt&Xtwj*$[Q}Q{$9}hom\"\n" \
"        url https://mainnet.obelisk.net:42\n" \
"    }\n" \
"    testnet\n" \
"    {\n" \
"        cert_file testnet.certificate.zpl\n" \
"        server_cert_key \"DrWu}il)+MbqD60BV)v/xt&Xtwj*$[Q}Q{$9}hom\"\n" \
"        url https://testnet.obelisk.net:42\n" \
"    }\n" \
"}\n"

BOOST_AUTO_TEST_CASE(settings__invoke__empty__okay_output)
{
    BX_DECLARE_COMMAND(settings);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SETTINGS_EMPTY);
}

BOOST_AUTO_TEST_CASE(settings__invoke__test_values__okay_output)
{
    BX_DECLARE_COMMAND(settings);
    command.set_general_channel_handshake_seconds_setting(9);
    command.set_general_connect_retries_setting(42);
    command.set_general_connect_timeout_seconds_setting(7);
    command.set_general_network_setting("testnet");
    command.set_general_hosts_file_setting("my.hosts");
    command.set_mainnet_url_setting({ "https://mainnet.obelisk.net:42" });
    command.set_mainnet_cert_file_setting("mainnet.certificate.zpl");
    command.set_mainnet_server_cert_key_setting({ "CrWu}il)+MbqD60BV)v/xt&Xtwj*$[Q}Q{$9}hom" });
    command.set_testnet_url_setting({ "https://testnet.obelisk.net:42" });
    command.set_testnet_cert_file_setting("testnet.certificate.zpl");
    command.set_testnet_server_cert_key_setting({ "DrWu}il)+MbqD60BV)v/xt&Xtwj*$[Q}Q{$9}hom" });
    command.set_logging_debug_file_setting("debug.log");
    command.set_logging_error_file_setting("error.log");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SETTINGS_TEST_VALUES);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
