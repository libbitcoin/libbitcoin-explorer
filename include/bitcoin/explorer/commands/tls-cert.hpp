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
#ifndef BX_TLS_CERT_HPP
#define BX_TLS_CERT_HPP

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/config/address.hpp>
#include <bitcoin/explorer/config/algorithm.hpp>
#include <bitcoin/explorer/config/btc.hpp>
#include <bitcoin/explorer/config/byte.hpp>
#include <bitcoin/explorer/config/bytes.hpp>
#include <bitcoin/explorer/config/ec_private.hpp>
#include <bitcoin/explorer/config/electrum.hpp>
#include <bitcoin/explorer/config/endorsement.hpp>
#include <bitcoin/explorer/config/group.hpp>
#include <bitcoin/explorer/config/hd_key.hpp>
#include <bitcoin/explorer/config/language.hpp>
#include <bitcoin/explorer/config/share.hpp>
#include <bitcoin/explorer/config/sighash.hpp>
#include <bitcoin/explorer/config/signature.hpp>
#include <bitcoin/explorer/config/wrapper.hpp>
#include <bitcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
namespace commands {

/**
 * Various localizable strings.
 */
#define BX_TLS_CERT_INVALID_KEY \
    "The private key is not a valid PEM P-256 private key."
#define BX_TLS_CERT_INVALID_IP \
    "An IP address is not valid."
#define BX_TLS_CERT_UNNAMED \
    "The certificate requires a common name, a host name or an IP address."
#define BX_TLS_CERT_INVALID_VALIDITY \
    "The validity period ends after the year 9999."

/**
 * Class to implement the tls-cert command.
 */
class BCX_API tls_cert
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "tls-cert";
    }

    /**
     * Destructor.
     */
    virtual ~tls_cert()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return tls_cert::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "MATH";
    }

    /**
     * The localizable command description.
     */
    virtual const char* description()
    {
        return "Create a self-signed PEM TLS certificate for a P-256 private key, for use with a Libbitcoin server.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("PRIVATE_KEY", 1);
    }

    /**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input      The input stream for loading the parameters.
     * @param[in]  variables  The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input,
        po::variables_map& variables)
    {
        load_input(get_private_key_argument(), "PRIVATE_KEY", variables, input);
    }

    /**
     * Load program option definitions.
     * @return  The loaded program option definitions.
     */
    virtual options_metadata& load_options()
    {
        using namespace po;
        options_description& options = get_option_metadata();
        options.add_options()
        (
            BX_HELP_VARIABLE ",h",
            value<bool>()->zero_tokens(),
            "Get a description and instructions for this command."
        )
        (
            BX_CONFIG_VARIABLE ",c",
            value<system::config::path>(),
            "The path to the configuration settings file."
        )
        (
            "name,n",
            value<std::string>(&option_.name),
            "The subject common name of the certificate."
        )
        (
            "host,h",
            value<std::vector<std::string>>(&option_.hosts),
            "A DNS host name of the server. Specify once for each name."
        )
        (
            "ip,i",
            value<std::vector<std::string>>(&option_.ips),
            "An IPv4 or IPv6 address of the server. Specify once for each address."
        )
        (
            "not_before,n",
            value<uint64_t>(&option_.not_before),
            "The start of the validity period in Unix seconds, defaults to the current time."
        )
        (
            "days,d",
            value<uint32_t>(&option_.days)->default_value(365),
            "The length of the validity period in days, defaults to 365."
        )
        (
            "PRIVATE_KEY",
            value<std::string>(&argument_.private_key),
            "The PEM P-256 private key of the certificate. If not specified the key is read from STDIN."
        );

        return options;
    }

    /**
     * Set variable defaults from configuration variable values.
     * @param[in]  variables  The loaded variables.
     */
    virtual void set_defaults_from_config(po::variables_map&)
    {
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    virtual console_result invoke(std::ostream& output,
        std::ostream& cerr);

    /* Properties */

    /**
     * Get the value of the PRIVATE_KEY argument.
     */
    virtual std::string& get_private_key_argument()
    {
        return argument_.private_key;
    }

    /**
     * Set the value of the PRIVATE_KEY argument.
     */
    virtual void set_private_key_argument(
        const std::string& value)
    {
        argument_.private_key = value;
    }

    /**
     * Get the value of the name option.
     */
    virtual std::string& get_name_option()
    {
        return option_.name;
    }

    /**
     * Set the value of the name option.
     */
    virtual void set_name_option(
        const std::string& value)
    {
        option_.name = value;
    }

    /**
     * Get the value of the host options.
     */
    virtual std::vector<std::string>& get_hosts_option()
    {
        return option_.hosts;
    }

    /**
     * Set the value of the host options.
     */
    virtual void set_hosts_option(
        const std::vector<std::string>& value)
    {
        option_.hosts = value;
    }

    /**
     * Get the value of the ip options.
     */
    virtual std::vector<std::string>& get_ips_option()
    {
        return option_.ips;
    }

    /**
     * Set the value of the ip options.
     */
    virtual void set_ips_option(
        const std::vector<std::string>& value)
    {
        option_.ips = value;
    }

    /**
     * Get the value of the not_before option.
     */
    virtual uint64_t& get_not_before_option()
    {
        return option_.not_before;
    }

    /**
     * Set the value of the not_before option.
     */
    virtual void set_not_before_option(
        const uint64_t& value)
    {
        option_.not_before = value;
    }

    /**
     * Get the value of the days option.
     */
    virtual uint32_t& get_days_option()
    {
        return option_.days;
    }

    /**
     * Set the value of the days option.
     */
    virtual void set_days_option(
        const uint32_t& value)
    {
        option_.days = value;
    }

private:

    /**
     * Command line argument bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct argument
    {
        argument()
          : private_key()
        {
        }

        std::string private_key;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : name(),
            hosts(),
            ips(),
            not_before(),
            days()
        {
        }

        std::string name;
        std::vector<std::string> hosts;
        std::vector<std::string> ips;
        uint64_t not_before;
        uint32_t days;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
