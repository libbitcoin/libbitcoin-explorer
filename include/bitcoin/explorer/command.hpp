/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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
#ifndef BX_COMMAND_HPP
#define BX_COMMAND_HPP

#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/address.hpp>
#include <bitcoin/explorer/primitives/base10.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>
#include <bitcoin/explorer/primitives/base2.hpp>
#include <bitcoin/explorer/primitives/base58.hpp>
#include <bitcoin/explorer/primitives/btc.hpp>
#include <bitcoin/explorer/primitives/btc160.hpp>
#include <bitcoin/explorer/primitives/btc256.hpp>
#include <bitcoin/explorer/primitives/ec_private.hpp>
#include <bitcoin/explorer/primitives/ec_public.hpp>
#include <bitcoin/explorer/primitives/encoding.hpp>
#include <bitcoin/explorer/primitives/hashtype.hpp>
#include <bitcoin/explorer/primitives/hd_key.hpp>
#include <bitcoin/explorer/primitives/hd_priv.hpp>
#include <bitcoin/explorer/primitives/hd_pub.hpp>
#include <bitcoin/explorer/primitives/header.hpp>
#include <bitcoin/explorer/primitives/input.hpp>
#include <bitcoin/explorer/primitives/output.hpp>
#include <bitcoin/explorer/primitives/raw.hpp>
#include <bitcoin/explorer/primitives/script.hpp>
#include <bitcoin/explorer/primitives/stealth.hpp>
#include <bitcoin/explorer/primitives/transaction.hpp>
#include <bitcoin/explorer/primitives/wif.hpp>
#include <bitcoin/explorer/primitives/wrapper.hpp>
#include <bitcoin/explorer/utility/config.hpp>
#include <bitcoin/explorer/utility/printer.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {

#define BX_CONFIG_VARIABLE "config"
#define BX_HELP_VARIABLE "help"
#define BX_PROGRAM_NAME "bx"

/**
 * Abstract base class for definition of each Bitcoin Explorer command.
 */
