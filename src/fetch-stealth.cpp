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
#include <sx/command/fetch-stealth.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/define.hpp>
#include <sx/serializer/address.hpp>
#include <sx/serializer/btc256.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/utility/callback_args.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

static bool stopped;
static console_result result;

static void handle_callback(callback_args& args,
    const blockchain::stealth_list& stealth_results)
{
    for (const auto& row: stealth_results)
        args.output() << boost::format(SX_FETCH_STEALTH_OUTPUT) %
            hex(row.ephemkey) % address(row.address) %
            btc256(row.transaction_hash) << std::endl;

    args.stopped() = true;
}


console_result fetch_stealth::invoke(std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    const auto height = get_height_option();
    const stealth_prefix prefix = get_prefix_option();

    callback_args args(cerr, output);
    const auto handler = [&args](const std::error_code& error,
        const blockchain::stealth_list& stealth_results)
    {
        handle_error(args, error);
        handle_callback(args, stealth_results);
    };

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    fullnode.blockchain.fetch_stealth(prefix,
        std::bind(handler, ph::_1, ph::_2), height);
    client.poll(args.stopped());

    return args.result();
}