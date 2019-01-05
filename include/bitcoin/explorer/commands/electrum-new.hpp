/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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
#ifndef BX_ELECTRUM_NEW_HPP
#define BX_ELECTRUM_NEW_HPP

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
#include <bitcoin/explorer/config/electrum.hpp>
#include <bitcoin/explorer/config/encoding.hpp>
#include <bitcoin/explorer/config/endorsement.hpp>
#include <bitcoin/explorer/config/hashtype.hpp>
#include <bitcoin/explorer/config/hd_key.hpp>
#include <bitcoin/explorer/config/language.hpp>
#include <bitcoin/explorer/config/raw.hpp>
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
#define BX_ELECTRUM_NEW_INVALID_SEED \
    "The seed size is not supported."
#define BX_ELECTRUM_REQUIRES_ICU \
    "The command requires an ICU build."

/**
 * Class to implement the electrum-new command.
 */
class BCX_API electrum_new
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "electrum-new";
    }


    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return electrum_new::symbol();
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
        return "Create a mnemonic seed (Electrum) from entropy. WARNING: mnemonic should be created from properly generated entropy.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual system::arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("SEED", 1);
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
        load_input(get_seed_argument(), "SEED", variables, input, raw);
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
            "prefix,p",
            value<explorer::config::electrum>(&option_.prefix),
            "The electrum seed type identifier to use. Options are 'standard', 'witness', and 'dual' (for two factor authentication), defaults to 'standard'."
        )
        (
            "language,l",
            value<explorer::config::language>(&option_.language),
            "The language identifier of the mnemonic dictionary to use. Options are 'en', 'es', 'pt', 'ja', 'zh_Hans' and 'any', defaults to 'en'."
        )
        (
            "SEED",
            value<system::config::base16>(&argument_.seed),
            "The Base16 entropy from which the mnemonic is created. If not specified the entropy is read from STDIN."
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
     * Get the value of the SEED argument.
     */
    virtual system::config::base16& get_seed_argument()
    {
        return argument_.seed;
    }

    /**
     * Set the value of the SEED argument.
     */
    virtual void set_seed_argument(
        const system::config::base16& value)
    {
        argument_.seed = value;
    }

    /**
     * Get the value of the prefix option.
     */
    virtual explorer::config::electrum& get_prefix_option()
    {
        return option_.prefix;
    }

    /**
     * Set the value of the prefix option.
     */
    virtual void set_prefix_option(
        const explorer::config::electrum& value)
    {
        option_.prefix = value;
    }

    /**
     * Get the value of the language option.
     */
    virtual explorer::config::language& get_language_option()
    {
        return option_.language;
    }

    /**
     * Set the value of the language option.
     */
    virtual void set_language_option(
        const explorer::config::language& value)
    {
        option_.language = value;
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
          : seed()
        {
        }

        system::config::base16 seed;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : prefix(),
            language()
        {
        }

        explorer::config::electrum prefix;
        explorer::config::language language;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
