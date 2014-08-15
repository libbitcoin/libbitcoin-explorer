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
#include "precompile.hpp"
#include <sx/command/stealth-newkey.hpp>

#include <iostream>
//#include <bitcoin/bitcoin.hpp>
//#include <wallet/wallet.hpp>
#include <sx/define.hpp>
//#include <sx/serializer/ec_private.hpp>

//using namespace bc;
//using namespace libwallet;
using namespace sx;
using namespace sx::extension;
//using namespace sx::serializer;

// Obsoleted because internal key generation is bad practice, and redundant.
console_result stealth_newkey::invoke(std::ostream& output, std::ostream& error)
{
    //const auto& scan_secret = generate_random_secret();
    //const auto& spend_secret = generate_random_secret();
    //const auto& spend_pubkey = secret_to_public_key(spend_secret);

    //stealth_address stealth;
    //stealth.options = 0;
    //stealth.scan_pubkey = secret_to_public_key(scan_secret);
    //stealth.spend_pubkeys.push_back(spend_pubkey);
    //stealth.number_signatures = 1;

    error << SX_STEALTH_NEWKEY_OBSOLETE << std::endl;
    return console_result::okay;
}