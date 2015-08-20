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
BOOST_AUTO_TEST_SUITE(ec_unlock__invoke)

BOOST_AUTO_TEST_CASE(ec_unlock__invoke__always__failure_error)
{
    BX_DECLARE_COMMAND(ec_unlock);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_LOCK_USING_PASSPHRASE_UNSUPPORTED "\n");
}

BOOST_AUTO_TEST_CASE(ec_unlock__invoke__unlock_1_no_compress__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_unlock);
    command.set_secret_argument({ "6PRVWUbkzzsbcVac2qwfssoUJAN1Xhrg6bNk8J7Nzm5H7kxEbn2Nh2ZoGg" });
    command.set_passphrase_argument({ "TestingOneTwoThree" });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("cbf4b9f70470856bb4f40f80b87edb90865997ffee6df315ab166d713af433a5\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_UNLOCK_USING_PASSPHRASE_UNSUPPORTED "\n");
#endif
}

BOOST_AUTO_TEST_CASE(ec_unlock__invoke__unlock_2_no_compress__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_unlock);
    command.set_secret_argument({ "6PRNFFkZc2NZ6dJqFfhRoFNMR9Lnyj7dYGrzdgXXVMXcxoKTePPX1dWByq" });
    command.set_passphrase_argument({ "Satoshi" });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("09c2686880095b1a4c249ee3ac4eea8a014f11e6f986d0b5025ac1f39afbd9ae\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_UNLOCK_USING_PASSPHRASE_UNSUPPORTED "\n");
#endif
}

BOOST_AUTO_TEST_CASE(ec_unlock__invoke__unlock_1_compress__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_unlock);
    command.set_secret_argument({ "6PYNKZ1EAgYgmQfmNVamxyXVWHzK5s6DGhwP4J5o44cvXdoY7sRzhtpUeo" });
    command.set_passphrase_argument({ "TestingOneTwoThree" });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("cbf4b9f70470856bb4f40f80b87edb90865997ffee6df315ab166d713af433a5\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_UNLOCK_USING_PASSPHRASE_UNSUPPORTED "\n");
#endif
}

BOOST_AUTO_TEST_CASE(ec_unlock__invoke__unlock_2_compress__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_unlock);
    command.set_secret_argument({ "6PYLtMnXvfG3oJde97zRyLYFZCYizPU5T3LwgdYJz1fRhh16bU7u6PPmY7" });
    command.set_passphrase_argument({ "Satoshi" });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("09c2686880095b1a4c249ee3ac4eea8a014f11e6f986d0b5025ac1f39afbd9ae\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_UNLOCK_USING_PASSPHRASE_UNSUPPORTED "\n");
#endif
}

BOOST_AUTO_TEST_CASE(ec_unlock__invoke__unlock_1_ec_multiply__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_unlock);
    command.set_secret_argument({ "6PfQu77ygVyJLZjfvMLyhLMQbYnu5uguoJJ4kMCLqWwPEdfpwANVS76gTX" });
    command.set_passphrase_argument({ "TestingOneTwoThree" });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("a43a940577f4e97f5c4d39eb14ff083a98187c64ea7c99ef7ce460833959a519\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_UNLOCK_USING_PASSPHRASE_UNSUPPORTED "\n");
#endif
}

BOOST_AUTO_TEST_CASE(ec_unlock__invoke__unlock_2_ec_multiply__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_unlock);
    command.set_secret_argument({ "6PfLGnQs6VZnrNpmVKfjotbnQuaJK4KZoPFrAjx1JMJUa1Ft8gnf5WxfKd" });
    command.set_passphrase_argument({ "Satoshi" });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("c2c8036df268f498099350718c4a3ef3984d2be84618c2650f5171dcc5eb660a\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_UNLOCK_USING_PASSPHRASE_UNSUPPORTED "\n");
#endif
}

BOOST_AUTO_TEST_CASE(ec_unlock__invoke__unlock_3_ec_multiply__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_unlock);
    command.set_secret_argument({ "6PgNBNNzDkKdhkT6uJntUXwwzQV8Rr2tZcbkDcuC9DZRsS6AtHts4Ypo1j" });
    command.set_passphrase_argument({ "MOLON LABE" });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("44ea95afbf138356a05ea32110dfd627232d0f2991ad221187be356f19fa8190\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_UNLOCK_USING_PASSPHRASE_UNSUPPORTED "\n");
#endif
}

BOOST_AUTO_TEST_CASE(ec_unlock__invoke__unlock_4_ec_multiply__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_unlock);
    command.set_secret_argument({ "6PgGWtx25kUg8QWvwuJAgorN6k9FbE25rv5dMRwu5SKMnfpfVe5mar2ngH" });
    command.set_passphrase_argument({ "ΜΟΛΩΝ ΛΑΒΕ" });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("ca2759aa4adb0f96c414f36abeb8db59342985be9fa50faac228c8e7d90e3006\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_UNLOCK_USING_PASSPHRASE_UNSUPPORTED "\n");
#endif
}

BOOST_AUTO_TEST_CASE(ec_unlock__invoke__unlock_5_ec_multiply__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_unlock);
    command.set_secret_argument({ "6PfPAw5HErFdzMyBvGMwSfSWjKmzgm3jDg7RxQyVCSSBJFZLAZ6hVupmpn" });
    command.set_passphrase_argument({ "libbitcoin test" });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("fb4bfb0bfe151d524b0b11983b9f826d6a0bc7f7bdc480864a1b557ff0c59eb4\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_UNLOCK_USING_PASSPHRASE_UNSUPPORTED "\n");
#endif
}

BOOST_AUTO_TEST_CASE(ec_unlock__invoke__unlock_6_ec_multiply__okay_if_icu)
{
    BX_DECLARE_COMMAND(ec_unlock);
    command.set_secret_argument({ "6PfU2yS6DUHjgH8wmsJRT1rHWXRofmDV5UJ3dypocew56BDcw5TQJXFYfm" });
    command.set_passphrase_argument({ "Libbitcoin BIP38 Test Vector" });
#ifdef WITH_ICU
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("97c745cc980e5a070e12d0bff3f539b70748aadb406045fc1b42d4ded559a564\n");
#else
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_UNLOCK_USING_PASSPHRASE_UNSUPPORTED "\n");
#endif
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
