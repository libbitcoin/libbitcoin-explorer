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
#ifndef SX_WALLET_HPP
#define SX_WALLET_HPP

#include "../command.hpp"
#include "../utility/compat.hpp"

/* TODO: GSL Code generation */

#define WALLET_NO_MASTER_PUBLIC_KEY \
    "No valid master public key or private secret key was passed in."

/**
 * Class to implement the sx wallet command.
 */
class wallet : public command
{
public:

    /**
     * The symbolic (not localizable) command name, in lower case.
     */
    static const char* symbol() { return "wallet"; }

    /**
     * The member symbolic (not localizable) command name, in lower case.
     */
    const char* name()
    {
        return wallet::symbol();
    }

    /**
     * The non-localizable tutorial for the command, in one line, grammatical.
     */
    const char* usage()
    {
        return "sx wallet SEED";
    }

    /**
     * The localizable category name for the command, in upper case.
     */
    const char* category()
    {
        return "EXPERIMENTAL";
    }

    /**
     * The localizable subcategory name for the command, in upper case.
     */
    const char* subcategory()
    {
        return "APPS";
    }

    /**
     * The localizable description for the command, in one line, punctuated.
     */
    const char* description()
    {
        return "Experimental command line wallet.";
    }

    /**
     * The localizable explanation for the command, multiple lines, punctuated.
     * Lines are terminated by std:endl.
     */
    const char* explanation()
    {
        return 
            "This is an experimental prototype." END_LINE;
    }

    /**
     * Invoke the wallet with the raw arguments as provided on the command
     * line. The process name is remove and argument count decremented.
     *
     * @param argc the number of elements in the argv array
     * @param argv the array of arguments, excluding the process
     * @return Success (true) or failure (false).
     */
    bool invoke(const int argc, const char* argv[]);
};

#endif