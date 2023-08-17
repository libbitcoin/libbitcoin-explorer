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
#ifndef BX_FETCH_FILTER_HEADERS_HPP
#define BX_FETCH_FILTER_HEADERS_HPP

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
 * Class to implement the fetch-filter-headers command.
 */
class BCX_API fetch_filter_headers
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "fetch-filter-headers";
    }

    /**
     * Destructor.
     */
    virtual ~fetch_filter_headers()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return fetch_filter_headers::symbol();
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
        return "Retrieve compact filter headers from a Libbitcoin server. The distance between provided height and hash must be strictly less than 2000.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual system::arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("start_height", 1);
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
            "stop_hash,s",
            value<system::config::hash256>(&option_.stop_hash),
            "The Base16 stop block hash."
        )
        (
            "stop_height,t",
            value<uint32_t>(&option_.stop_height),
            "The stop block height."
        )
        (
            "start_height",
            value<uint32_t>(&argument_.start_height),
            "The starting block height."
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
     * Get the value of the start_height argument.
     */
    virtual uint32_t& get_start_height_argument()
    {
        return argument_.start_height;
    }

    /**
     * Set the value of the start_height argument.
     */
    virtual void set_start_height_argument(
        const uint32_t& value)
    {
        argument_.start_height = value;
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
     * Get the value of the stop_hash option.
     */
    virtual system::config::hash256& get_stop_hash_option()
    {
        return option_.stop_hash;
    }

    /**
     * Set the value of the stop_hash option.
     */
    virtual void set_stop_hash_option(
        const system::config::hash256& value)
    {
        option_.stop_hash = value;
    }

    /**
     * Get the value of the stop_height option.
     */
    virtual uint32_t& get_stop_height_option()
    {
        return option_.stop_height;
    }

    /**
     * Set the value of the stop_height option.
     */
    virtual void set_stop_height_option(
        const uint32_t& value)
    {
        option_.stop_height = value;
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
          : start_height()
        {
        }

        uint32_t start_height;
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
            stop_hash(),
            stop_height()
        {
        }

        explorer::config::encoding format;
        system::config::hash256 stop_hash;
        uint32_t stop_height;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
