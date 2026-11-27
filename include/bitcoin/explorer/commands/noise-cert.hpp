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
#ifndef BX_NOISE_CERT_HPP
#define BX_NOISE_CERT_HPP

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/config/address.hpp>
#include <bitcoin/explorer/config/algorithm.hpp>
#include <bitcoin/explorer/config/btc.hpp>
#include <bitcoin/explorer/config/byte.hpp>
#include <bitcoin/explorer/config/bytes.hpp>
#include <bitcoin/explorer/config/ec_private.hpp>
#include <bitcoin/explorer/config/electrum.hpp>
#include <bitcoin/explorer/config/endorsement.hpp>
#include <bitcoin/explorer/config/group.hpp>
#include <bitcoin/explorer/config/hd_key.hpp>
#include <bitcoin/explorer/config/language.hpp>
#include <bitcoin/explorer/config/share.hpp>
#include <bitcoin/explorer/config/sighash.hpp>
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
#define BX_NOISE_CERT_INVALID_AUXILIARY \
    "The auxiliary data is not 32 bytes."
#define BX_NOISE_CERT_INVALID_KEY \
    "The authority private key is not valid."
#define BX_NOISE_CERT_INVALID_VALIDITY \
    "The validity period ends after the year 2106."

/**
 * Class to implement the noise-cert command.
 */
class BCX_API noise_cert
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "noise-cert";
    }

    /**
     * Destructor.
     */
    virtual ~noise_cert()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return noise_cert::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "MATH";
    }

    /**
     * The localizable command description.
     */
    virtual const char* description()
    {
        return "Create a Base16 Stratum v2 Noise authority certificate for a server static public key, for use with a Libbitcoin server.";
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("SERVER_PUBLIC_KEY", 1)
            .add("AUTHORITY_PRIVATE_KEY", 1);
    }

    /**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input      The input stream for loading the parameters.
     * @param[in]  variables  The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input,
        po::variables_map& variables)
    {
        load_input(get_authority_private_key_argument(), "AUTHORITY_PRIVATE_KEY", variables, input);
    }

    /**
     * Load program option definitions.
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
            value<system::config::path>(),
            "The path to the configuration settings file."
        )
        (
            "valid_from,v",
            value<uint32_t>(&option_.valid_from),
            "The start of the validity period in Unix seconds, defaults to the current time."
        )
        (
            "days,d",
            value<uint32_t>(&option_.days)->default_value(365),
            "The length of the validity period in days, defaults to 365."
        )
        (
            "auxiliary,a",
            value<system::config::base16>(&option_.auxiliary),
            "The Base16 32 byte auxiliary random data of the signature, defaults to zero."
        )
        (
            "SERVER_PUBLIC_KEY",
            value<system::wallet::ec_public>(&argument_.server_public_key)->required(),
            "The Base16 EC public key of the server static key."
        )
        (
            "AUTHORITY_PRIVATE_KEY",
            value<explorer::config::ec_private>(&argument_.authority_private_key),
            "The Base16 EC private key of the authority. If not specified the key is read from STDIN."
        );

        return options;
    }

    /**
     * Set variable defaults from configuration variable values.
     * @param[in]  variables  The loaded variables.
     */
    virtual void set_defaults_from_config(po::variables_map&)
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
     * Get the value of the SERVER_PUBLIC_KEY argument.
     */
    virtual system::wallet::ec_public& get_server_public_key_argument()
    {
        return argument_.server_public_key;
    }

    /**
     * Set the value of the SERVER_PUBLIC_KEY argument.
     */
    virtual void set_server_public_key_argument(
        const system::wallet::ec_public& value)
    {
        argument_.server_public_key = value;
    }

    /**
     * Get the value of the AUTHORITY_PRIVATE_KEY argument.
     */
    virtual explorer::config::ec_private& get_authority_private_key_argument()
    {
        return argument_.authority_private_key;
    }

    /**
     * Set the value of the AUTHORITY_PRIVATE_KEY argument.
     */
    virtual void set_authority_private_key_argument(
        const explorer::config::ec_private& value)
    {
        argument_.authority_private_key = value;
    }

    /**
     * Get the value of the valid_from option.
     */
    virtual uint32_t& get_valid_from_option()
    {
        return option_.valid_from;
    }

    /**
     * Set the value of the valid_from option.
     */
    virtual void set_valid_from_option(
        const uint32_t& value)
    {
        option_.valid_from = value;
    }

    /**
     * Get the value of the days option.
     */
    virtual uint32_t& get_days_option()
    {
        return option_.days;
    }

    /**
     * Set the value of the days option.
     */
    virtual void set_days_option(
        const uint32_t& value)
    {
        option_.days = value;
    }

    /**
     * Get the value of the auxiliary option.
     */
    virtual system::config::base16& get_auxiliary_option()
    {
        return option_.auxiliary;
    }

    /**
     * Set the value of the auxiliary option.
     */
    virtual void set_auxiliary_option(
        const system::config::base16& value)
    {
        option_.auxiliary = value;
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
          : server_public_key(),
            authority_private_key()
        {
        }

        system::wallet::ec_public server_public_key;
        explorer::config::ec_private authority_private_key;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : valid_from(),
            days(),
            auxiliary()
        {
        }

        uint32_t valid_from;
        uint32_t days;
        system::config::base16 auxiliary;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
