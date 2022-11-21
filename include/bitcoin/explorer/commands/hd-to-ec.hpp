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
#ifndef BX_HD_TO_EC_HPP
#define BX_HD_TO_EC_HPP

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
#include <bitcoin/explorer/config/bytes.hpp>
#include <bitcoin/explorer/config/electrum.hpp>
#include <bitcoin/explorer/config/encoding.hpp>
#include <bitcoin/explorer/config/endorsement.hpp>
#include <bitcoin/explorer/config/hd_key.hpp>
#include <bitcoin/explorer/config/language.hpp>
#include <bitcoin/explorer/config/sighash.hpp>
#include <bitcoin/explorer/config/signature.hpp>
#include <bitcoin/explorer/config/witness.hpp>
#include <bitcoin/explorer/config/wrapper.hpp>
#include <bitcoin/protocol/zmq/sodium.hpp>
#include <bitcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
namespace commands {

/**
 * Various localizable strings.
 */
#define BX_HD_TO_EC_INVALID_KEY \
    "The key is invalid."
#define HD_TO_EC_VERSION_MISMATCH \
    "The version options are inconsistent."

/**
 * Class to implement the hd-to-ec command.
 */
class BCX_API hd_to_ec
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "hd-to-ec";
    }

    /**
     * Destructor.
     */
    virtual ~hd_to_ec()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return hd_to_ec::symbol();
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
        return "Convert a HD (BIP32) public or private key to the equivalent EC public or private key.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual system::arguments_metadata& load_arguments()
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
            value<explorer::config::hd_key>(&argument_.hd_key),
            "The HD public or private key to convert. If not specified the key is read from STDIN."
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
    virtual system::console_result invoke(std::ostream& output,
        std::ostream& cerr);

    /* Properties */

    /**
     * Get the value of the HD_KEY argument.
     */
    virtual explorer::config::hd_key& get_hd_key_argument()
    {
        return argument_.hd_key;
    }

    /**
     * Set the value of the HD_KEY argument.
     */
    virtual void set_hd_key_argument(
        const explorer::config::hd_key& value)
    {
        argument_.hd_key = value;
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

        explorer::config::hd_key hd_key;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : secret_version(),
            public_version()
        {
        }

        uint32_t secret_version;
        uint32_t public_version;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
