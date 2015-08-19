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
#ifndef BX_EC_LOCK_HPP
#define BX_EC_LOCK_HPP

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
#define BX_EC_LOCK_PRIVKEY_LENGTH_INVALID \
    "The specified private key is invalid."
#define BX_EC_LOCK_MODE_INCORRECT \
    "Either passphrase or intermediate mode can be specified, but not both."
#define BX_EC_LOCK_INTERMEDIATE_LENGTH_INVALID \
    "The specified intermediate is invalid."
#define BX_EC_LOCK_INTERMEDIATE_MORE_REQUIRED \
    "When using an intermediate, both an intermediate and the seed are required."
#define BX_EC_LOCK_SEED_NOT_REQUIRED \
    "The specified seed is not required when using a passphrase."
#define BX_EC_LOCK_SEED_LENGTH_INVALID \
    "The seed is required to be 24 bytes in length."
#define BX_EC_LOCK_USING_PASSPHRASE_UNSUPPORTED \
    "The passphrase option requires an ICU build."

/**
 * Class to implement the ec-lock command.
 */
class ec_lock 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    BCX_API static const char* symbol()
    {
        return "ec-lock";
    }

    /**
     * The symbolic (not localizable) former command name, lower case.
     */
    BCX_API static const char* formerly()
    {
        return "brainwallet";
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    BCX_API virtual const char* name()
    {
        return ec_lock::symbol();
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
        return "Make a passphrase-protected EC private key (BIP38) from an EC private key.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    BCX_API virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("EC_PRIVATE_KEY", 1)
            .add("passphrase", 1)
            .add("intermediate", 1)
            .add("seed", 1)
            .add("compress", 1)
            .add("confirm", 1);
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
        load_input(get_ec_private_key_argument(), "EC_PRIVATE_KEY", variables, input, raw);
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
            "EC_PRIVATE_KEY",
            value<primitives::ec_private>(&argument_.ec_private_key),
            "The Base16 EC private key."
        )
        (
            "passphrase",
            value<std::string>(&argument_.passphrase),
            "The Unicode passphrase."
        )
        (
            "intermediate",
            value<primitives::base58>(&argument_.intermediate),
            "The base58 checked Intermediate."
        )
        (
            "seed",
            value<primitives::base16>(&argument_.seed),
            "24 bytes of random data used in the bip38 process (required if locking with an intermediate instead of a passphrase)."
        )
        (
            "compress",
            value<primitives::byte>(&argument_.compress),
            "Specify '1' if the key should be converted to a bitcoin address using the compressed public key format."
        )
        (
            "confirm",
            value<primitives::byte>(&argument_.confirm),
            "Specify '1' if the confirmation code generated when locking with an intermediate should be displayed"
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
     * Get the value of the EC_PRIVATE_KEY argument.
     */
    BCX_API virtual primitives::ec_private& get_ec_private_key_argument()
    {
        return argument_.ec_private_key;
    }

    /**
     * Set the value of the EC_PRIVATE_KEY argument.
     */
    BCX_API virtual void set_ec_private_key_argument(
        const primitives::ec_private& value)
    {
        argument_.ec_private_key = value;
    }

    /**
     * Get the value of the passphrase argument.
     */
    BCX_API virtual std::string& get_passphrase_argument()
    {
        return argument_.passphrase;
    }

    /**
     * Set the value of the passphrase argument.
     */
    BCX_API virtual void set_passphrase_argument(
        const std::string& value)
    {
        argument_.passphrase = value;
    }

    /**
     * Get the value of the intermediate argument.
     */
    BCX_API virtual primitives::base58& get_intermediate_argument()
    {
        return argument_.intermediate;
    }

    /**
     * Set the value of the intermediate argument.
     */
    BCX_API virtual void set_intermediate_argument(
        const primitives::base58& value)
    {
        argument_.intermediate = value;
    }

    /**
     * Get the value of the seed argument.
     */
    BCX_API virtual primitives::base16& get_seed_argument()
    {
        return argument_.seed;
    }

    /**
     * Set the value of the seed argument.
     */
    BCX_API virtual void set_seed_argument(
        const primitives::base16& value)
    {
        argument_.seed = value;
    }

    /**
     * Get the value of the compress argument.
     */
    BCX_API virtual primitives::byte& get_compress_argument()
    {
        return argument_.compress;
    }

    /**
     * Set the value of the compress argument.
     */
    BCX_API virtual void set_compress_argument(
        const primitives::byte& value)
    {
        argument_.compress = value;
    }

    /**
     * Get the value of the confirm argument.
     */
    BCX_API virtual primitives::byte& get_confirm_argument()
    {
        return argument_.confirm;
    }

    /**
     * Set the value of the confirm argument.
     */
    BCX_API virtual void set_confirm_argument(
        const primitives::byte& value)
    {
        argument_.confirm = value;
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
          : ec_private_key(),
            passphrase(),
            intermediate(),
            seed(),
            compress(),
            confirm()
        {
        }

        primitives::ec_private ec_private_key;
        std::string passphrase;
        primitives::base58 intermediate;
        primitives::base16 seed;
        primitives::byte compress;
        primitives::byte confirm;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
        {
        }

    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
