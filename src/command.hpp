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
#ifndef SX_COMMAND_HPP
#define SX_COMMAND_HPP

/**
 * Pure virtual base class for definition of each SX command.
 */
class command
{
public:

    /**
     * The symbolic (not localizable) command name, in lower case.
     * Exmaple: "btc"
     */
    virtual const char* name() = 0;

    /**
     * The localizable category name for the command, in upper case.
     * Example: "UTILITY"
     */
    virtual const char* category() = 0;

    /**
     * The localizable subcategory name for the command, in upper case.
     * Example: "SATOSHI MATH"
     */
    virtual const char* subcategory() = 0;

    /**
     * The localizable description for the command, in one line, punctuated.
     * Example: "Convert Bitcoins into Satoshis."
     */
    virtual const char* description() = 0;

    /**
     * The non-localizable tutorial for the command, in one line, grammatical.
     * This should not include the process, command name or a leading space.
     * Example:
     * "sx btc SATOSHIS"
     * "Convert Satoshis into Bitcoins."
     */
    virtual const char* usage() = 0;

    /**
     * Invoke the command with the raw arguments as provided on the command
     * line. The process name is remove and argument count decremented.
     *
     * @param argc the number of elements in the argv array
     * @param argv the array of arguments, excluding the process
     * @return Success (true) or failure (false).
     */
    virtual bool invoke(const int argc, const char* argv[]) = 0;
};

#endif