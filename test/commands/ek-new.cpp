/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
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
#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(ek_new__invoke)

BOOST_AUTO_TEST_CASE(ek_new__invoke__vector_8_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_new);
    command.set_token_argument({ "passphraseo59BauW85etaRsKpbbTrEa5RRYw6bq5K9yrDf4r4N5fcirPdtDKmfJw9oYNoGM" });
    command.set_seed_argument({ "d36d8e703d8bd5445044178f69087657fba73d9f3ff211f7" });
    command.set_uncompressed_option(true);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PfPAw5HErFdzMyBvGMwSfSWjKmzgm3jDg7RxQyVCSSBJFZLAZ6hVupmpn\n");
}

BOOST_AUTO_TEST_CASE(ek_new__invoke__vector_9_uncompressed__okay)
{
    BX_DECLARE_COMMAND(ek_new);
    command.set_token_argument({ "passphraseouGLY8yjTZQ5Q2bTo8rtKfdbHz4tme7QuPheRgES8KnT6pX5yxFauYhv3SVPDD" });
    command.set_seed_argument({ "bbeac8b9bb39381520b6873553544b387bcaa19112602230" });
    command.set_uncompressed_option(true);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PfU2yS6DUHjgH8wmsJRT1rHWXRofmDV5UJ3dypocew56BDcw5TQJXFYfm\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
