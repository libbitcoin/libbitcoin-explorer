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
#ifndef BX_EK_PUBLIC_HPP
#define BX_EK_PUBLIC_HPP

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
#include <bitcoin/explorer/primitives/algorithm.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>
#include <bitcoin/explorer/primitives/base2.hpp>
#include <bitcoin/explorer/primitives/base58.hpp>
#include <bitcoin/explorer/primitives/base64.hpp>
#include <bitcoin/explorer/primitives/base85.hpp>
#include <bitcoin/explorer/primitives/btc.hpp>
#include <bitcoin/explorer/primitives/btc160.hpp>
#include <bitcoin/explorer/primitives/byte.hpp>
#include <bitcoin/explorer/primitives/cert_key.hpp>
#include <bitcoin/explorer/primitives/ec_private.hpp>
#include <bitcoin/explorer/primitives/encoding.hpp>
#include <bitcoin/explorer/primitives/endorsement.hpp>
#include <bitcoin/explorer/primitives/hashtype.hpp>
#include <bitcoin/explorer/primitives/hd_key.hpp>
#include <bitcoin/explorer/primitives/header.hpp>
#include <bitcoin/explorer/primitives/input.hpp>
#include <bitcoin/explorer/primitives/language.hpp>
#include <bitcoin/explorer/primitives/output.hpp>
#include <bitcoin/explorer/primitives/raw.hpp>
#include <bitcoin/explorer/primitives/script.hpp>
#include <bitcoin/explorer/primitives/signature.hpp>
#include <bitcoin/explorer/primitives/transaction.hpp>
#include <bitcoin/explorer/primitives/wrapper.hpp>
#include <bitcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
namespace commands {

/**
 * Various localizable strings.
 */
#define BX_EK_PUBLIC_SHORT_SEED \
    "The seed is less than 192 bits long."

/**
 * Class to implement the ek-public command.
 */
class BCX_API ek_public 
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "ek-public";
    }


    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return ek_public::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "KEY_ENCRYPTION";
    }

    /**
     * The localizable command description.
     */
    virtual const char* description()
    {
        return "Create an encrypted public key from an intermediate passphrase token (BIP38).";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("TOKEN", 1)
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
            "uncompressed,u",
            value<bool>(&option_.uncompressed)->zero_tokens(),
            "Use the uncompressed public key format, as used to create the corresponding encrypted private key."
        )
        (
            "version,v",
            value<primitives::byte>(&option_.version)->default_value(0),
            "The desired payment address version used to create the corresponding encrypted private key."
        )
        (
            "TOKEN",
            value<bc::wallet::ek_token>(&argument_.token)->required(),
            "The intermediate passphrase token used to create the corresponding encrypted private key."
        )
        (
            "SEED",
            value<primitives::base16>(&argument_.seed),
            "The Base16 entropy for the new encrypted public key. Must be at least 192 bits in length (only the first 192 bits are used). If not specified the seed is read from STDIN."
        );

        return options;
    }

    /**
     * Set variable defaults from configuration variable values.
     * @param[in]  variables  The loaded variables.
     */
    virtual void set_defaults_from_config(po::variables_map& variables)
    {
        const auto& option_version = variables["version"];
        const auto& option_version_config = variables["wallet.pay_to_public_key_hash_version"];
        if (option_version.defaulted() && !option_version_config.defaulted())
        {
            option_.version = option_version_config.as<primitives::byte>();
        }
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
     * Get the value of the TOKEN argument.
     */
    virtual bc::wallet::ek_token& get_token_argument()
    {
        return argument_.token;
    }

    /**
     * Set the value of the TOKEN argument.
     */
    virtual void set_token_argument(
        const bc::wallet::ek_token& value)
    {
        argument_.token = value;
    }

    /**
     * Get the value of the SEED argument.
     */
    virtual primitives::base16& get_seed_argument()
    {
        return argument_.seed;
    }

    /**
     * Set the value of the SEED argument.
     */
    virtual void set_seed_argument(
        const primitives::base16& value)
    {
        argument_.seed = value;
    }

    /**
     * Get the value of the uncompressed option.
     */
    virtual bool& get_uncompressed_option()
    {
        return option_.uncompressed;
    }

    /**
     * Set the value of the uncompressed option.
     */
    virtual void set_uncompressed_option(
        const bool& value)
    {
        option_.uncompressed = value;
    }

    /**
     * Get the value of the version option.
     */
    virtual primitives::byte& get_version_option()
    {
        return option_.version;
    }

    /**
     * Set the value of the version option.
     */
    virtual void set_version_option(
        const primitives::byte& value)
    {
        option_.version = value;
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
          : token(),
            seed()
        {
        }

        bc::wallet::ek_token token;
        primitives::base16 seed;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : uncompressed(),
            version()
        {
        }

        bool uncompressed;
        primitives::byte version;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
