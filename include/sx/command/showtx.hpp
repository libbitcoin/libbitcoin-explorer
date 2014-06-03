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
#ifndef SX_SHOWTX_HPP
#define SX_SHOWTX_HPP

#include <vector>
#include <sx/command.hpp>
#include <sx/utility/compat.hpp>

/********** WARNING: This file is generated, do not edit directly. **********/

namespace sx {
namespace extensions {

/**
 * Class to implement the sx showtx command.
 */
class showtx : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "showtx"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    const char* name()
    {
        return showtx::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    const char* category()
    {
        return "OFFLINE TRANSACTIONS";
    }

    /**
     * The localizable command subcategory name, upper case.
     */
    const char* subcategory()
    {
        return "SCRIPTING";
    }

    /**
     * The localizable command description, multiple lines, punctuated.
     */
    const std::vector<char*> description()
    {
        return
        {
            { "Show the details of a transaction." }
        };
    }


    /**
     * The non-localizable command usage examples, multiple lines.
     */
    const std::vector<char*> example()
    {
        return
        {
            { "sx showtx [-j] [FILENAME]" }
        };
    }

    /**
     * The localizable command explanation, multiple lines, punctuated.
     */
    const std::vector<char*> explanation()
    {
        return
        {
            { "'showtx' allows inspecting of tx files." },
            { "" },
            { "  -j, --json                 Enable json parseable output." },
            { "" },
            { "Example:" },
            { "" },
            { "  $ sx fetch-transaction cd484f683bc99c94948613a7f7254880e9c98cd74f2760a2d2c4e372fda1bc6a | sx showtx" },
            { "  hash: cd484f683bc99c94948613a7f7254880e9c98cd74f2760a2d2c4e372fda1bc6a" },
            { "  version: 1" },
            { "  locktime: 0" },
            { "  Input:" },
            { "    previous output: f97367c5dc9e521a4c541327cbff69d118e35a2d0b67f91eb7771741a6374b20:0" },
            { "    script: [ 3046022100f63b1109e1b04c0a4b5230e6f6c75f5e2a10c16d022cdf93de9b3cc946e6e24a022100ae3da40f05504521f2f3557e736a2d1724d6d1d8c18b66a64990bf1afee78dba01 ] [ 028a2adb719bbf7e9cf0cb868d4f30b10551f2a4402eb2ece9b177b49e68e90511 ]" },
            { "    sequence: 4294967295" },
            { "    address: 1NYMePixLjAATLaz55vN7FfTLUfFB23Tt" },
            { "  Output:" },
            { "    value: 2676400" },
            { "    script: dup hash160 [ 6ff00bd374abb3a3f19d1576bb36520b2cb15e2d ] equalverify checksig" },
            { "    address: 1BCsZziw8Q1sMhxr2DjAR7Rmt1qQvYwXSU" },
            { "  Output:" },
            { "    value: 1000000" },
            { "    script: hash160 [ 0db1635fe975792a9a7b6f2d4061b730478dc6b9 ] equal" },
            { "    address: 32wRDBezxnazSBxMrMqLWqD1ajwEqnDnMc" }
        };
    }

    /**
     * Invoke the command with the raw arguments as provided on the command
     * line. The process name is removed and argument count decremented.
     *
     * @param[in]  argc  The number of elements in the argv array.
     * @param[in]  argv  The array of arguments, excluding the process.
     * @return           True if successful.
     */
    bool invoke(const int argc, const char* argv[]);
};

} // extensions
} // sx

#endif
