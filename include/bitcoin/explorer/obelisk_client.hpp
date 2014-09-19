/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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
#ifndef BX_OBELISK_CLIENT_HPP__
#define BX_OBELISK_CLIENT_HPP__

#include <cstdint>
#include <functional>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/async_client.hpp>
#include <bitcoin/explorer/command.hpp>
#include <czmq++/czmq.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {

/**
 * Class to simplify libbitcoin server usage. 
 */
class obelisk_client
{
public:

    /**
     * Initialization constructor.
     * @param[in]  command  The command being processed.
     * @param[in]  threads  The number of pool threads to initialize.
     */
    obelisk_client(czmqpp::context& context);

    virtual int connect();

    ///**
    // * Get the value of the obelisk fullnode interface.
    // */
    virtual bc::client::obelisk_codec& get_codec();

    virtual void resolve_callbacks();

private:

    czmqpp::socket socket_;

    bc::client::socket_message_stream stream_;

    ///**
    // * Encapsulated full node client instance.
    // */
    bc::client::obelisk_codec codec_;
};

} // namespace explorer
} // namespace libbitcoin

#endif
