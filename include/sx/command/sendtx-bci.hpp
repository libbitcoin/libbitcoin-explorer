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
#ifndef SX_SENDTX_BCI_HPP
#define SX_SENDTX_BCI_HPP

#include <vector>
#include <sx/command.hpp>
#include <sx/utility/compat.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace sx {
namespace extensions {

/**
 * Class to implement the sx sendtx-bci command.
 */
class sendtx_bci : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "sendtx-bci"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    const char* name()
    {
        return sendtx_bci::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    const char* category()
    {
        return "ONLINE (BLOCKCHAIN.INFO)";
    }

    /**
     * The localizable command subcategory name, upper case.
     */
    const char* subcategory()
    {
        return "BLOCKCHAIN UPDATES";
    }

    /**
     * The localizable command description, multiple lines, punctuated.
     */
    const std::vector<char*> description()
    {
        return
        {
            { "Send tx to blockchain.info/pushtx." }
        };
    }


    /**
     * The non-localizable command usage examples, multiple lines.
     */
    const std::vector<char*> example()
    {
        return
        {
            { "sx bci-push-tx FILENAME" }
        };
    }

    /**
     * The localizable command explanation, multiple lines, punctuated.
     */
    const std::vector<char*> explanation()
    {
        return
        {
            { "Send tx to blockchain.info/pushtx." },
            { "" },
            { "  $ sx sendtx-bci txfile.tx" }
        };
    }

    /**
     * Invoke the command with the raw arguments as provided on the command
     * line. The process name is removed and argument count decremented.
     *
     * @param[in]  argc  The number of elements in the argv array.
     * @param[in]  argv  The array of arguments, excluding the process.
     * @return           The appropriate console return code { -1, 0, 1 }.
     */
    console_result invoke(int argc, const char* argv[]);
};

} // extensions
} // sx

#endif
