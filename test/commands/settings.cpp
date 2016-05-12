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
"    network\n" \
"    {\n" \
"        channel_handshake_seconds 0\n" \
"        connect_retries 0\n" \
"        connect_timeout_seconds 0\n" \
"        debug_file \"\"\n" \
"        error_file \"\"\n" \
"        hosts_file \"\"\n" \
"        identifier 0\n" \
"        seeds seed.bitchannels.io:8333,seed.bitcoinstats.com:8333,seed.bitcoin.sipa.be:8333,dnsseed.bluematt.me:8333,seed.bitcoin.jonasschnelli.ch:8333,dnsseed.bitcoin.dashjr.org:8333\n" \
"    }\n" \
"    server\n" \
"    {\n" \
"        client_certificate_file \"\"\n" \
"        connect_retries 0\n" \
"        connect_timeout_seconds 0\n" \
"        server_certificate_key \"\"\n" \
"        url localhost\n" \
"    }\n" \
"    wallet\n" \
"    {\n" \
"        hd_public_version 0\n" \
"        hd_secret_version 0\n" \
"        pay_to_public_key_hash_version 0\n" \
"        pay_to_script_hash_version 0\n" \
"        transaction_version 0\n" \
"        wif_version 0\n" \
"    }\n" \
"}\n"

#define BX_SETTINGS_TEST_VALUES \
"settings\n" \
"{\n" \
"    network\n" \
"    {\n" \
"        channel_handshake_seconds 13\n" \
"        connect_retries 11\n" \
"        connect_timeout_seconds 12\n" \
"        debug_file debug.log\n" \
"        error_file error.log\n" \
"        hosts_file my.hosts\n" \
"        identifier 10\n" \
"        seeds seed1.libbitcoin.org:8333,seed2.libbitcoin.org:8333\n" \
"    }\n" \
"    server\n" \
"    {\n" \
"        client_certificate_file mainnet.certificate.zpl\n" \
"        connect_retries 21\n" \
"        connect_timeout_seconds 22\n" \
"        server_certificate_key \"CrWu}il)+MbqD60BV)v/xt&Xtwj*$[Q}Q{$9}hom\"\n" \
"        url https://mainnet.obelisk.net:42\n" \
"    }\n" \
"    wallet\n" \
"    {\n" \
"        hd_public_version 2\n" \
"        hd_secret_version 3\n" \
"        pay_to_public_key_hash_version 4\n" \
"        pay_to_script_hash_version 5\n" \
"        transaction_version 6\n" \
"        wif_version 1\n" \
"    }\n" \
"}\n"

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
    command.set_wallet_transaction_version_setting(6);
    command.set_network_identifier_setting(10);
    command.set_network_connect_retries_setting(11);
    command.set_network_connect_timeout_seconds_setting(12);
    command.set_network_channel_handshake_seconds_setting(13);
    command.set_network_hosts_file_setting("my.hosts");
    command.set_network_debug_file_setting("debug.log");
    command.set_network_error_file_setting("error.log");
    command.set_network_seeds_setting({ { "seed1.libbitcoin.org:8333" }, { "seed2.libbitcoin.org:8333" } });
    command.set_server_url_setting({ "https://mainnet.obelisk.net:42" });
    command.set_server_connect_retries_setting(21);
    command.set_server_connect_timeout_seconds_setting(22);
    command.set_server_server_certificate_key_setting({ "CrWu}il)+MbqD60BV)v/xt&Xtwj*$[Q}Q{$9}hom" });
    command.set_server_client_certificate_file_setting("mainnet.certificate.zpl");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SETTINGS_TEST_VALUES);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
