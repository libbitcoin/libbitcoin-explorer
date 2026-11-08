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
BC_AUTO_TEST_SUITE(tls_cert__invoke)

#define TLS_CERT_KEY "-----BEGIN PRIVATE KEY-----\nMIGTAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBHkwdwIBAQQgXasIfmJKikt54X+L\ng4AO5m87sSkmGLb9HC+LJ/+I4OugCgYIKoZIzj0DAQehRANCAARI+NtMTx129/9E\nW4QLyhGU1Tx7uhrkZq2qLFks2349vOVTGxcu/SxtCaZI+8lKIIzOsbcZ4nYbU3Ot\nCKV047vP\n-----END PRIVATE KEY-----\n"
#define TLS_CERT_NAMED "-----BEGIN CERTIFICATE-----\nMIIBezCCASGgAwIBAgIQIMsmoHr/GaAVbB238lJYpTAKBggqhkjOPQQDAjARMQ8w\nDQYDVQQDDAZzZXJ2ZXIwHhcNMjYwMTAxMDAwMDAwWhcNMjcwMTAxMDAwMDAwWjAR\nMQ8wDQYDVQQDDAZzZXJ2ZXIwWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAARI+NtM\nTx129/9EW4QLyhGU1Tx7uhrkZq2qLFks2349vOVTGxcu/SxtCaZI+8lKIIzOsbcZ\n4nYbU3OtCKV047vPo1swWTAMBgNVHRMBAf8EAjAAMA4GA1UdDwEB/wQEAwIHgDAd\nBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwGgYDVR0RBBMwEYIJbG9jYWxo\nb3N0hwR/AAABMAoGCCqGSM49BAMCA0gAMEUCIQCdIlgTwaRZhzfF+wovZ4hI1Pag\npS/YycHbpBi7X+Tk6QIgRa/ZClikC+VwzYMpRlPR/qn2Gll55+TckP4ecF7ECvA=\n-----END CERTIFICATE-----\n"
#define TLS_CERT_HOST_IPV6 "-----BEGIN CERTIFICATE-----\nMIIBejCCASGgAwIBAgIQIMsmoHr/GaAVbB238lJYpTAKBggqhkjOPQQDAjAAMB4X\nDTI2MDEwMTAwMDAwMFoXDTI2MDEzMTAwMDAwMFowADBZMBMGByqGSM49AgEGCCqG\nSM49AwEHA0IABEj420xPHXb3/0RbhAvKEZTVPHu6GuRmraosWSzbfj285VMbFy79\nLG0Jpkj7yUogjM6xtxnidhtTc60IpXTju8+jfTB7MAwGA1UdEwEB/wQCMAAwDgYD\nVR0PAQH/BAQDAgeAMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjA8BgNV\nHREBAf8EMjAwggtleGFtcGxlLmNvbYIPd3d3LmV4YW1wbGUuY29thxAAAAAAAAAA\nAAAAAAAAAAABMAoGCCqGSM49BAMCA0cAMEQCIHx17ewpLutVrSWwXkEVyrU9/FIE\n/Iac7L7vHDP0DtSdAiA9aQWCfuieyZ5vJsJbExzojxGMZvBaamMrNKOaL7NB8g==\n-----END CERTIFICATE-----\n"

BC_AUTO_TEST_CASE(tls_cert__invoke__name_host_ip__okay_output)
{
    BX_DECLARE_COMMAND(tls_cert);
    command.set_name_option({ "server" });
    command.set_hosts_option({ "localhost" });
    command.set_ips_option({ "127.0.0.1" });
    command.set_not_before_option(1767225600);
    command.set_days_option(365);
    command.set_private_key_argument({ TLS_CERT_KEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TLS_CERT_NAMED);
}

BC_AUTO_TEST_CASE(tls_cert__invoke__hosts_ipv6_unnamed__okay_output)
{
    BX_DECLARE_COMMAND(tls_cert);
    command.set_name_option({ "" });
    command.set_hosts_option({ "example.com", "www.example.com" });
    command.set_ips_option({ "::1" });
    command.set_not_before_option(1767225600);
    command.set_days_option(30);
    command.set_private_key_argument({ TLS_CERT_KEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(TLS_CERT_HOST_IPV6);
}

BC_AUTO_TEST_CASE(tls_cert__invoke__current_time__okay)
{
    BX_DECLARE_COMMAND(tls_cert);
    command.set_name_option({ "server" });
    command.set_hosts_option({});
    command.set_ips_option({});
    command.set_not_before_option(0);
    command.set_days_option(365);
    command.set_private_key_argument({ TLS_CERT_KEY });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BC_REQUIRE(output.str().starts_with("-----BEGIN CERTIFICATE-----\n"));
}

BC_AUTO_TEST_CASE(tls_cert__invoke__invalid_key__failure_error)
{
    BX_DECLARE_COMMAND(tls_cert);
    command.set_name_option({ "server" });
    command.set_hosts_option({});
    command.set_ips_option({});
    command.set_not_before_option(1767225600);
    command.set_days_option(365);
    command.set_private_key_argument({ "baadf00d" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TLS_CERT_INVALID_KEY "\n");
}

BC_AUTO_TEST_CASE(tls_cert__invoke__unnamed__failure_error)
{
    BX_DECLARE_COMMAND(tls_cert);
    command.set_name_option({ "" });
    command.set_hosts_option({});
    command.set_ips_option({});
    command.set_not_before_option(1767225600);
    command.set_days_option(365);
    command.set_private_key_argument({ TLS_CERT_KEY });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TLS_CERT_UNNAMED "\n");
}

BC_AUTO_TEST_CASE(tls_cert__invoke__invalid_ip__failure_error)
{
    BX_DECLARE_COMMAND(tls_cert);
    command.set_name_option({ "server" });
    command.set_hosts_option({});
    command.set_ips_option({ "127.0.0.256" });
    command.set_not_before_option(1767225600);
    command.set_days_option(365);
    command.set_private_key_argument({ TLS_CERT_KEY });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TLS_CERT_INVALID_IP "\n");
}

BC_AUTO_TEST_CASE(tls_cert__invoke__after_year_9999__failure_error)
{
    BX_DECLARE_COMMAND(tls_cert);
    command.set_name_option({ "server" });
    command.set_hosts_option({});
    command.set_ips_option({});
    command.set_not_before_option(253402214400);
    command.set_days_option(1);
    command.set_private_key_argument({ TLS_CERT_KEY });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_TLS_CERT_INVALID_VALIDITY "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
