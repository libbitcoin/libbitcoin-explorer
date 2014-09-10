/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
#include <explorer/command.hpp>
#include <explorer/define.hpp>
#include <explorer/generated.hpp>
#include <explorer/primitives/address.hpp>
#include <explorer/primitives/base16.hpp>
#include <explorer/primitives/base58.hpp>
#include <explorer/primitives/btc.hpp>
#include <explorer/primitives/btc160.hpp>
#include <explorer/primitives/btc256.hpp>
#include <explorer/primitives/ec_private.hpp>
#include <explorer/primitives/ec_public.hpp>
#include <explorer/primitives/encoding.hpp>
#include <explorer/primitives/hashtype.hpp>
#include <explorer/primitives/hd_key.hpp>
#include <explorer/primitives/hd_priv.hpp>
#include <explorer/primitives/hd_pub.hpp>
#include <explorer/primitives/header.hpp>
#include <explorer/primitives/input.hpp>
#include <explorer/primitives/output.hpp>
#include <explorer/primitives/prefix.hpp>
#include <explorer/primitives/raw.hpp>
#include <explorer/primitives/script.hpp>
#include <explorer/primitives/stealth.hpp>
#include <explorer/primitives/transaction.hpp>
#include <explorer/primitives/wif.hpp>
#include <explorer/primitives/wrapper.hpp>
#include <explorer/utility/compat.hpp>
#include <explorer/utility/config.hpp>
#include <explorer/utility/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
namespace commands {

/**
 * Various localizable strings.
 */
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
    static const char* symbol() { return "send-tx-p2p"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return send_tx_p2p::symbol();
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
        return get_argument_metadata()
            .add("TRANSACTION", -1);
    }
	
	/**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
        //load_path(get_transactions_argument(), "TRANSACTION", variables);
        //load_input(get_transactions_argument(), "TRANSACTION", variables, input);
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
                BX_VARIABLE_CONFIG ",c",
                value<boost::filesystem::path>(),                 
                "The path and file name for the configuration settings file for this application."
            )
            (
                "help,h",
                value<bool>(&option_.help)->implicit_value(true),
                "Broadcast a transaction to the Bitcoin transaction pool via the Bitcoin peer-to-peer network."
            )
            (
                "nodes,n",
                value<size_t>(&option_.nodes)->default_value(2),
                "The number of network nodes to send the transaction to, defaults to two."
            )
            (
                "TRANSACTION",
                value<std::string>(),
                "The file path of the set of Base16 transactions. If not specified the transactions are read from STDIN."
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
     * Get the value of the TRANSACTION arguments.
     */
    virtual std::vector<primitives::transaction>& get_transactions_argument()
    {
        return argument_.transactions;
    }
    
    /**
     * Set the value of the TRANSACTION arguments.
     */
    virtual void set_transactions_argument(
        const std::vector<primitives::transaction>& value)
    {
        argument_.transactions = value;
    }

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
     * Get the value of the nodes option.
     */
    virtual size_t& get_nodes_option()
    {
        return option_.nodes;
    }
    
    /**
     * Set the value of the nodes option.
     */
    virtual void set_nodes_option(
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
          : transactions()
        {
        }
        
        std::vector<primitives::transaction> transactions;
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
            nodes()
        {
        }
        
        bool help;
        size_t nodes;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
