/**
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
#ifndef SX_COMMAND_HPP
#define SX_COMMAND_HPP

#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <sx/define.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace sx {

#define SX_VARIABLE_CONFIG "config"

/**
 * Abstract base class for definition of each SX command.
 */
class command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "not-implemented"; }

    /**
     * The symbolic (not localizable) command name, lower case.
     *
     * @return  Example: "fetch-transaction"
     */
    virtual const char* name()
    {
        return symbol();
    }

    /**
     * The localizable command category name, upper case.
     *
     * @return  Example: "ONLINE (OBELISK)"
     */
    virtual const char* category()
    {
        return symbol();
    }
    
    /**
     * Write the usage help for this command to the specified stream.
     *
     * @param[out] stream  The stream of interest.
     */
    virtual void write_usage(std::ostream& stream)
    {
        auto options = load_options();
        auto arguments = load_arguments();
    }
    
    /**
     * Invoke the command.
     *
     * @param[in]   input   The input stream for the command execution.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    virtual console_result invoke(std::istream& input, std::ostream& output,
        std::ostream& error)
    {
        return console_result::failure;
    }

    /**
     * Load command argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     *
     * @return  The loaded argument definitions.
     */
    virtual po::positional_options_description& load_arguments()
    {
        return argument_metadata_;
    }

    /**
     * Load environment variable definitions.
     *
     * @param[out] definitions  The defined program argument definitions.
     */
    virtual void load_environment(po::options_description& definitions)
    {
        using namespace po;
        definitions.add_options()
            /* This composes with the command line options. */
            (
                SX_VARIABLE_CONFIG, 
                value<boost::filesystem::path>()
                    ->composing()->default_value(config_default()),
                "The path and file name for the configuration settings file for this application."
            );
    }

    /**
     * Load command option definitions.
     * The implicit_value call allows flags to be strongly-typed on read while
     * allowing but not requiring a value on the command line for the option.
     *
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     *
     * @return  The loaded option definitions.
     */
    virtual po::options_description& load_options()
    {
        return option_metadata_;
    }
    
    /**
     * Load configuration setting definitions.
     *
     * @param[out] definitions  The defined program argument definitions.
     */
    virtual void load_settings(po::options_description& definitions)
    {
        using namespace po;
        definitions.add_options()
            (
                "general.testnet",
                value<bool>(&setting_.general.testnet),
                "Set to true in order to operate this application using Bitcoin testnet (vs. mainnet) addressing and blockchain data. This option is EXPERIMENTAL because other  libraries on which this application depends must currently be compiled with the testnet flag to ensure complete testnet semantics."
            )
            (
                "obelisk.client-certificate",
                value<boost::filesystem::path>(&setting_.obelisk.client_certificate),
                "The path to a private key certificate (file) that the server can use to prove the identity of this client. This is useful in authorizing remote administration of the server. The associated public key would need to be known by the server. Use the CZMQ program 'makecert' to generate the key certificate. For example: /home/genjix/.sx.cert"
            )
            (
                "obelisk.server-public-key",
                value<std::string>(&setting_.obelisk.server_public_key),
                "The public key of the server to which this application may connect. This must be the key for server specified by the 'service' option. For example: W=GRFxHUuUN#En3MI]f{}X:KWnV=pRZ$((byg=:h"
            )
            (
                "obelisk.service",
                value<std::string>(&setting_.obelisk.service)->default_value("tcp://obelisk.unsystem.net:8081"),
                "The URI of the server to which this application may connect."
            );
    }
	
	/**
     * Load streamed value as parameter fallback.
     *
     * @param[in]  input  The input stream for loading the parameter.
     * @param[in]         The loaded variables.
     */
    virtual void load_stream(std::istream& input, po::variables_map& variables)
	{
	}
    
    /* Properties */
    
    /**
     * Get command line argument metadata.
     */
    virtual po::positional_options_description& get_argument_metadata()
    {
        return argument_metadata_;
    }
    
    /**
     * Get command line option metadata.
     */
    virtual po::options_description& get_option_metadata()
    {
        return option_metadata_;
    }

    /**
     * Get the value of the general.testnet setting.
     */
    virtual bool get_general_testnet_setting()
    {
        return setting_.general.testnet;
    }

    /**
     * Set the value of the general.testnet setting.
     */
    virtual void set_general_testnet_setting(bool value)
    {
        setting_.general.testnet = value;
    }
    
    /**
     * Get the value of the obelisk.client-certificate setting.
     */
    virtual boost::filesystem::path get_obelisk_client_certificate_setting()
    {
        return setting_.obelisk.client_certificate;
    }

    /**
     * Set the value of the obelisk.client-certificate setting.
     */
    virtual void set_obelisk_client_certificate_setting(boost::filesystem::path value)
    {
        setting_.obelisk.client_certificate = value;
    }
    
    /**
     * Get the value of the obelisk.server-public-key setting.
     */
    virtual std::string get_obelisk_server_public_key_setting()
    {
        return setting_.obelisk.server_public_key;
    }

    /**
     * Set the value of the obelisk.server-public-key setting.
     */
    virtual void set_obelisk_server_public_key_setting(std::string value)
    {
        setting_.obelisk.server_public_key = value;
    }
    
    /**
     * Get the value of the obelisk.service setting.
     */
    virtual std::string get_obelisk_service_setting()
    {
        return setting_.obelisk.service;
    }

    /**
     * Set the value of the obelisk.service setting.
     */
    virtual void set_obelisk_service_setting(std::string value)
    {
        setting_.obelisk.service = value;
    }
    
protected:

    /**
     * This base class is abstract but not pure virtual, so prevent direct 
     * construction here.
     */
    command() {}
    
private:
    
    /**
     * Command line argument metadata.
     */
    po::positional_options_description argument_metadata_;

    /**
     * Command line option metadata.
     */
    po::options_description option_metadata_;
    
    /**
     * Environment variable bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct environment
    {
        environment()
            {}
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
              : testnet()
                {}
            bool testnet;
        } general;

        struct obelisk
        {
            obelisk()
              : client_certificate(),
                server_public_key(),
                service()
                {}
            boost::filesystem::path client_certificate;
            std::string server_public_key;
            std::string service;
        } obelisk;

        setting()
          : general(),
            obelisk()
            {}
    } setting_;
};

} // sx

#endif
