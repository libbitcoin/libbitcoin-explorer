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
#ifndef BX_HD_PUBLIC_HPP
#define BX_HD_PUBLIC_HPP

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
#include <bitcoin/explorer/primitives/btc.hpp>
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
#define BX_HD_PUBLIC_HARD_OPTION_CONFLICT \
    "The hard option requires a private key."

/**
 * Class to implement the hd-public command.
 */
class BCX_API hd_public 
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "hd-public";
    }


    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return hd_public::symbol();
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
        return "Derive a child HD (BIP32) public key from another HD public or private key.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("HD_KEY", 1);
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
        load_input(get_hd_key_argument(), "HD_KEY", variables, input, raw);
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
            "hard,d",
            value<bool>(&option_.hard)->zero_tokens(),
            "Signal to create a hardened key."
        )
        (
            "index,i",
            value<uint32_t>(&option_.index),
            "The HD index, defaults to 0."
        )
        (
            "secret_version,s",
            value<uint32_t>(&option_.secret_version)->default_value(76066276),
            "The expected version for an HD private key, defaults to 76066276."
        )
        (
            "public_version,p",
            value<uint32_t>(&option_.public_version)->default_value(76067358),
            "The expected version for an HD public key, defaults to 76067358."
        )
        (
            "HD_KEY",
            value<primitives::hd_key>(&argument_.hd_key),
            "The parent HD public or private key. If not specified the key is read from STDIN."
        );

        return options;
    }

    /**
     * Set variable defaults from configuration variable values.
     * @param[in]  variables  The loaded variables.
     */
    virtual void set_defaults_from_config(po::variables_map& variables)
    {
        const auto& option_secret_version = variables["secret_version"];
        const auto& option_secret_version_config = variables["wallet.hd_secret_version"];
        if (option_secret_version.defaulted() && !option_secret_version_config.defaulted())
        {
            option_.secret_version = option_secret_version_config.as<uint32_t>();
        }

        const auto& option_public_version = variables["public_version"];
        const auto& option_public_version_config = variables["wallet.hd_public_version"];
        if (option_public_version.defaulted() && !option_public_version_config.defaulted())
        {
            option_.public_version = option_public_version_config.as<uint32_t>();
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
     * Get the value of the HD_KEY argument.
     */
    virtual primitives::hd_key& get_hd_key_argument()
    {
        return argument_.hd_key;
    }

    /**
     * Set the value of the HD_KEY argument.
     */
    virtual void set_hd_key_argument(
        const primitives::hd_key& value)
    {
        argument_.hd_key = value;
    }

    /**
     * Get the value of the hard option.
     */
    virtual bool& get_hard_option()
    {
        return option_.hard;
    }

    /**
     * Set the value of the hard option.
     */
    virtual void set_hard_option(
        const bool& value)
    {
        option_.hard = value;
    }

    /**
     * Get the value of the index option.
     */
    virtual uint32_t& get_index_option()
    {
        return option_.index;
    }

    /**
     * Set the value of the index option.
     */
    virtual void set_index_option(
        const uint32_t& value)
    {
        option_.index = value;
    }

    /**
     * Get the value of the secret_version option.
     */
    virtual uint32_t& get_secret_version_option()
    {
        return option_.secret_version;
    }

    /**
     * Set the value of the secret_version option.
     */
    virtual void set_secret_version_option(
        const uint32_t& value)
    {
        option_.secret_version = value;
    }

    /**
     * Get the value of the public_version option.
     */
    virtual uint32_t& get_public_version_option()
    {
        return option_.public_version;
    }

    /**
     * Set the value of the public_version option.
     */
    virtual void set_public_version_option(
        const uint32_t& value)
    {
        option_.public_version = value;
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
          : hd_key()
        {
        }

        primitives::hd_key hd_key;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : hard(),
            index(),
            secret_version(),
            public_version()
        {
        }

        bool hard;
        uint32_t index;
        uint32_t secret_version;
        uint32_t public_version;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
