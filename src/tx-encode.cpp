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
#include <sx/command/tx-encode.hpp>

#include <iostream>
#include <vector>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/serializer/item.hpp>
#include <sx/serializer/input.hpp>
#include <sx/serializer/output.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace libwallet;
using namespace sx;
using namespace sx::extension;
using namespace sx::serializer;

console_result tx_encode::invoke(std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    const auto locktime = get_locktime_option();
    const auto version = get_version_option();
    const auto& inputs = get_inputs_option();
    const auto& outputs = get_outputs_option();
    const auto& path = get_file_argument();

    transaction_type tx;
    tx.version = version;

    // TODO: coordinate input sequence and locktime to enable this feature.
    // Locktime will not function unless an input sequence is not at max.
    tx.locktime = locktime;

    for (const bc::transaction_input_type& input: inputs)
        tx.inputs.push_back(input);

    for (const std::vector<bc::transaction_output_type>& output_sets: outputs)
        for (const auto& output: output_sets)
            tx.outputs.push_back(output);

    const auto transaction = item<transaction_type>(tx);
    if (path.empty() || path == SX_STDIO_PATH_SENTINEL)
        output << transaction;
    else
    {
        std::ofstream outfile(path, std::ofstream::binary);
        outfile << transaction;
    }

    return console_result::okay;
}