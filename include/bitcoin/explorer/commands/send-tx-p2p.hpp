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
#ifndef BX_SEND_TX_P2P_HPP
#define BX_SEND_TX_P2P_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/generated.hpp>
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
#include <bitcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
namespace commands {

/**
 * Various localizable strings.
 */
#define BX_SEND_TX_P2P_OUTPUT \
    "%1% [%2%]: %3%"
#define BX_SEND_TX_P2P_SIGNAL \
    "Caught signal: %1%"
#define BX_SEND_TX_P2P_START_OKAY \
    "Started."
#define BX_SEND_TX_P2P_START_FAIL \
    "Start failed: %1%"
#define BX_SEND_TX_P2P_CHECK_OKAY \
    "%1% connections."
#define BX_SEND_TX_P2P_CHECK_FAIL \
    "Check failed: %1%"
#define BX_SEND_TX_P2P_SETUP_OKAY \
    "Sending %1%."
#define BX_SEND_TX_P2P_SETUP_FAIL \
    "Setup failed: %1%"
#define BX_SEND_TX_P2P_SEND_OKAY \
    "Sent at %1%."
#define BX_SEND_TX_P2P_SEND_FAIL \
    "Send failed: %1%"

/**
 * Class to implement the send-tx-p2p command.
 */
class send_tx_p2p 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    BCX_API static const char* symbol()
    {
        return "send-tx-p2p";
    }

    /**
     * The symbolic (not localizable) former command name, lower case.
     */
    BCX_API static const char* formerly()
    {
        return "sendtx-p2p";
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    BCX_API virtual const char* name()
    {
        return send_tx_p2p::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    BCX_API virtual const char* category()
    {
        return "ONLINE";
    }

    /**
     * The localizable command description.
     */
    BCX_API virtual const char* description()
    {
        return "Broadcast a transaction to the Bitcoin network via the Bitcoin peer-to-peer network.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    BCX_API virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("TRANSACTION", 1);
    }

	/**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    BCX_API virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
        load_input(get_transaction_argument(), "TRANSACTION", variables, input);
    }

    /**
     * Load program option definitions.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded program option definitions.
     */
    BCX_API virtual options_metadata& load_options()
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
            "nodes,n",
            value<size_t>(&option_.nodes)->default_value(2),
            "The number of network nodes to send the transaction to, defaults to two."
        )
        (
            "TRANSACTION",
            value<primitives::transaction>(&argument_.transaction),
            "The Base16 transaction to send. If not specified the transaction is read from STDIN."
        );

        return options;
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    BCX_API virtual console_result invoke(std::ostream& output,
        std::ostream& cerr);

    /* Properties */

    /**
     * Get the value of the TRANSACTION argument.
     */
    BCX_API virtual primitives::transaction& get_transaction_argument()
    {
        return argument_.transaction;
    }

    /**
     * Set the value of the TRANSACTION argument.
     */
    BCX_API virtual void set_transaction_argument(
        const primitives::transaction& value)
    {
        argument_.transaction = value;
    }

    /**
     * Get the value of the nodes option.
     */
    BCX_API virtual size_t& get_nodes_option()
    {
        return option_.nodes;
    }

    /**
     * Set the value of the nodes option.
     */
    BCX_API virtual void set_nodes_option(
        const size_t& value)
    {
        option_.nodes = value;
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
          : transaction()
        {
        }

        primitives::transaction transaction;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : nodes()
        {
        }

        size_t nodes;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
