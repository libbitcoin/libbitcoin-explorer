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
#ifndef BX_QRCODE_HPP
#define BX_QRCODE_HPP

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
#define BX_QRCODE_REQUIRES_QRENCODE \
    "The command requires a QRENCODE build."
#define BX_QRCODE_REQUIRES_PNG \
    "The command requires a PNG build."
#define BX_QRCODE_WRITE_ERROR \
    "Error writing encoded data."

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
        return "Create a QRCODE image file for a payment address.";
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
    virtual arguments_metadata& load_arguments()
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
            "density,d",
            value<uint32_t>(&option_.density)->default_value(72),
            "The pixels per inch of the QRCODE, defaults to 72."
        )
        (
            "insensitive,i",
            value<bool>(&option_.insensitive)->zero_tokens(),
            "Do not use use sensitivity."
        )
        (
            "module_size,m",
            value<uint32_t>(&option_.module_size)->default_value(8),
            "The module size in pixels of the QRCODE, defaults to 8."
        )
        (
            "margin_size,r",
            value<uint32_t>(&option_.margin_size)->default_value(2),
            "The margin size in pixels of the QRCODE, defaults to 2."
        )
        (
            "png,p",
            value<bool>(&option_.png)->zero_tokens(),
            "Write the QRCODE in PNG file format."
        )
        (
            "scheme,s",
            value<std::string>(&option_.scheme)->default_value("bitcoin"),
            "The URI scheme of the QRCODE data, defaults to bitcoin."
        )
        (
            "version,v",
            value<uint32_t>(&option_.version),
            "The version of the QRCODE."
        )
        (
            "PAYMENT_ADDRESS",
            value<bc::wallet::payment_address>(&argument_.payment_address)->required(),
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
    virtual console_result invoke(std::ostream& output,
        std::ostream& cerr);

    /* Properties */

    /**
     * Get the value of the PAYMENT_ADDRESS argument.
     */
    virtual bc::wallet::payment_address& get_payment_address_argument()
    {
        return argument_.payment_address;
    }

    /**
     * Set the value of the PAYMENT_ADDRESS argument.
     */
    virtual void set_payment_address_argument(
        const bc::wallet::payment_address& value)
    {
        argument_.payment_address = value;
    }

    /**
     * Get the value of the density option.
     */
    virtual uint32_t& get_density_option()
    {
        return option_.density;
    }

    /**
     * Set the value of the density option.
     */
    virtual void set_density_option(
        const uint32_t& value)
    {
        option_.density = value;
    }

    /**
     * Get the value of the insensitive option.
     */
    virtual bool& get_insensitive_option()
    {
        return option_.insensitive;
    }

    /**
     * Set the value of the insensitive option.
     */
    virtual void set_insensitive_option(
        const bool& value)
    {
        option_.insensitive = value;
    }

    /**
     * Get the value of the module_size option.
     */
    virtual uint32_t& get_module_size_option()
    {
        return option_.module_size;
    }

    /**
     * Set the value of the module_size option.
     */
    virtual void set_module_size_option(
        const uint32_t& value)
    {
        option_.module_size = value;
    }

    /**
     * Get the value of the margin_size option.
     */
    virtual uint32_t& get_margin_size_option()
    {
        return option_.margin_size;
    }

    /**
     * Set the value of the margin_size option.
     */
    virtual void set_margin_size_option(
        const uint32_t& value)
    {
        option_.margin_size = value;
    }

    /**
     * Get the value of the png option.
     */
    virtual bool& get_png_option()
    {
        return option_.png;
    }

    /**
     * Set the value of the png option.
     */
    virtual void set_png_option(
        const bool& value)
    {
        option_.png = value;
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
    virtual uint32_t& get_version_option()
    {
        return option_.version;
    }

    /**
     * Set the value of the version option.
     */
    virtual void set_version_option(
        const uint32_t& value)
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

        bc::wallet::payment_address payment_address;
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
          : density(),
            insensitive(),
            module_size(),
            margin_size(),
            png(),
            scheme(),
            version()
        {
        }

        uint32_t density;
        bool insensitive;
        uint32_t module_size;
        uint32_t margin_size;
        bool png;
        std::string scheme;
        uint32_t version;
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
