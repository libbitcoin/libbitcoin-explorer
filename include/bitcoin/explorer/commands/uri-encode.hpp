/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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
#ifndef BX_URI_ENCODE_HPP
#define BX_URI_ENCODE_HPP

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
#include <bitcoin/explorer/config/cert_key.hpp>
#include <bitcoin/explorer/config/ec_private.hpp>
#include <bitcoin/explorer/config/encoding.hpp>
#include <bitcoin/explorer/config/endorsement.hpp>
#include <bitcoin/explorer/config/hashtype.hpp>
#include <bitcoin/explorer/config/hd_key.hpp>
#include <bitcoin/explorer/config/header.hpp>
#include <bitcoin/explorer/config/input.hpp>
#include <bitcoin/explorer/config/language.hpp>
#include <bitcoin/explorer/config/output.hpp>
#include <bitcoin/explorer/config/raw.hpp>
#include <bitcoin/explorer/config/script.hpp>
#include <bitcoin/explorer/config/signature.hpp>
#include <bitcoin/explorer/config/transaction.hpp>
#include <bitcoin/explorer/config/wrapper.hpp>
#include <bitcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
namespace commands {

/**
 * Class to implement the uri-encode command.
 */
class BCX_API uri_encode
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "uri-encode";
    }


    /**
     * Destructor.
     */
    virtual ~uri_encode()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return uri_encode::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "WALLET";
    }

    /**
     * The localizable command description.
     */
    virtual const char* description()
    {
        return "Compose a Bitcoin URI from specified parts.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("ADDRESS", 1);
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
            value<boost::filesystem::path>(),
            "The path to the configuration settings file."
        )
        (
            "amount,a",
            value<explorer::config::btc>(&option_.amount),
            "The value of the amount parameter."
        )
        (
            "label,l",
            value<std::string>(&option_.label),
            "The value of the label parameter."
        )
        (
            "message,m",
            value<std::string>(&option_.message),
            "The value of the message parameter."
        )
        (
            "request,r",
            value<bc::config::endpoint>(&option_.request),
            "The value of the payment request parameter."
        )
        (
            "ADDRESS",
            value<explorer::config::address>(&argument_.address),
            "The payment address or stealth address for the address part."
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
    virtual console_result invoke(std::ostream& output,
        std::ostream& cerr);

    /* Properties */

    /**
     * Get the value of the ADDRESS argument.
     */
    virtual explorer::config::address& get_address_argument()
    {
        return argument_.address;
    }

    /**
     * Set the value of the ADDRESS argument.
     */
    virtual void set_address_argument(
        const explorer::config::address& value)
    {
        argument_.address = value;
    }

    /**
     * Get the value of the amount option.
     */
    virtual explorer::config::btc& get_amount_option()
    {
        return option_.amount;
    }

    /**
     * Set the value of the amount option.
     */
    virtual void set_amount_option(
        const explorer::config::btc& value)
    {
        option_.amount = value;
    }

    /**
     * Get the value of the label option.
     */
    virtual std::string& get_label_option()
    {
        return option_.label;
    }

    /**
     * Set the value of the label option.
     */
    virtual void set_label_option(
        const std::string& value)
    {
        option_.label = value;
    }

    /**
     * Get the value of the message option.
     */
    virtual std::string& get_message_option()
    {
        return option_.message;
    }

    /**
     * Set the value of the message option.
     */
    virtual void set_message_option(
        const std::string& value)
    {
        option_.message = value;
    }

    /**
     * Get the value of the request option.
     */
    virtual bc::config::endpoint& get_request_option()
    {
        return option_.request;
    }

    /**
     * Set the value of the request option.
     */
    virtual void set_request_option(
        const bc::config::endpoint& value)
    {
        option_.request = value;
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
          : address()
        {
        }

        explorer::config::address address;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : amount(),
            label(),
            message(),
            request()
        {
        }

        explorer::config::btc amount;
        std::string label;
        std::string message;
        bc::config::endpoint request;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
