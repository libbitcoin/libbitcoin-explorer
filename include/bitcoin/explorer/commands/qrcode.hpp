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
#ifndef BX_QRCODE_HPP
#define BX_QRCODE_HPP

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
#define BX_QRCODE_MINIMUM_SIZE \
    "The pixel size of modules must be greater than 0. "
#define BX_QRCODE_MAXIMUM_SIZE \
    "The image is too large for uncompressed TIFF encoding."
#define BX_QRCODE_MAXIMUM_VERSION \
    "The version exceeds the maximum value of 40."

/**
 * Class to implement the qrcode command.
 */
class BCX_API qrcode
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "qrcode";
    }

    /**
     * Destructor.
     */
    virtual ~qrcode()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return qrcode::symbol();
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
        return "Create a square QRCODE TIFF file for a payment address.";
    }

    /**
     * Determines if STDOUT is required to be raw.
     * @return  True if the type of the STDOUT argument is primitive::raw.
     */
    virtual bool requires_raw_output()
    {
        return true;
    }

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual system::arguments_metadata& load_arguments()
    {
        return get_argument_metadata()
            .add("PAYMENT_ADDRESS", 1);
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
        load_input(get_payment_address_argument(), "PAYMENT_ADDRESS", variables, input, raw);
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
            "margin,m",
            value<uint16_t>(&option_.margin)->default_value(2),
            "The pixel width of the QRCODE margin, defaults to 2."
        )
        (
            "pixels,p",
            value<uint16_t>(&option_.pixels)->default_value(8),
            "The pixel width of the QRCODE modules, defaults to 8."
        )
        (
            "scheme,s",
            value<std::string>(&option_.scheme)->default_value("bitcoin"),
            "The URI scheme of the QRCODE data, defaults to 'bitcoin'."
        )
        (
            "version,v",
            value<uint8_t>(&option_.version),
            "The version of the QRCODE, defaults to 0 which is the minimum size."
        )
        (
            "PAYMENT_ADDRESS",
            value<system::wallet::payment_address>(&argument_.payment_address)->required(),
            "The payment address. If not specified the address is read from STDIN."
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
     * Get the value of the PAYMENT_ADDRESS argument.
     */
    virtual system::wallet::payment_address& get_payment_address_argument()
    {
        return argument_.payment_address;
    }

    /**
     * Set the value of the PAYMENT_ADDRESS argument.
     */
    virtual void set_payment_address_argument(
        const system::wallet::payment_address& value)
    {
        argument_.payment_address = value;
    }

    /**
     * Get the value of the margin option.
     */
    virtual uint16_t& get_margin_option()
    {
        return option_.margin;
    }

    /**
     * Set the value of the margin option.
     */
    virtual void set_margin_option(
        const uint16_t& value)
    {
        option_.margin = value;
    }

    /**
     * Get the value of the pixels option.
     */
    virtual uint16_t& get_pixels_option()
    {
        return option_.pixels;
    }

    /**
     * Set the value of the pixels option.
     */
    virtual void set_pixels_option(
        const uint16_t& value)
    {
        option_.pixels = value;
    }

    /**
     * Get the value of the scheme option.
     */
    virtual std::string& get_scheme_option()
    {
        return option_.scheme;
    }

    /**
     * Set the value of the scheme option.
     */
    virtual void set_scheme_option(
        const std::string& value)
    {
        option_.scheme = value;
    }

    /**
     * Get the value of the version option.
     */
    virtual uint8_t& get_version_option()
    {
        return option_.version;
    }

    /**
     * Set the value of the version option.
     */
    virtual void set_version_option(
        const uint8_t& value)
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
          : payment_address()
        {
        }

        system::wallet::payment_address payment_address;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : margin(),
            pixels(),
            scheme(),
            version()
        {
        }

        uint16_t margin;
        uint16_t pixels;
        std::string scheme;
        uint8_t version;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
