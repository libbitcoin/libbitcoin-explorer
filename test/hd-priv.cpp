/*
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
#include <iostream>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <sx/sx.hpp>
#include "command.hpp"

SX_USING_NAMESPACES()

// This is a namespace for tests by class/file__method/function.
BOOST_AUTO_TEST_SUITE(hd_priv__invoke)

BOOST_AUTO_TEST_CASE(hd_priv__invoke__bogus_secret__throws_invalid_option_value)
{
    // $ sx hd-priv bogus
    SX_DECLARE_COMMAND(hd_priv);
    SX_REQUIRE_INVALID_OPTION_VALUE(command.set_secret_argument({ "bogus" }));
}

//// TODO: trigger SX_HD_PRIV_DERIVATION_ERROR
//BOOST_AUTO_TEST_CASE(hd_priv__invoke__hard_bogus_index__failure_error)
//{
//    // $ sx embed-addr bogus
//    SX_DECLARE_COMMAND(hd_priv);
//    command.set_index_argument(1 << 31);
//    command.set_hard_option(true);
//    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
//    SX_REQUIRE_ERROR(SX_HD_PRIV_DERIVATION_ERROR "\n");
//}

// https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-1

BOOST_AUTO_TEST_CASE(hd_priv__invoke__vector1_hard_0__okay_output)
{
    // $ sx embed-addr bogus
    SX_DECLARE_COMMAND(hd_priv);
    command.set_hard_option(true);
    command.set_index_argument(0);
    command.set_secret_argument({ "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xprv9uHRZZhk6KAJC1avXpDAp4MDc3sQKNxDiPvvkX8Br5ngLNv1TxvUxt4cV1rGL5hj6KCesnDYUhd7oWgT11eZG7XnxHrnYeSvkzY7d2bhkJ7\n");
}

BOOST_AUTO_TEST_CASE(hd_priv__invoke__vector1_soft_1__okay_output)
{
    // $ sx embed-addr bogus
    SX_DECLARE_COMMAND(hd_priv);
    command.set_hard_option(false);
    command.set_index_argument(1);
    command.set_secret_argument({ "xprv9uHRZZhk6KAJC1avXpDAp4MDc3sQKNxDiPvvkX8Br5ngLNv1TxvUxt4cV1rGL5hj6KCesnDYUhd7oWgT11eZG7XnxHrnYeSvkzY7d2bhkJ7" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xprv9wTYmMFdV23N2TdNG573QoEsfRrWKQgWeibmLntzniatZvR9BmLnvSxqu53Kw1UmYPxLgboyZQaXwTCg8MSY3H2EU4pWcQDnRnrVA1xe8fs\n");
}

// https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-2

BOOST_AUTO_TEST_CASE(hd_priv__invoke__vector2_hard_0__okay_output)
{
    // $ sx embed-addr bogus
    SX_DECLARE_COMMAND(hd_priv);
    command.set_hard_option(false);
    command.set_index_argument(0);
    command.set_secret_argument({ "xprv9s21ZrQH143K31xYSDQpPDxsXRTUcvj2iNHm5NUtrGiGG5e2DtALGdso3pGz6ssrdK4PFmM8NSpSBHNqPqm55Qn3LqFtT2emdEXVYsCzC2U" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xprv9vHkqa6EV4sPZHYqZznhT2NPtPCjKuDKGY38FBWLvgaDx45zo9WQRUT3dKYnjwih2yJD9mkrocEZXo1ex8G81dwSM1fwqWpWkeS3v86pgKt\n");
}

BOOST_AUTO_TEST_CASE(hd_priv__invoke__vector2_hard_2147483647__okay_output)
{
    // $ sx embed-addr bogus
    SX_DECLARE_COMMAND(hd_priv);
    command.set_hard_option(true);
    command.set_index_argument(2147483647);
    command.set_secret_argument({ "xprv9vHkqa6EV4sPZHYqZznhT2NPtPCjKuDKGY38FBWLvgaDx45zo9WQRUT3dKYnjwih2yJD9mkrocEZXo1ex8G81dwSM1fwqWpWkeS3v86pgKt" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xprv9wSp6B7kry3Vj9m1zSnLvN3xH8RdsPP1Mh7fAaR7aRLcQMKTR2vidYEeEg2mUCTAwCd6vnxVrcjfy2kRgVsFawNzmjuHc2YmYRmagcEPdU9\n");
}


BOOST_AUTO_TEST_SUITE_END()