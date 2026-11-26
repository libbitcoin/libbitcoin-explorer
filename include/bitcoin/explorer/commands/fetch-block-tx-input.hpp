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
#ifndef BX_FETCH_BLOCK_TX_INPUT_HPP
#define BX_FETCH_BLOCK_TX_INPUT_HPP

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
#define BX_FETCH_TX_INDEX_UNCONFIRMED \
    "The transaction is not confirmed."

/**
 * Class to implement the fetch-block-tx-input command.
 */
class BCX_API fetch_block_tx_input
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "fetch-block-tx-input";
    }

    /**
     * Destructor.
     */
    virtual ~fetch_block_tx_input()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return fetch_block_tx_input::symbol();
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
        return "Get the script of an input of the transaction at a position in the block. Requires a Libbitcoin server connection.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("height", 1)
            .add("tx-index", 1)
            .add("input-index", 1)
            .add("server-url", 1);
    }

    /**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input      The input stream for loading the parameters.
     * @param[in]  variables  The loaded variables.
     */
    virtual void load_fallbacks(std::istream&,
        po::variables_map&)
    {
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
            "height",
            value<uint32_t>(&argument_.height)->required(),
            "The block height."
        )
        (
            "tx-index",
            value<uint32_t>(&argument_.tx_index),
            "The transaction position index in the block, defaults to 0."
        )
        (
            "input-index",
            value<uint32_t>(&argument_.input_index),
            "The input position index in the transaction, defaults to 0."
        )
        (
            "server-url",
            value<system::config::url>(&argument_.server_url),
            "The URL of the Libbitcoin server to use. If not specified the URL is obtained from configuration settings or defaults."
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
     * Get the value of the tx-index argument.
     */
    virtual uint32_t& get_tx_index_argument()
    {
        return argument_.tx_index;
    }

    /**
     * Set the value of the tx-index argument.
     */
    virtual void set_tx_index_argument(
        const uint32_t& value)
    {
        argument_.tx_index = value;
    }

    /**
     * Get the value of the input-index argument.
     */
    virtual uint32_t& get_input_index_argument()
    {
        return argument_.input_index;
    }

    /**
     * Set the value of the input-index argument.
     */
    virtual void set_input_index_argument(
        const uint32_t& value)
    {
        argument_.input_index = value;
    }

    /**
     * Get the value of the server-url argument.
     */
    virtual system::config::url& get_server_url_argument()
    {
        return argument_.server_url;
    }

    /**
     * Set the value of the server-url argument.
     */
    virtual void set_server_url_argument(
        const system::config::url& value)
    {
        argument_.server_url = value;
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
            tx_index(),
            input_index(),
            server_url()
        {
        }

        uint32_t height;
        uint32_t tx_index;
        uint32_t input_index;
        system::config::url server_url;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
        {
        }

    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