class command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    BCX_API static const char* symbol()
    {
        return "not-implemented";
    }

    /**
     * The symbolic (not localizable) command name, lower case.
     * @return  Example: "fetch-transaction"
     */
    BCX_API virtual const char* name()
    {
        return symbol();
    }

    /**
     * The localizable command category name, upper case.
     * @return  Example: "ONLINE"
     */
    BCX_API virtual const char* category()
    {
        return "not-implemented";
    }

    /**
     * The localizable command description.
     * @return  Example: "Get transactions by hash."
     */
    BCX_API virtual const char* description()
    {
        return "not-implemented";
    }

    /**
     * Declare whether the command has been obsoleted.
     * @return  True if the command is obsolete
     */
    BCX_API virtual bool obsolete()
    {
        return false;
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    BCX_API virtual console_result invoke(std::ostream& output,
        std::ostream& error)
    {
        return console_result::failure;
    }

    /**
     * Load command argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded argument definitions.
     */
    BCX_API virtual arguments_metadata& load_arguments()
    {
        return argument_metadata_;
    }

    /**
     * Load environment variable definitions.
     * @param[out] definitions  The defined program argument definitions.
     */
    BCX_API virtual void load_environment(options_metadata& definitions)
    {
        using namespace po;
        definitions.add_options()
        /* This composes with the command line options. */
        (
            BX_CONFIG_VARIABLE, 
            value<boost::filesystem::path>()
                ->composing()->default_value(config_default()),
            "The path to the configuration settings file."
        );
    }

    /**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input      The input stream for loading the parameters.
     * @param[in]  variables  The loaded variables.
     */
    BCX_API virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
    }

    /**
     * Load command option definitions.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded option definitions.
     */
    BCX_API virtual options_metadata& load_options()
    {
        return option_metadata_;
    }

    /**
     * Load configuration setting definitions.
     * @param[out] definitions  The defined program argument definitions.
     */
    BCX_API virtual void load_settings(options_metadata& definitions)
    {
        using namespace po;
        definitions.add_options()
        (
            "general.testnet",
            value<bool>(&setting_.general.testnet)->default_value(false),
            "Set to true for testnet operation. This option is EXPERIMENTAL because other libraries on which this application depends must currently be compiled with the testnet flag to ensure complete testnet semantics."
        )
        (
            "general.retries",
            value<primitives::base10>(&setting_.general.retries),
            "Number of times to retry contacting the server before giving up."
        )
        (
            "general.wait",
            value<uint32_t>(&setting_.general.wait)->default_value(2000),
            "Milliseconds to wait for a response from the server."
        )
        (
            "logging.debug",
            value<boost::filesystem::path>(&setting_.logging.debug)->default_value("debug.log"),
            "The file and path name to the debug log file."
        )
        (
            "logging.error",
            value<boost::filesystem::path>(&setting_.logging.error)->default_value("error.log"),
            "The file and path name to the error log file."
        )
        (
            "server.public-key",
            value<primitives::base16>(&setting_.server.public_key),
            "The public key of the server to which this application may connect. This must be the key for server specified by the 'service' option. For example: W=GRFxHUuUN#En3MI]f{}X:KWnV=pRZ$((byg=:h"
        )
        (
            "server.address",
            value<std::string>(&setting_.server.address)->default_value("tcp://obelisk-sol.airbitz.co:9091"),
            "The URI of the server to which this application may connect."
        )
        (
            "server.socks-proxy",
            value<std::string>(&setting_.server.socks_proxy),
            "The host name and port number of a Socks5 proxy server."
        );
    }

    /**
     * Load streamed value as parameter fallback.
     * @param[in]  input      The input stream for loading the parameter.
     * @param[in]  variables  The loaded variables.
     */
    BCX_API virtual void load_stream(std::istream& input, po::variables_map& variables)
    {
    }

    /**
     * Write the help for this command to the specified stream.
     * @param[out] output  The output stream.
     */
    BCX_API virtual void write_help(std::ostream& output)
    {
        const auto& options = get_option_metadata();
        const auto& arguments = get_argument_metadata();
        printer help(BX_PROGRAM_NAME, category(), name(), description(),
            arguments, options);
        help.initialize();
        help.print(output);
    }

    /* Properties */
    
    /**
     * Get command line argument metadata.
     */
    BCX_API virtual arguments_metadata& get_argument_metadata()
    {
        return argument_metadata_;
    }

    /**
     * Get command line option metadata.
     */
    BCX_API virtual options_metadata& get_option_metadata()
    {
        return option_metadata_;
    }

    /**
     * Get the value of the general.testnet setting.
     */
    BCX_API virtual bool get_general_testnet_setting()
    {
        return setting_.general.testnet;
    }

    /**
     * Set the value of the general.testnet setting.
     */
    BCX_API virtual void set_general_testnet_setting(bool value)
    {
        setting_.general.testnet = value;
    }

    /**
     * Get the value of the general.retries setting.
     */
    BCX_API virtual primitives::base10 get_general_retries_setting()
    {
        return setting_.general.retries;
    }

    /**
     * Set the value of the general.retries setting.
     */
    BCX_API virtual void set_general_retries_setting(primitives::base10 value)
    {
        setting_.general.retries = value;
    }

    /**
     * Get the value of the general.wait setting.
     */
    BCX_API virtual uint32_t get_general_wait_setting()
    {
        return setting_.general.wait;
    }

    /**
     * Set the value of the general.wait setting.
     */
    BCX_API virtual void set_general_wait_setting(uint32_t value)
    {
        setting_.general.wait = value;
    }

    /**
     * Get the value of the logging.debug setting.
     */
    BCX_API virtual boost::filesystem::path get_logging_debug_setting()
    {
        return setting_.logging.debug;
    }

    /**
     * Set the value of the logging.debug setting.
     */
    BCX_API virtual void set_logging_debug_setting(boost::filesystem::path value)
    {
        setting_.logging.debug = value;
    }

    /**
     * Get the value of the logging.error setting.
     */
    BCX_API virtual boost::filesystem::path get_logging_error_setting()
    {
        return setting_.logging.error;
    }

    /**
     * Set the value of the logging.error setting.
     */
    BCX_API virtual void set_logging_error_setting(boost::filesystem::path value)
    {
        setting_.logging.error = value;
    }

    /**
     * Get the value of the server.public-key setting.
     */
    BCX_API virtual primitives::base16 get_server_public_key_setting()
    {
        return setting_.server.public_key;
    }

    /**
     * Set the value of the server.public-key setting.
     */
    BCX_API virtual void set_server_public_key_setting(primitives::base16 value)
    {
        setting_.server.public_key = value;
    }

    /**
     * Get the value of the server.address setting.
     */
    BCX_API virtual std::string get_server_address_setting()
    {
        return setting_.server.address;
    }

    /**
     * Set the value of the server.address setting.
     */
    BCX_API virtual void set_server_address_setting(std::string value)
    {
        setting_.server.address = value;
    }

    /**
     * Get the value of the server.socks-proxy setting.
     */
    BCX_API virtual std::string get_server_socks_proxy_setting()
    {
        return setting_.server.socks_proxy;
    }

    /**
     * Set the value of the server.socks-proxy setting.
     */
    BCX_API virtual void set_server_socks_proxy_setting(std::string value)
    {
        setting_.server.socks_proxy = value;
    }

protected:

    /**
     * This base class is abstract but not pure virtual, so prevent direct 
     * construction here.
     */
    BCX_API command()
    {
    }

private:
    
    /**
     * Command line argument metadata.
     */
    arguments_metadata argument_metadata_;

    /**
     * Command line option metadata.
     */
    options_metadata option_metadata_;

    /**
     * Environment variable bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct environment
    {
        environment()
        {
        }

    } environment_;

    /**
     * Configuration setting file bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct setting
    {
        struct general
        {
            general()
              : testnet(),
                retries(),
                wait()
            {
            }

            bool testnet;
            primitives::base10 retries;
            uint32_t wait;
        } general;

        struct logging
        {
            logging()
              : debug(),
                error()
            {
            }

            boost::filesystem::path debug;
            boost::filesystem::path error;
        } logging;

        struct server
        {
            server()
              : public_key(),
                address(),
                socks_proxy()
            {
            }

            primitives::base16 public_key;
            std::string address;
            std::string socks_proxy;
        } server;

        setting()
          : general(),
            logging(),
            server()
        {
        }
    } setting_;
};

} // namespace explorer
} // namespace libbitcoin

#endif
