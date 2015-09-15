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
#ifndef BX_TOKEN_NEW_HPP
#define BX_TOKEN_NEW_HPP

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
#define BX_TOKEN_NEW_MAXIMUM_LOT \
    "The lot exceeds the maximum value of 1048575."
#define BX_TOKEN_NEW_MAXIMUM_SEQUENCE \
    "The sequence exceeds the maximum value of 4095."
#define BX_TOKEN_NEW_SHORT_SALT \
    "The salt is less than 32 bits long."
#define BX_TOKEN_NEW_REQUIRES_ICU \
    "The command requires an ICU build."

/**
 * Class to implement the token-new command.
 */
class token_new 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    BCX_API static const char* symbol()
    {
        return "token-new";
    }


    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    BCX_API virtual const char* name()
    {
        return token_new::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    BCX_API virtual const char* category()
    {
        return "KEY_ENCRYPTION";
    }

    /**
     * The localizable command description.
     */
    BCX_API virtual const char* description()
    {
        return "Create an intermediate passphrase token for deferred encrypted key generation (BIP38).";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    BCX_API virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("PASSPHRASE", 1)
            .add("SALT", 1);
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
        load_input(get_salt_argument(), "SALT", variables, input, raw);
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
            "lot,l",
            value<uint32_t>(&option_.lot),
            "An arbitrary lot number, limited to 1048575."
        )
        (
            "sequence,s",
            value<uint32_t>(&option_.sequence),
            "An arbitrary sequence number, limited to 4095."
        )
        (
            "PASSPHRASE",
            value<std::string>(&argument_.passphrase)->required(),
            "The passphrase for encrypting the token."
        )
        (
            "SALT",
            value<primitives::base16>(&argument_.salt),
            "The Base16 entropy for the new token. Must be at least 32 bits in length. Only the first 32 bits are used unless lot and sequence are zero or unspecified and the salt is at least 64 bits, in which case 64 bits are used and lot and sequence are not used. If not specified the salt is read from STDIN."
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
     * Get the value of the PASSPHRASE argument.
     */
    BCX_API virtual std::string& get_passphrase_argument()
    {
        return argument_.passphrase;
    }

    /**
     * Set the value of the PASSPHRASE argument.
     */
    BCX_API virtual void set_passphrase_argument(
        const std::string& value)
    {
        argument_.passphrase = value;
    }

    /**
     * Get the value of the SALT argument.
     */
    BCX_API virtual primitives::base16& get_salt_argument()
    {
        return argument_.salt;
    }

    /**
     * Set the value of the SALT argument.
     */
    BCX_API virtual void set_salt_argument(
        const primitives::base16& value)
    {
        argument_.salt = value;
    }

    /**
     * Get the value of the lot option.
     */
    BCX_API virtual uint32_t& get_lot_option()
    {
        return option_.lot;
    }

    /**
     * Set the value of the lot option.
     */
    BCX_API virtual void set_lot_option(
        const uint32_t& value)
    {
        option_.lot = value;
    }

    /**
     * Get the value of the sequence option.
     */
    BCX_API virtual uint32_t& get_sequence_option()
    {
        return option_.sequence;
    }

    /**
     * Set the value of the sequence option.
     */
    BCX_API virtual void set_sequence_option(
        const uint32_t& value)
    {
        option_.sequence = value;
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
          : passphrase(),
            salt()
        {
        }

        std::string passphrase;
        primitives::base16 salt;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : lot(),
            sequence()
        {
        }

        uint32_t lot;
        uint32_t sequence;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
