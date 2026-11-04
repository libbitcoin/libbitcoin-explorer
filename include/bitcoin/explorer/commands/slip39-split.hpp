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
#ifndef BX_SLIP39_SPLIT_HPP
#define BX_SLIP39_SPLIT_HPP

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
#include <bitcoin/explorer/config/witness.hpp>
#include <bitcoin/explorer/config/wrapper.hpp>
#include <bitcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
namespace commands {

/**
 * Various localizable strings.
 */
#define BX_SLIP39_SPLIT_INVALID_SECRET \
    "The secret size is not an even 16 to 64 bytes."
#define BX_SLIP39_SPLIT_INVALID_GROUPS \
    "The groups or threshold are invalid."
#define BX_SLIP39_SPLIT_INVALID_IDENTIFIER \
    "The identifier is greater than 32767."
#define BX_SLIP39_SPLIT_INVALID_EXPONENT \
    "The exponent is greater than 15."
#define BX_SLIP39_SPLIT_INVALID_PASSPHRASE \
    "The passphrase is not printable ASCII."
#define BX_SLIP39_SPLIT_INVALID_ENTROPY_SIZE \
    "The entropy size in bytes must be"

/**
 * Class to implement the slip39-split command.
 */
class BCX_API slip39_split
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "slip39-split";
    }

    /**
     * Destructor.
     */
    virtual ~slip39_split()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return slip39_split::symbol();
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
        return "Split a master secret into groups of SLIP39 shares, one share per line, in group order.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("ENTROPY", 1);
    }

    /**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input      The input stream for loading the parameters.
     * @param[in]  variables  The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input,
        po::variables_map& variables)
    {
        load_input(get_entropy_argument(), "ENTROPY", variables, input);
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
            "exponent,e",
            value<uint8_t>(&option_.exponent)->default_value(1),
            "The exponent of the passphrase iteration count, 0 to 15, defaults to 1."
        )
        (
            "extendable,x",
            value<bool>(&option_.extendable)->zero_tokens(),
            "Create an extendable share set."
        )
        (
            "group,g",
            value<std::vector<explorer::config::group>>(&option_.groups)->required(),
            "A group of shares, as its threshold and count, such as 2/3. Specify once for each group."
        )
        (
            "identifier,i",
            value<uint16_t>(&option_.identifier)->default_value(0),
            "The random identifier of the share set, 0 to 32767, defaults to 0."
        )
        (
            "passphrase,p",
            value<std::string>(&option_.passphrase),
            "An optional passphrase of printable ASCII."
        )
        (
            "secret,s",
            value<system::config::base16>(&option_.secret)->required(),
            "The Base16 master secret, an even 16 to 64 bytes."
        )
        (
            "threshold,t",
            value<uint8_t>(&option_.threshold)->default_value(1),
            "The number of groups required to recover the master secret, defaults to 1."
        )
        (
            "ENTROPY",
            value<system::config::base16>(&argument_.entropy),
            "The Base16 entropy for the shares, of a size determined by the groups and secret. If not specified the entropy is read from STDIN."
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
     * Get the value of the ENTROPY argument.
     */
    virtual system::config::base16& get_entropy_argument()
    {
        return argument_.entropy;
    }

    /**
     * Set the value of the ENTROPY argument.
     */
    virtual void set_entropy_argument(
        const system::config::base16& value)
    {
        argument_.entropy = value;
    }

    /**
     * Get the value of the exponent option.
     */
    virtual uint8_t& get_exponent_option()
    {
        return option_.exponent;
    }

    /**
     * Set the value of the exponent option.
     */
    virtual void set_exponent_option(
        const uint8_t& value)
    {
        option_.exponent = value;
    }

    /**
     * Get the value of the extendable option.
     */
    virtual bool& get_extendable_option()
    {
        return option_.extendable;
    }

    /**
     * Set the value of the extendable option.
     */
    virtual void set_extendable_option(
        const bool& value)
    {
        option_.extendable = value;
    }

    /**
     * Get the value of the group options.
     */
    virtual std::vector<explorer::config::group>& get_groups_option()
    {
        return option_.groups;
    }

    /**
     * Set the value of the group options.
     */
    virtual void set_groups_option(
        const std::vector<explorer::config::group>& value)
    {
        option_.groups = value;
    }

    /**
     * Get the value of the identifier option.
     */
    virtual uint16_t& get_identifier_option()
    {
        return option_.identifier;
    }

    /**
     * Set the value of the identifier option.
     */
    virtual void set_identifier_option(
        const uint16_t& value)
    {
        option_.identifier = value;
    }

    /**
     * Get the value of the passphrase option.
     */
    virtual std::string& get_passphrase_option()
    {
        return option_.passphrase;
    }

    /**
     * Set the value of the passphrase option.
     */
    virtual void set_passphrase_option(
        const std::string& value)
    {
        option_.passphrase = value;
    }

    /**
     * Get the value of the secret option.
     */
    virtual system::config::base16& get_secret_option()
    {
        return option_.secret;
    }

    /**
     * Set the value of the secret option.
     */
    virtual void set_secret_option(
        const system::config::base16& value)
    {
        option_.secret = value;
    }

    /**
     * Get the value of the threshold option.
     */
    virtual uint8_t& get_threshold_option()
    {
        return option_.threshold;
    }

    /**
     * Set the value of the threshold option.
     */
    virtual void set_threshold_option(
        const uint8_t& value)
    {
        option_.threshold = value;
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
          : entropy()
        {
        }

        system::config::base16 entropy;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : exponent(),
            extendable(),
            groups(),
            identifier(),
            passphrase(),
            secret(),
            threshold()
        {
        }

        uint8_t exponent;
        bool extendable;
        std::vector<explorer::config::group> groups;
        uint16_t identifier;
        std::string passphrase;
        system::config::base16 secret;
        uint8_t threshold;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
