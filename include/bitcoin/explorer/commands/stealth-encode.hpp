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
#ifndef BX_STEALTH_ENCODE_HPP
#define BX_STEALTH_ENCODE_HPP

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
#define BX_STEALTH_ENCODE_FILTER_TOO_LONG \
    "The filter is limited to 32 bits."
#define BX_STEALTH_ENCODE_SIGNATURES_OVERFLOW \
    "The number of signatures is greater than the number of SPEND_PUBKEYs."
#define BX_STEALTH_ENCODE_MULTISIG_NOT_SUPPORTED \
    "WARNING: multiple signature stealth transactions are not yet fully supported."

/**
 * Class to implement the stealth-encode command.
 */
class BCX_API stealth_encode 
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "stealth-encode";
    }


    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return stealth_encode::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "STEALTH";
    }

    /**
     * The localizable command description.
     */
    virtual const char* description()
    {
        return "Encode a stealth payment address.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("SCAN_PUBKEY", 1)
            .add("SPEND_PUBKEY", -1);
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
            "filter,f",
            value<primitives::base2>(&option_.filter),
            "The Base2 stealth prefix filter that will be used to locate payments."
        )
        (
            "signatures,s",
            value<primitives::byte>(&option_.signatures),
            "The number of signatures required to spend a payment to the stealth address. Defaults to the number of SPEND_PUBKEYs."
        )
        (
            "version,v",
            value<primitives::byte>(&option_.version)->default_value(0),
            "The desired payment address version, defaults to 0."
        )
        (
            "SCAN_PUBKEY",
            value<bc::wallet::ec_public>(&argument_.scan_pubkey)->required(),
            "The Base16 EC public key required to create a payment."
        )
        (
            "SPEND_PUBKEY",
            value<std::vector<bc::wallet::ec_public>>(&argument_.spend_pubkeys),
            "The set of Base16 EC public keys corresponding to private keys that will be able to spend payments to the address. Defaults to the value of SCAN_PUBKEY."
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
     * Get the value of the SCAN_PUBKEY argument.
     */
    virtual bc::wallet::ec_public& get_scan_pubkey_argument()
    {
        return argument_.scan_pubkey;
    }

    /**
     * Set the value of the SCAN_PUBKEY argument.
     */
    virtual void set_scan_pubkey_argument(
        const bc::wallet::ec_public& value)
    {
        argument_.scan_pubkey = value;
    }

    /**
     * Get the value of the SPEND_PUBKEY arguments.
     */
    virtual std::vector<bc::wallet::ec_public>& get_spend_pubkeys_argument()
    {
        return argument_.spend_pubkeys;
    }

    /**
     * Set the value of the SPEND_PUBKEY arguments.
     */
    virtual void set_spend_pubkeys_argument(
        const std::vector<bc::wallet::ec_public>& value)
    {
        argument_.spend_pubkeys = value;
    }

    /**
     * Get the value of the filter option.
     */
    virtual primitives::base2& get_filter_option()
    {
        return option_.filter;
    }

    /**
     * Set the value of the filter option.
     */
    virtual void set_filter_option(
        const primitives::base2& value)
    {
        option_.filter = value;
    }

    /**
     * Get the value of the signatures option.
     */
    virtual primitives::byte& get_signatures_option()
    {
        return option_.signatures;
    }

    /**
     * Set the value of the signatures option.
     */
    virtual void set_signatures_option(
        const primitives::byte& value)
    {
        option_.signatures = value;
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
          : scan_pubkey(),
            spend_pubkeys()
        {
        }

        bc::wallet::ec_public scan_pubkey;
        std::vector<bc::wallet::ec_public> spend_pubkeys;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : filter(),
            signatures(),
            version()
        {
        }

        primitives::base2 filter;
        primitives::byte signatures;
        primitives::byte version;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
