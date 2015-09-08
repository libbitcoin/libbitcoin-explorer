/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
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
#ifndef BX_MNEMONIC_TO_SEED_HPP
#define BX_MNEMONIC_TO_SEED_HPP

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
#include <bitcoin/explorer/primitives/base85.hpp>
#include <bitcoin/explorer/primitives/btc.hpp>
#include <bitcoin/explorer/primitives/btc160.hpp>
#include <bitcoin/explorer/primitives/btc256.hpp>
#include <bitcoin/explorer/primitives/byte.hpp>
#include <bitcoin/explorer/primitives/cert_key.hpp>
#include <bitcoin/explorer/primitives/ec_private.hpp>
#include <bitcoin/explorer/primitives/ec_public.hpp>
#include <bitcoin/explorer/primitives/ek_private.hpp>
#include <bitcoin/explorer/primitives/ek_public.hpp>
#include <bitcoin/explorer/primitives/ek_token.hpp>
#include <bitcoin/explorer/primitives/encoding.hpp>
#include <bitcoin/explorer/primitives/endorsement.hpp>
#include <bitcoin/explorer/primitives/hashtype.hpp>
#include <bitcoin/explorer/primitives/hd_key.hpp>
#include <bitcoin/explorer/primitives/hd_priv.hpp>
#include <bitcoin/explorer/primitives/hd_pub.hpp>
#include <bitcoin/explorer/primitives/header.hpp>
#include <bitcoin/explorer/primitives/input.hpp>
#include <bitcoin/explorer/primitives/language.hpp>
#include <bitcoin/explorer/primitives/output.hpp>
#include <bitcoin/explorer/primitives/point.hpp>
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
#define BX_EC_MNEMONIC_TO_SEED_LENGTH_INVALID_SENTENCE \
    "The number of words must be divisible by 3."
#define BX_EC_MNEMONIC_TO_SEED_PASSPHRASE_UNSUPPORTED \
    "The passphrase option requires an ICU build."
#define BX_EC_MNEMONIC_TO_SEED_INVALID_IN_LANGUAGE \
    "The specified words are not a valid mnemonic in the specified dictionary."
#define BX_EC_MNEMONIC_TO_SEED_INVALID_IN_LANGUAGES \
    "WARNING: The specified words are not a valid mnemonic in any supported dictionary."

/**
 * Class to implement the mnemonic-to-seed command.
 */
class mnemonic_to_seed 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    BCX_API static const char* symbol()
    {
        return "mnemonic-to-seed";
    }


    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    BCX_API virtual const char* name()
    {
        return mnemonic_to_seed::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    BCX_API virtual const char* category()
    {
        return "WALLET";
    }

    /**
     * The localizable command description.
     */
    BCX_API virtual const char* description()
    {
        return "Convert a mnemonic seed (BIP39) to its numeric representation.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    BCX_API virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("WORD", -1);
    }

	/**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    BCX_API virtual void load_fallbacks(std::istream& input, 
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
            "language,l",
            value<primitives::language>(&option_.language),
            "The language identifier of the dictionary of the mnemonic. Options are 'en', 'es', 'ja', 'zh_Hans', 'zh_Hant' and 'any', defaults to 'any'."
        )
        (
            "passphrase,p",
            value<std::string>(&option_.passphrase),
            "An optional passphrase for converting the mnemonic to a seed."
        )
        (
            "WORD",
            value<std::vector<std::string>>(&argument_.words),
            "The set of words that that make up the mnemonic. If not specified the words are read from STDIN."
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
     * Get the value of the WORD arguments.
     */
    BCX_API virtual std::vector<std::string>& get_words_argument()
    {
        return argument_.words;
    }

    /**
     * Set the value of the WORD arguments.
     */
    BCX_API virtual void set_words_argument(
        const std::vector<std::string>& value)
    {
        argument_.words = value;
    }

    /**
     * Get the value of the language option.
     */
    BCX_API virtual primitives::language& get_language_option()
    {
        return option_.language;
    }

    /**
     * Set the value of the language option.
     */
    BCX_API virtual void set_language_option(
        const primitives::language& value)
    {
        option_.language = value;
    }

    /**
     * Get the value of the passphrase option.
     */
    BCX_API virtual std::string& get_passphrase_option()
    {
        return option_.passphrase;
    }

    /**
     * Set the value of the passphrase option.
     */
    BCX_API virtual void set_passphrase_option(
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
          : language(),
            passphrase()
        {
        }

        primitives::language language;
        std::string passphrase;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
