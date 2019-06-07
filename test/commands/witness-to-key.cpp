/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(witness_to_key__invoke)

// Vectors.
#define BX_WITNESS_TO_KEY_WITNESS1 "tb1qr47dd36u96r0fjle36hdygdnp0v6pwfgqe6jxg"
#define BX_WITNESS_TO_KEY_WITNESS2 "tb1qq82ajthl5mlm50h6x70esvxs7atp3vfnjwp8z5kjdepsjqqw3zcsj5rufw"

// Expectations.
#define BX_WITNESS_TO_KEY_KEY1 "31923086d7a16098a89b512c541c0bdea1f249b2bb3e9817382f7fbc087d5062\n"
#define BX_WITNESS_TO_KEY_KEY2 "edd374bd7ae9fe2c2cb9f20adbc675724fbb20b6f40b995ad7c9deb617d09d7b\n"

BOOST_AUTO_TEST_CASE(witness_to_key__invoke__witness1__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::witness_to_key);
    command.set_witness_address_argument({ BX_WITNESS_TO_KEY_WITNESS1, bc::system::wallet::witness_address::encoding::testnet_p2wpkh });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_WITNESS_TO_KEY_KEY1);
}

BOOST_AUTO_TEST_CASE(witness_to_key__invoke__witness2__okay_output)
{
    BX_DECLARE_CLIENT_COMMAND(bc::explorer::commands::witness_to_key);
    command.set_witness_address_argument({ BX_WITNESS_TO_KEY_WITNESS2, bc::system::wallet::witness_address::encoding::testnet_p2wsh });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_WITNESS_TO_KEY_KEY2);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
