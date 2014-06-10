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
#ifndef SX_FETCH_TRANSACTION_HPP
#define SX_FETCH_TRANSACTION_HPP

#include <stdint.h>
#include <vector>
#include <boost/program_options.hpp>
#include <sx/command.hpp>
#include <sx/generated.hpp>
#include <sx/utility/compat.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace sx {
namespace extensions {

/**
 * Class to implement the sx fetch-transaction command.
 */
class fetch_transaction 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "fetch-transaction"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    const char* name()
    {
        return fetch_transaction::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    const char* category()
    {
        return "ONLINE (OBELISK)";
    }

    /**
     * The localizable command subcategory name, upper case.
     */
    const char* subcategory()
    {
        return "BLOCKCHAIN QUERIES";
    }

    /**
     * The localizable command description, multiple lines, punctuated.
     */
    const std::vector<const char*> description()
    {
        return
        {
            { "Fetch a raw transaction using a network connection to" }
            { "make requests against the obelisk load balancer backend." },
        };
    }

    /**
     * The non-localizable command usage examples, multiple lines.
     */
    const std::vector<const char*> example()
    {
        return
        {
            { "sx fetch-transaction HASH" },
        };
    }

    /**
     * The localizable command explanation, multiple lines, punctuated.
     */
    const std::vector<const char*> explanation()
    {
        return
        {
            { "Fetch a raw transaction using a network connection to" }
            { "make requests against the obelisk load balancer backend." }
            { "" }
            { "EXAMPLE:" }
            { "" }
            { "  $ sx fetch-transaction 69735d70ada1be32ff39b49c6fc2390b03e9d5eed8918ed10fe42c8cbabf62d4 # fetches raw data" },
        };
    }
    
    /**
     * Initialize the program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     *
     * @param[out] definitions  The defined program argument definitions.
     */
    void initialize_arguments(
        boost::program_options::positional_options_description& definitions)
    {
    }
    
    /**
     * Initialize the program option definitions.
     * The implicit_value call allows flags to be stringly-typed on read while
     * allowing but not requiring a value on the command line for the option.
     *
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     *
     * @param[out] definitions  The defined program option definitions.
     */
    void initialize_options(
        boost::program_options::options_description& definitions)
    {
        using namespace std;
        using namespace boost::filesystem;
        using namespace boost::program_options;
        definitions.add_options()
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
