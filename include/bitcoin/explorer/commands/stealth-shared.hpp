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
#ifndef BX_STEALTH_SHARED_HPP
#define BX_STEALTH_SHARED_HPP

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
#define BX_STEALTH_SHARED_OUT_OF_RANGE \
    "Product exceeds valid range."

/**
 * Class to implement the stealth-shared command.
 */
class BCX_API stealth_shared
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "stealth-shared";
    }

    /**
     * Destructor.
     */
    virtual ~stealth_shared()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return stealth_shared::symbol();
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
        return "Derive the secret shared between an ephemeral key pair and a scan key pair. Provide scan SECRET and ephemeral PUBKEY, or ephemeral SECRET and scan PUBKEY.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual system::arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("SECRET", 1)
            .add("PUBKEY", 1);
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
        load_input(get_pubkey_argument(), "PUBKEY", variables, input, raw);
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
            "SECRET",
            value<system::wallet::ec_private>(&argument_.secret)->required(),
            "A Base16 EC private key. Either the scan or ephemeral secret."
        )
        (
            "PUBKEY",
            value<system::wallet::ec_public>(&argument_.pubkey),
            "A Base16 EC public key. Either the scan or ephemeral public key. If not specified the key is read from STDIN."
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
     * Get the value of the SECRET argument.
     */
    virtual system::wallet::ec_private& get_secret_argument()
    {
        return argument_.secret;
    }

    /**
     * Set the value of the SECRET argument.
     */
    virtual void set_secret_argument(
        const system::wallet::ec_private& value)
    {
        argument_.secret = value;
    }

    /**
     * Get the value of the PUBKEY argument.
     */
    virtual system::wallet::ec_public& get_pubkey_argument()
    {
        return argument_.pubkey;
    }

    /**
     * Set the value of the PUBKEY argument.
     */
    virtual void set_pubkey_argument(
        const system::wallet::ec_public& value)
    {
        argument_.pubkey = value;
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
          : secret(),
            pubkey()
        {
        }

        system::wallet::ec_private secret;
        system::wallet::ec_public pubkey;
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
