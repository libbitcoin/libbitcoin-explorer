
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

BOOST_AUTO_TEST_SUITE(stub)
BOOST_AUTO_TEST_SUITE(ec_lock__invoke)

BOOST_AUTO_TEST_CASE(ec_lock__invoke__always__failure_error)
{
    BX_DECLARE_COMMAND(ec_lock);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
#ifdef WITH_ICU
    BX_REQUIRE_ERROR(BX_EC_LOCK_MODE_INCORRECT "\n");
#else
    BX_REQUIRE_ERROR(BX_EC_LOCK_USING_PASSPHRASE_UNSUPPORTED "\n");
#endif
}

#ifndef ENABLE_TESTNET

#ifdef WITH_ICU
BOOST_AUTO_TEST_CASE(ec_lock__invoke__lock_passphrase_1_no_compress__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_ec_private_key_argument({ "cbf4b9f70470856bb4f40f80b87edb90865997ffee6df315ab166d713af433a5" });
    command.set_passphrase_argument({ "TestingOneTwoThree" });
    command.set_compress_argument({ "0" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PRVWUbkzzsbcVac2qwfssoUJAN1Xhrg6bNk8J7Nzm5H7kxEbn2Nh2ZoGg\n");
}

BOOST_AUTO_TEST_CASE(ec_lock__invoke__lock_passphrase_2_no_compress__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_ec_private_key_argument({ "09c2686880095b1a4c249ee3ac4eea8a014f11e6f986d0b5025ac1f39afbd9ae" });
    command.set_passphrase_argument({ "Satoshi" });
    command.set_compress_argument({ "0" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PRNFFkZc2NZ6dJqFfhRoFNMR9Lnyj7dYGrzdgXXVMXcxoKTePPX1dWByq\n");
}

BOOST_AUTO_TEST_CASE(ec_lock__invoke__lock_passphrase_1_compress__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_ec_private_key_argument({ "cbf4b9f70470856bb4f40f80b87edb90865997ffee6df315ab166d713af433a5" });
    command.set_passphrase_argument({ "TestingOneTwoThree" });
    command.set_compress_argument({ "1" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PYNKZ1EAgYgmQfmNVamxyXVWHzK5s6DGhwP4J5o44cvXdoY7sRzhtpUeo\n");
}

BOOST_AUTO_TEST_CASE(ec_lock__invoke__lock_passphrase_2_compress__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_ec_private_key_argument({ "09c2686880095b1a4c249ee3ac4eea8a014f11e6f986d0b5025ac1f39afbd9ae" });
    command.set_passphrase_argument({ "Satoshi" });
    command.set_compress_argument({ "1" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PYLtMnXvfG3oJde97zRyLYFZCYizPU5T3LwgdYJz1fRhh16bU7u6PPmY7\n");
}
#endif // WITH_ICU

BOOST_AUTO_TEST_CASE(ec_lock__invoke__lock_intermediate_1_no_compress__okay)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_intermediate_argument({ "passphraseo59BauW85etaRsKpbbTrEa5RRYw6bq5K9yrDf4r4N5fcirPdtDKmfJw9oYNoGM" });
    command.set_seed_argument({ "d36d8e703d8bd5445044178f69087657fba73d9f3ff211f7" });
    command.set_compress_argument({ "0" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PfPAw5HErFdzMyBvGMwSfSWjKmzgm3jDg7RxQyVCSSBJFZLAZ6hVupmpn\n");
}

BOOST_AUTO_TEST_CASE(ec_lock__invoke__lock_intermediate_2_no_compress__okay)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_intermediate_argument({ "passphraseouGLY8yjTZQ5Q2bTo8rtKfdbHz4tme7QuPheRgES8KnT6pX5yxFauYhv3SVPDD" });
    command.set_seed_argument({ "bbeac8b9bb39381520b6873553544b387bcaa19112602230" });
    command.set_compress_argument({ "0" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PfU2yS6DUHjgH8wmsJRT1rHWXRofmDV5UJ3dypocew56BDcw5TQJXFYfm\n");
}

BOOST_AUTO_TEST_CASE(ec_lock__invoke__lock_intermediate_3_no_compress__okay)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_intermediate_argument({ "passphraseo59BauW85etaRsKpbbTrEa5RRYw6bq5K9yrDf4r4N5fcirPdtDKmfJw9oYNoGM" });
    command.set_seed_argument({ "d36d8e703d8bd5445044178f69087657fba73d9f3ff211f7" });
    command.set_compress_argument({ "0" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PfPAw5HErFdzMyBvGMwSfSWjKmzgm3jDg7RxQyVCSSBJFZLAZ6hVupmpn\n");
}

BOOST_AUTO_TEST_CASE(ec_lock__invoke__lock_intermediate_4_no_compress__okay)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_intermediate_argument({ "passphraseouGLY8yjTZQ5Q2bTo8rtKfdbHz4tme7QuPheRgES8KnT6pX5yxFauYhv3SVPDD" });
    command.set_seed_argument({ "bbeac8b9bb39381520b6873553544b387bcaa19112602230" });
    command.set_compress_argument({ "0" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PfU2yS6DUHjgH8wmsJRT1rHWXRofmDV5UJ3dypocew56BDcw5TQJXFYfm\n");
}

#else // ENABLE_TESTNET

#ifdef WITH_ICU
BOOST_AUTO_TEST_CASE(ec_lock__testnet__invoke__lock_passphrase_1_no_compress__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_ec_private_key_argument({ "cbf4b9f70470856bb4f40f80b87edb90865997ffee6df315ab166d713af433a5" });
    command.set_passphrase_argument({ "TestingOneTwoThree" });
    command.set_compress_argument({ "0" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PRL8jj6dLQjBBJjHMdUKLSNLEpjTyAfmt8GnCnfT87NeQ2BU5eAW1tcsS\n");
}

BOOST_AUTO_TEST_CASE(ec_lock__testnet__invoke__lock_passphrase_2_no_compress__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_ec_private_key_argument({ "09c2686880095b1a4c249ee3ac4eea8a014f11e6f986d0b5025ac1f39afbd9ae" });
    command.set_passphrase_argument({ "Satoshi" });
    command.set_compress_argument({ "0" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PRN49fV2yEpyCv1pTaXxwCNuMtJEoYCT19iDTUJiRYdPW1HRyrZapfCWP\n");
}

BOOST_AUTO_TEST_CASE(ec_lock__testnet__invoke__lock_passphrase_1_compress__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_ec_private_key_argument({ "cbf4b9f70470856bb4f40f80b87edb90865997ffee6df315ab166d713af433a5" });
    command.set_passphrase_argument({ "TestingOneTwoThree" });
    command.set_compress_argument({ "1" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PYVB5nHnumbUua1UmsAMPHWHa76Ci48MY79aKYnpKmwxeGqHU2XpXtKvo\n");
}

BOOST_AUTO_TEST_CASE(ec_lock__testnet__invoke__lock_passphrase_2_compress__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_ec_private_key_argument({ "09c2686880095b1a4c249ee3ac4eea8a014f11e6f986d0b5025ac1f39afbd9ae" });
    command.set_passphrase_argument({ "Satoshi" });
    command.set_compress_argument({ "1" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PYR63Hbut6L25z7t9mufV6wiiqcjfkV3AEKkyKCCNUZXoE6f8yoAc4JPq\n");
}
#endif // WITH_ICU

BOOST_AUTO_TEST_CASE(ec_lock__testnet__invoke__lock_intermediate_1_no_compress__okay)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_intermediate_argument({ "passphraseo59BauW85etaRsKpbbTrEa5RRYw6bq5K9yrDf4r4N5fcirPdtDKmfJw9oYNoGM" });
    command.set_seed_argument({ "d36d8e703d8bd5445044178f69087657fba73d9f3ff211f7" });
    command.set_compress_argument({ "0" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PfTz8uK5eN6KaNwkG2mzBb1AQkWdD8UMTLYvPm3t8cPaKuSGxzNG2cc4X\n");
}

BOOST_AUTO_TEST_CASE(ec_lock__testnet__invoke__lock_intermediate_2_no_compress__okay)
{
    BX_DECLARE_COMMAND(ec_lock);
    command.set_intermediate_argument({ "passphraseouGLY8yjTZQ5Q2bTo8rtKfdbHz4tme7QuPheRgES8KnT6pX5yxFauYhv3SVPDD" });
    command.set_seed_argument({ "bbeac8b9bb39381520b6873553544b387bcaa19112602230" });
    command.set_compress_argument({ "0" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("6PfN3FmLygXWEJ98jtnM9PadDuig2CxmHzgDm2GeEWggowp9zHrSLiJkNS\n");
}

#endif // ENABLE_TESTNET


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

