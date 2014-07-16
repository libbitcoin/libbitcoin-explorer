/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#ifndef WIF_HPP
#define WIF_HPP

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

#define SX_SERIALIZER_WIF_EXCEPTION \
    "Invalid wallet import format."

/**
 * Serialization helper to convert between hex string and ec_secret.
 */
class wif
{
public:

    /**
     * Constructor.
     */
    wif()
        : compressed_(true), value_() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  text  The value to initialize with.
     */
    wif(const std::string& text)
    {
        std::stringstream(text) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    wif(const bc::ec_secret& value)
        : compressed_(true)
    {
        std::copy(value.begin(), value.end(), value_.begin());
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    wif(const wif& other)
        : wif(other.value_) {}

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bc::ec_secret& data()
    {
        return value_;
    }

    /**
     * Get the compressed property.
     */
    bool get_compressed()
    {
        return compressed_;
    }

    /**
     * Set the compressed property.
     */
    void set_compressed(bool value)
    {
        compressed_ = value;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const bc::ec_secret() const
    {
        return value_; 
    }

    /**
     * Overload stream in. Throws if input is invalid.
     *
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, wif& argument)
    {
        std::string text;
        input >> text;
        auto value = libwallet::wif_to_secret(text);

        if (!bc::verify_private_key(value))
            throw po::invalid_option_value(SX_SERIALIZER_WIF_EXCEPTION);

        argument.compressed_ = libwallet::is_wif_compressed(text);
        std::copy(value.begin(), value.end(), argument.value_.begin());
        return input;
    }

    /**
     * Overload stream out.
     *
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output, const wif& argument)
    {
        // bc::secret_to_public_key(secret, compressed);
        output << libwallet::secret_to_wif(argument.value_, 
            argument.compressed_);
        return output;
    }

private:

    /**
     * The state of derived public key compression, indicating that the derived
     * public key should be compressed when serialized. This is obtained from
     * and serialized with the WIF private key and otherwise defaults to true.
     * https://bitcointalk.org/index.php?topic=129652.msg1384929#msg1384929
     */
    bool compressed_;

    /**
     * The state of this object's secret.
     */
    bc::ec_secret value_;
};

} // sx
} // serializer

#endif