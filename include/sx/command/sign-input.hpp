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
#ifndef SX_SIGN_INPUT_HPP
#define SX_SIGN_INPUT_HPP

#include <vector>
#include <sx/command.hpp>
#include <sx/utility/compat.hpp>

/********** WARNING: This file is generated, do not edit directly. **********/

namespace sx {
namespace extensions {

/**
 * Class to implement the sx sign-input command.
 */
class sign_input : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol() { return "sign-input"; }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    const char* name()
    {
        return sign_input::symbol();
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
            { "Sign a transaction input." }
        };
    }


    /**
     * The non-localizable command usage examples, multiple lines.
     */
    const std::vector<char*> example()
    {
        return
        {
            { "cat secret.key | sx sign-input FILENAME INDEX PREVOUT_SCRIPT" }
        };
    }

    /**
     * The localizable command explanation, multiple lines, punctuated.
     */
    const std::vector<char*> explanation()
    {
        return
        {
            { "Sign a transaction input." },
            { "" },
            { "" },
            { "Note how the input script in the following transaction is empty." },
            { "  $ sx mktx txfile.tx -i 97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:0 -o 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe:90000" },
            { "  $ sx showtx txfile.tx" },
            { "  hash: 4d25b18ed094ad68f75f21692d8540f45ceb90b240a521b8f191e95d8b6b8bb0" },
            { "  version: 1  locktime: 0" },
            { "  Input:" },
            { "    previous output:" },
            { "  97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:0" },
            { "    script:   sequence: 4294967295" },
            { "  Output:" },
            { "    value: 90000" },
            { "    script: dup hash160 [ 18c0bd8d1818f1bf99cb1df2269c645318ef7b73 ] equalverify" },
            { "  checksig" },
            { "    address: 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe" },
            { "" },
            { "We will now sign the first input using our private key." },
            { "" },
            { "  $ echo '5KPFsatiYrJcvCSRrDbtx61822vZjeGGGx3wu38pQDHRF8eVJ8H' > private.key" },
            { "  $ DECODED_ADDR=$(cat private.key | sx addr | sx decode-addr)" },
            { "  $ PREVOUT_SCRIPT=$(sx rawscript dup hash160 [ $DECODED_ADDR ] equalverify checksig)" },
            { "  $ SIGNATURE=$(cat private.key | sx sign-input txfile.tx 0 $PREVOUT_SCRIPT)" },
            { "  $ SIGNATURE_AND_PUBKEY_SCRIPT=$(sx rawscript [ $SIGNATURE ] [ $(cat private.key | sx pubkey) ])" },
            { "  $ sx set-input txfile.tx 0 $SIGNATURE_AND_PUBKEY_SCRIPT > txfile.tx.signed  # the first input has index 0" },
            { "" },
            { "Note how the input script in the following transaction is now filled." },
            { "" },
            { "  $ cat txfile.tx.signed | sx showtx" },
            { "  hash: cc5650c69173e7607c095200f4ff36265f9fbb45e112b60cd467d696b2724488" },
            { "  version: 1" },
            { "  locktime: 0" },
            { "  Input:" },
            { "    previous output: 97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:0" },
            { "    script: [ 3045022100b778f7fb270b751491ba7e935a6978eaea2a44795b3f6636ea583939697b1ca102203ce47d3ecb0b7e832114e88e549fce476d4ea120ca1e60c508fe8083889a9cba01 ] [ 04c40cbd64c9c608df2c9730f49b0888c4db1c436e8b2b74aead6c6afbd10428c0adb73f303ae1682415253f4411777224ab477ad098347ddb7e0b94d49261e613 ]" },
            { "    sequence: 4294967295" },
            { "    address: 1MyKMeDsom7rYcp69KpbKn4DcyuvLMkLYJ" },
            { "  Output:" },
            { "    value: 90000" },
            { "    script: dup hash160 [ 18c0bd8d1818f1bf99cb1df2269c645318ef7b73 ] equalverify checksig" },
            { "    address: 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe" },
            { "" },
            { "" },
            { "Now the input script is prepared, and the transaction is signed." }
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
