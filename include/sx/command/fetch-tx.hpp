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
#ifndef SX_FETCH_TX_HPP
#define SX_FETCH_TX_HPP

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/command.hpp>
#include <sx/define.hpp>
#include <sx/generated.hpp>
#include <sx/serializer/address.hpp>
#include <sx/serializer/base58.hpp>
#include <sx/serializer/btc160.hpp>
#include <sx/serializer/btc256.hpp>
#include <sx/serializer/ec_private.hpp>
#include <sx/serializer/ec_public.hpp>
#include <sx/serializer/encoding.hpp>
#include <sx/serializer/hd_key.hpp>
#include <sx/serializer/hd_priv.hpp>
#include <sx/serializer/hd_pub.hpp>
#include <sx/serializer/header.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/serializer/input.hpp>
#include <sx/serializer/output.hpp>
#include <sx/serializer/prefix.hpp>
#include <sx/serializer/raw.hpp>
#include <sx/serializer/script.hpp>
#include <sx/serializer/signature_hash.hpp>
#include <sx/serializer/stealth.hpp>
#include <sx/serializer/transaction.hpp>
#include <sx/serializer/wif.hpp>
#include <sx/serializer/wrapper.hpp>
#include <sx/utility/compat.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace sx {
namespace extension {

/**
 * Class to implement the sx fetch-tx command.
 */
class fetch_tx 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "fetch-tx"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return fetch_tx::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "ONLINE";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata();
    }
	
	/**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
    }
    
    /**
     * Load program option definitions.
     * The implicit_value call allows flags to be strongly-typed on read while
     * allowing but not requiring a value on the command line for the option.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded program option definitions.
     */
    virtual options_metadata& load_options()
    {
        using namespace po;
        options_description& options = get_option_metadata();
        options.add_options()
            (
                SX_VARIABLE_CONFIG ",c",
                value<boost::filesystem::path>(),                 
                "The path and file name for the configuration settings file for this application."
            )
            (
                "help,h",
                value<bool>(&option_.help)->implicit_value(true),
                "Get transactions by filter. Requires an Obelisk server connection."
            )
            (
                "format,f",
                value<serializer::encoding>(&option_.format),
                "The output format. Options are 'json', 'xml', 'info' or 'native', defaults to native."
            )
            (
                "hash,s",
                value<std::vector<serializer::btc256>>(&option_.hashs),
                "The set of hex encoded transaction hashes to get. Overrides prefix and height options."
            )
            (
                "prefix,p",
                value<std::vector<serializer::prefix>>(&option_.prefixs),
                "The set of binary encoded stealth search prefixes of transactions to get."
            )
            (
                "height,t",
                value<size_t>(&option_.height),
                "The minimum block height of prefix transactions to get. Includes all blocks if not set."
            )
            (
                "secret,s",
                value<serializer::ec_private>(&option_.secret),
                "The hex encoded EC private key to use locally in confirming stealth transactions."
            );

        return options;
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    virtual console_result invoke(std::ostream& output, std::ostream& cerr);
        
    /* Properties */

    /**
     * Get the value of the help option.
     */
    virtual bool& get_help_option()
    {
        return option_.help;
    }
    
    /**
     * Set the value of the help option.
     */
    virtual void set_help_option(
        const bool& value)
    {
        option_.help = value;
    }

    /**
     * Get the value of the format option.
     */
    virtual serializer::encoding& get_format_option()
    {
        return option_.format;
    }
    
    /**
     * Set the value of the format option.
     */
    virtual void set_format_option(
        const serializer::encoding& value)
    {
        option_.format = value;
    }

    /**
     * Get the value of the hash options.
     */
    virtual std::vector<serializer::btc256>& get_hashs_option()
    {
        return option_.hashs;
    }
    
    /**
     * Set the value of the hash options.
     */
    virtual void set_hashs_option(
        const std::vector<serializer::btc256>& value)
    {
        option_.hashs = value;
    }

    /**
     * Get the value of the prefix options.
     */
    virtual std::vector<serializer::prefix>& get_prefixs_option()
    {
        return option_.prefixs;
    }
    
    /**
     * Set the value of the prefix options.
     */
    virtual void set_prefixs_option(
        const std::vector<serializer::prefix>& value)
    {
        option_.prefixs = value;
    }

    /**
     * Get the value of the height option.
     */
    virtual size_t& get_height_option()
    {
        return option_.height;
    }
    
    /**
     * Set the value of the height option.
     */
    virtual void set_height_option(
        const size_t& value)
    {
        option_.height = value;
    }

    /**
     * Get the value of the secret option.
     */
    virtual serializer::ec_private& get_secret_option()
    {
        return option_.secret;
    }
    
    /**
     * Set the value of the secret option.
     */
    virtual void set_secret_option(
        const serializer::ec_private& value)
    {
        option_.secret = value;
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
        {
        }
        
    } argument_;
    
    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : help(),
            format(),
            hashs(),
            prefixs(),
            height(),
            secret()
        {
        }
        
        bool help;
        serializer::encoding format;
        std::vector<serializer::btc256> hashs;
        std::vector<serializer::prefix> prefixs;
        size_t height;
        serializer::ec_private secret;
    } option_;
};

} // extension
} // sx

#endif
