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
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/config.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/address.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>
#include <bitcoin/explorer/primitives/base2.hpp>
#include <bitcoin/explorer/primitives/base58.hpp>
#include <bitcoin/explorer/primitives/base64.hpp>
#include <bitcoin/explorer/primitives/btc.hpp>
#include <bitcoin/explorer/primitives/btc160.hpp>
#include <bitcoin/explorer/primitives/btc256.hpp>
#include <bitcoin/explorer/primitives/byte.hpp>
#include <bitcoin/explorer/primitives/ec_private.hpp>
#include <bitcoin/explorer/primitives/ec_public.hpp>
#include <bitcoin/explorer/primitives/encoding.hpp>
#include <bitcoin/explorer/primitives/endorsement.hpp>
#include <bitcoin/explorer/primitives/hashtype.hpp>
#include <bitcoin/explorer/primitives/hd_key.hpp>
#include <bitcoin/explorer/primitives/hd_priv.hpp>
#include <bitcoin/explorer/primitives/hd_pub.hpp>
#include <bitcoin/explorer/primitives/header.hpp>
#include <bitcoin/explorer/primitives/input.hpp>
#include <bitcoin/explorer/primitives/output.hpp>
#include <bitcoin/explorer/primitives/raw.hpp>
#include <bitcoin/explorer/primitives/script.hpp>
#include <bitcoin/explorer/primitives/signature.hpp>
#include <bitcoin/explorer/primitives/stealth.hpp>
#include <bitcoin/explorer/primitives/transaction.hpp>
#include <bitcoin/explorer/primitives/uri.hpp>
#include <bitcoin/explorer/primitives/wif.hpp>
#include <bitcoin/explorer/primitives/wrapper.hpp>
#include <bitcoin/explorer/primitives/bip39_language.hpp>
#include <bitcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {

#define BX_CONFIG_VARIABLE "config"
#define BX_HELP_VARIABLE "help"
#define BX_PROGRAM_NAME "bx"

/**
 * Base class for definition of each Bitcoin Explorer command.
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
        (
            /* This composes with the command line options. */
            BX_CONFIG_VARIABLE, 
            value<boost::filesystem::path>()
                ->composing()->default_value(default_config_path()),
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
            "general.network",
#ifdef ENABLE_TESTNET
            value<std::string>(&setting_.general.network)->default_value("testnet"),
            "The network to use, either 'mainnet' or 'testnet'. Defaults to 'testnet'."
#else
            value<std::string>(&setting_.general.network)->default_value("mainnet"),
            "The network to use, either 'mainnet' or 'testnet'. Defaults to 'mainnet'."
#endif
        )
        (
            "general.retries",
            value<primitives::byte>(&setting_.general.retries),
            "Number of times to retry contacting the server before giving up."
        )
        (
            "general.wait",
            value<uint32_t>(&setting_.general.wait)->default_value(2000),
            "Milliseconds to wait for a response from the server."
        )
        (
            "mainnet.url",
            value<primitives::uri>(&setting_.mainnet.url)->default_value({ "tcp://obelisk.airbitz.co:9091" }),
            "The URL of the Obelisk mainnet server."
        )
        (
            "testnet.url",
            value<primitives::uri>(&setting_.testnet.url)->default_value({ "tcp://obelisk-testnet.airbitz.co:9091" }),
            "The URL of the Obelisk testnet server."
        )
        (
            "logging.debug",
            value<boost::filesystem::path>(&setting_.logging.debug)->default_value("debug.log"),
            "The path to the debug log file, used by send-tx-p2p."
        )
        (
            "logging.error",
            value<boost::filesystem::path>(&setting_.logging.error)->default_value("error.log"),
            "The path to the error log file, used by send-tx-p2p."
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
        config::printer help(options, arguments, BX_PROGRAM_NAME, description(),
            name());
        help.initialize();
        help.commandline(output);
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
     * Get the value of the general.network setting.
     */
    BCX_API virtual std::string get_general_network_setting()
    {
        return setting_.general.network;
    }

    /**
     * Set the value of the general.network setting.
     */
    BCX_API virtual void set_general_network_setting(std::string value)
    {
        setting_.general.network = value;
    }

    /**
     * Get the value of the general.retries setting.
     */
    BCX_API virtual primitives::byte get_general_retries_setting()
    {
        return setting_.general.retries;
    }

    /**
     * Set the value of the general.retries setting.
     */
    BCX_API virtual void set_general_retries_setting(primitives::byte value)
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
     * Get the value of the mainnet.url setting.
     */
    BCX_API virtual primitives::uri get_mainnet_url_setting()
    {
        return setting_.mainnet.url;
    }

    /**
     * Set the value of the mainnet.url setting.
     */
    BCX_API virtual void set_mainnet_url_setting(primitives::uri value)
    {
        setting_.mainnet.url = value;
    }

    /**
     * Get the value of the testnet.url setting.
     */
    BCX_API virtual primitives::uri get_testnet_url_setting()
    {
        return setting_.testnet.url;
    }

    /**
     * Set the value of the testnet.url setting.
     */
    BCX_API virtual void set_testnet_url_setting(primitives::uri value)
    {
        setting_.testnet.url = value;
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
              : network(),
                retries(),
                wait()
            {
            }

            std::string network;
            primitives::byte retries;
            uint32_t wait;
        } general;

        struct mainnet
        {
            mainnet()
              : url()
            {
            }

            primitives::uri url;
        } mainnet;

        struct testnet
        {
            testnet()
              : url()
            {
            }

            primitives::uri url;
        } testnet;

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

        setting()
          : general(),
            mainnet(),
            testnet(),
            logging()
        {
        }
    } setting_;
};

} // namespace explorer
} // namespace libbitcoin

#endif
