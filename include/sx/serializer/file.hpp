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
#ifndef FILE_HPP
#define FILE_HPP

#include <io.h>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/utility/utility.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {
    
/**
 * Conventional command line argument sentinel for indicating that a file
 * should be read from STDIN.
 */
#define SX_STDIN_PATH_SENTINEL "-"

/**
 * Serialization helper to convert between hex string and ec_secret.
 */
class file
{
public:

    /**
     * Constructor.
     */
    file() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  text  The value to initialize with.
     */
    file(const std::string& text)
    {
        std::stringstream(text) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    file(const bc::data_chunk& value)
    {
        std::copy(value.begin(), value.end(), value_.begin());
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    file(const file& other)
    {
    }

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bc::data_chunk& data()
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const std::string&() const
    {
        return path_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const bc::data_chunk&() const
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
    friend std::istream& operator>>(std::istream& input, file& argument)
    {
        std::string path(SX_STDIN_PATH_SENTINEL);
        input >> path;
        argument.path_ = path;

        if (path == SX_STDIN_PATH_SENTINEL)
        {
#ifdef _WIN32
            // The function sets the _fmode global variable.
            // This specifies the default translation mode for 
            // file I/O operations 
            _setmode(_fileno(stdin), _O_BINARY);
#endif
            std::istreambuf_iterator<char> first(std::cin), last;
            argument.value_.assign(first, last);
#ifdef _WIN32
            // The default setting of _fmode is _O_TEXT.
            // msdn.microsoft.com/en-us/library/61dstksf.aspx
            _setmode(_fileno(stdin), _O_TEXT);
#endif
        }
        else
        {
            std::ifstream infile(path, std::ifstream::binary);
            if (infile.fail())
                throw po::invalid_option_value(path);

            std::istreambuf_iterator<char> first(infile), last;
            argument.value_.assign(first, last);
        }

        return input;
    }

    /**
     * Overload stream out.
     *
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output, const file& argument)
    {
        std::ostreambuf_iterator<char> out(output);
        std::copy(argument.value_.begin(), argument.value_.end(), out);
        return output;
    }

private:

    /**
     * The state of this object's file data.
     */
    bc::data_chunk value_;

    /**
    * The state of this object's file path.
    */
    std::string path_;
};

} // sx
} // serializer

#endif