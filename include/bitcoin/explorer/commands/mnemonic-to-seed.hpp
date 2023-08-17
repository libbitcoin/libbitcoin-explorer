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
#ifndef BX_MNEMONIC_TO_SEED_HPP
#define BX_MNEMONIC_TO_SEED_HPP

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
#include <bitcoin/explorer/config/dictionary.hpp>
#include <bitcoin/explorer/config/ec_private.hpp>
#include <bitcoin/explorer/config/electrum.hpp>
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
 * Various localizable strings.
 */
#define BX_MNEMONIC_TO_SEED_INVALID_LANGUAGES \
    "The specified words are not a valid mnemonic in any specified dictionary."
#define BX_MNEMONIC_TO_SEED_INVALID_SENTENCE \
    "The word count must be evenly divisible by 3."
#define BX_MNEMONIC_TO_SEED_PASSPHRASE_REQUIRES_ICU \
    "The passphrase option requires an ICU build."
#define BX_MNEMONIC_TO_SEED_UNSAFE_SENTENCE \
    "The word count must be at least 12."

/**
 * Class to implement the mnemonic-to-seed command.
 */
class BCX_API mnemonic_to_seed
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "mnemonic-to-seed";
    }


    /**
     * Destructor.
     */
    virtual ~mnemonic_to_seed()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return mnemonic_to_seed::symbol();
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
        return "Convert a mnemonic seed (BIP39) to its numeric representation.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("WORD", -1);
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
        load_input(get_words_argument(), "WORD", variables, input, raw);
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
            "language,l",
            value<std::vector<explorer::config::language>>(&option_.languages),
            "The optional language identifiers of mnemonic dictionaries against which to validate. Options are 'en', 'es', 'fr', 'it', 'cs', 'pt', 'ja', 'ko', 'zh_Hans', and 'zh_Hant', defaults to none. Multiple tokens must be quoted."
        )
        (
            "passphrase,p",
            value<std::string>(&option_.passphrase),
            "An optional passphrase for converting the mnemonic to a seed."
        )
        (
            "WORD",
            value<std::vector<std::string>>(&argument_.words),
            "At least 12 words evenly disible by 3 that that make up the mnemonic. If not specified the words are read from STDIN."
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
     * Get the value of the WORD arguments.
     */
    virtual std::vector<std::string>& get_words_argument()
    {
        return argument_.words;
    }

    /**
     * Set the value of the WORD arguments.
     */
    virtual void set_words_argument(
        const std::vector<std::string>& value)
    {
        argument_.words = value;
    }

    /**
     * Get the value of the language options.
     */
    virtual std::vector<explorer::config::language>& get_languages_option()
    {
        return option_.languages;
    }

    /**
     * Set the value of the language options.
     */
    virtual void set_languages_option(
        const std::vector<explorer::config::language>& value)
    {
        option_.languages = value;
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

private:

    /**
     * Command line argument bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct argument
    {
        argument()
          : words()
        {
        }

        std::vector<std::string> words;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : languages(),
            passphrase()
        {
        }

        std::vector<explorer::config::language> languages;
        std::string passphrase;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
