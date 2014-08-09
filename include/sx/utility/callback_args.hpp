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
#ifndef SX_CALLBACK_ARGS_HPP
#define SX_CALLBACK_ARGS_HPP

#include <iostream>
#include <sx/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {

/**
 * Class to simplify parameter passing to our standard callbacks.
 */
class callback_args
{
public:

    /**
     * Constructor.
     *
     * @param[in]  error   The error stream for the callback handler.
     * @param[in]  output  The output stream for the callback handler.
     */
    callback_args(std::ostream& error, std::ostream& output)
        : error_(error), output_(output), stopped_(false),
        result_(console_result::okay)
    {
    }

    /**
     * Get a reference to the error stream.
     */
    std::ostream& error()
    {
        return error_;
    }
    
    /**
     * Get a reference to the output stream.
     */
    std::ostream& output()
    {
        return output_;
    }
    
    /**
     * Get a reference to the callback result.
     */
    console_result& result()
    {
        return result_;
    }
    
    /**
     * Get a reference to the callback synchronization flag.
     */
    bool& stopped()
    {
        return stopped_;
    }

private:
    bool stopped_;
    console_result result_;
    std::ostream& error_;
    std::ostream& output_;
};

} // sx

#endif
