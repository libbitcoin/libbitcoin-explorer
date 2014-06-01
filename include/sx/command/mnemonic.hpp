/*
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
#ifndef SX_MNEMONIC_HPP
#define SX_MNEMONIC_HPP

#include <vector>
#include <sx/command.hpp>
#include <sx/utility/compat.hpp>

/********** WARNING: This file is generated, do not edit directly. **********/

namespace sx {
namespace extensions {

/**
 * Class to implement the sx mnemonic command.
 */
class mnemonic : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "mnemonic"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    const char* name()
    {
        return mnemonic::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    const char* category()
    {
        return "OFFLINE KEYS AND ADDRESSES";
    }

    /**
     * The localizable command subcategory name, upper case.
     */
    const char* subcategory()
    {
        return "BRAIN STORAGE";
    }

    /**
     * The localizable command description, multiple lines, punctuated.
     */
    const std::vector<char*> description()
    {
        return
        {
            { "Make 12 word mnemonic out of 128 bit electrum or bip32 seed." }
        };
    }


    /**
     * The non-localizable command usage examples, multiple lines.
     */
    const std::vector<char*> example()
    {
        return
        {
            { "sx mnemonic" },
            { "sx mnemonic SEED" },
            { "sx mnemonic WORD1 WORD2 WORD3 ... WORD12" },
            { "sx mnemonic <<< SEED" },
            { "sx mnemonic <<< 'WORD1 WORD2 WORD3 ... WORD12'" }
        };
    }

    /**
     * The localizable command explanation, multiple lines, punctuated.
     */
    const std::vector<char*> explanation()
    {
        return
        {
            { "Electrum compatible 12 word seeds." },
            { "" },
            { "  $ echo 148f0a1d77e20dbaee3ff920ca40240d | sx mnemonic" },
            { "  people blonde admit dart couple different truth common alas stumble time cookie" },
            { "  $ echo 'people blonde admit dart couple different truth common alas stumble time cookie' | sx mnemonic" },
            { "  148f0a1d77e20dbaee3ff920ca40240d" }
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
