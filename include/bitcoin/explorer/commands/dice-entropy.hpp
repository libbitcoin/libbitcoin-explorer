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
#ifndef BX_DICE_ENTROPY_HPP
#define BX_DICE_ENTROPY_HPP

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
#include <bitcoin/explorer/config/hd_key.hpp>
#include <bitcoin/explorer/config/language.hpp>
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
#define BX_DICE_SIDES_INVALID \
    "The number of sides is not between 2 and 16."
#define BX_DICE_ROLLS_INVALID \
    "The dice roll input is invalid."
#define BX_DICE_ROLLS_REJECTED \
    "The rolls would bias the entropy, roll again."

/**
 * Class to implement the dice-entropy command.
 */
class BCX_API dice_entropy
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "dice-entropy";
    }

    /**
     * Destructor.
     */
    virtual ~dice_entropy()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return dice_entropy::symbol();
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
        return "Convert a sequence of dice rolls to Base16 entropy. Each roll is one character, the face value 0 to 15 as a hexadecimal digit, so the rolls of a sixteen-sided die are their own Base16 encoding. Subtract one from each roll of a die with faces numbered from one, writing a six-sided roll of 1 to 6 as 0 to 5.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("rolls", 1);
    }

    /**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input      The input stream for loading the parameters.
     * @param[in]  variables  The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input,
        po::variables_map& variables)
    {
        load_input(get_rolls_argument(), "rolls", variables, input);
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
            "sides,s",
            value<uint8_t>(&option_.sides)->default_value(6),
            "The number of sides on the die, 2 to 16, defaults to 6."
        )
        (
            "rolls",
            value<std::string>(&argument_.rolls),
            "The sequence of dice rolls, one character per roll. The entropy is the whole bytes the rolls provide. A sequence that would bias the entropy is rejected and must be rolled again. If not specified the rolls are read from STDIN."
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
     * Get the value of the rolls argument.
     */
    virtual std::string& get_rolls_argument()
    {
        return argument_.rolls;
    }

    /**
     * Set the value of the rolls argument.
     */
    virtual void set_rolls_argument(
        const std::string& value)
    {
        argument_.rolls = value;
    }

    /**
     * Get the value of the sides option.
     */
    virtual uint8_t& get_sides_option()
    {
        return option_.sides;
    }

    /**
     * Set the value of the sides option.
     */
    virtual void set_sides_option(
        const uint8_t& value)
    {
        option_.sides = value;
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
          : rolls()
        {
        }

        std::string rolls;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : sides()
        {
        }

        uint8_t sides;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
