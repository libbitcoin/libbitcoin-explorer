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
#ifndef BX_GET_FILTERS_HPP
#define BX_GET_FILTERS_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/generated.hpp>
#include <bitcoin/explorer/config/address.hpp>
#include <bitcoin/explorer/config/algorithm.hpp>
#include <bitcoin/explorer/config/btc.hpp>
#include <bitcoin/explorer/config/byte.hpp>
#include <bitcoin/explorer/config/bytes.hpp>
#include <bitcoin/explorer/config/electrum.hpp>
#include <bitcoin/explorer/config/encoding.hpp>
#include <bitcoin/explorer/config/endorsement.hpp>
#include <bitcoin/explorer/config/hd_key.hpp>
#include <bitcoin/explorer/config/language.hpp>
#include <bitcoin/explorer/config/sighash.hpp>
#include <bitcoin/explorer/config/signature.hpp>
#include <bitcoin/explorer/config/witness.hpp>
#include <bitcoin/explorer/config/wrapper.hpp>
#include <bitcoin/protocol/zmq/sodium.hpp>
#include <bitcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
namespace commands {

/**
 * Various localizable strings.
 */
#define BX_BIP157_UNSUPPORTED \
    "The peer does not indicate support for BIP157."

/**
 * Class to implement the get-filters command.
 */
class BCX_API get_filters
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "get-filters";
    }

    /**
     * Destructor.
     */
    virtual ~get_filters()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return get_filters::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "ONLINE";
    }

    /**
     * The localizable command description.
     */
    virtual const char* description()
    {
        return "Retrieve compact filters from a single Bitcoin network node. The distance between provided height and hash must be strictly less than 100.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual system::arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("height", 1)
            .add("hash", 1);
    }

    /**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input,
        po::variables_map& variables)
    {
        const auto raw = requires_raw_input();
        load_input(get_hash_argument(), "hash", variables, input, raw);
    }

    /**
     * Load program option definitions.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded program option definitions.
     */
    virtual system::options_metadata& load_options()
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
            value<boost::filesystem::path>(),
            "The path to the configuration settings file."
        )
        (
            "format,f",
            value<explorer::config::encoding>(&option_.format),
            "The output format. Options are 'info', 'json' and 'xml', defaults to 'info'."
        )
        (
            "host,t",
            value<std::string>(&option_.host)->default_value("localhost"),
            "The IP address or DNS name of the node. Defaults to localhost."
        )
        (
            "port,p",
            value<uint16_t>(&option_.port)->default_value(8333),
            "The IP port of the Bitcoin service on the node. Defaults to 8333, the standard for mainnet."
        )
        (
            "height",
            value<uint32_t>(&argument_.height),
            "The block height."
        )
        (
            "hash",
            value<system::config::hash256>(&argument_.hash),
            "The Base16 block hash. If not specified the hash is read from STDIN."
        );

        return options;
    }

    /**
     * Set variable defaults from configuration variable values.
     * @param[in]  variables  The loaded variables.
     */
    virtual void set_defaults_from_config(po::variables_map& variables)
    {
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    virtual system::console_result invoke(std::ostream& output,
        std::ostream& cerr);

    /* Properties */

    /**
     * Get the value of the height argument.
     */
    virtual uint32_t& get_height_argument()
    {
        return argument_.height;
    }

    /**
     * Set the value of the height argument.
     */
    virtual void set_height_argument(
        const uint32_t& value)
    {
        argument_.height = value;
    }

    /**
     * Get the value of the hash argument.
     */
    virtual system::config::hash256& get_hash_argument()
    {
        return argument_.hash;
    }

    /**
     * Set the value of the hash argument.
     */
    virtual void set_hash_argument(
        const system::config::hash256& value)
    {
        argument_.hash = value;
    }

    /**
     * Get the value of the format option.
     */
    virtual explorer::config::encoding& get_format_option()
    {
        return option_.format;
    }

    /**
     * Set the value of the format option.
     */
    virtual void set_format_option(
        const explorer::config::encoding& value)
    {
        option_.format = value;
    }

    /**
     * Get the value of the host option.
     */
    virtual std::string& get_host_option()
    {
        return option_.host;
    }

    /**
     * Set the value of the host option.
     */
    virtual void set_host_option(
        const std::string& value)
    {
        option_.host = value;
    }

    /**
     * Get the value of the port option.
     */
    virtual uint16_t& get_port_option()
    {
        return option_.port;
    }

    /**
     * Set the value of the port option.
     */
    virtual void set_port_option(
        const uint16_t& value)
    {
        option_.port = value;
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
          : height(),
            hash()
        {
        }

        uint32_t height;
        system::config::hash256 hash;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : format(),
            host(),
            port()
        {
        }

        explorer::config::encoding format;
        std::string host;
        uint16_t port;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
