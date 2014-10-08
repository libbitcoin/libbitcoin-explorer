/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.

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
BOOST_AUTO_TEST_SUITE(hd_private__invoke)

// https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-1

BOOST_AUTO_TEST_CASE(hd_private__invoke__mainnet_vector1_m_0h__okay_output)
{
    BX_DECLARE_COMMAND(hd_private);
    command.set_hard_option(true);
    command.set_index_option(0);
    command.set_hd_private_key_argument({ "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprv9uHRZZhk6KAJC1avXpDAp4MDc3sQKNxDiPvvkX8Br5ngLNv1TxvUxt4cV1rGL5hj6KCesnDYUhd7oWgT11eZG7XnxHrnYeSvkzY7d2bhkJ7\n");
}

BOOST_AUTO_TEST_CASE(hd_private__invoke__mainnet_vector1_m_0h_1__okay_output)
{
    BX_DECLARE_COMMAND(hd_private);
    command.set_hard_option(false);
    command.set_index_option(1);
    command.set_hd_private_key_argument({ "xprv9uHRZZhk6KAJC1avXpDAp4MDc3sQKNxDiPvvkX8Br5ngLNv1TxvUxt4cV1rGL5hj6KCesnDYUhd7oWgT11eZG7XnxHrnYeSvkzY7d2bhkJ7" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprv9wTYmMFdV23N2TdNG573QoEsfRrWKQgWeibmLntzniatZvR9BmLnvSxqu53Kw1UmYPxLgboyZQaXwTCg8MSY3H2EU4pWcQDnRnrVA1xe8fs\n");
}

BOOST_AUTO_TEST_CASE(hd_private__invoke__mainnet_vector1_m_0h_1_2h__okay_output)
{
    BX_DECLARE_COMMAND(hd_private);
    command.set_hard_option(true);
    command.set_index_option(2);
    command.set_hd_private_key_argument({ "xprv9wTYmMFdV23N2TdNG573QoEsfRrWKQgWeibmLntzniatZvR9BmLnvSxqu53Kw1UmYPxLgboyZQaXwTCg8MSY3H2EU4pWcQDnRnrVA1xe8fs" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprv9z4pot5VBttmtdRTWfWQmoH1taj2axGVzFqSb8C9xaxKymcFzXBDptWmT7FwuEzG3ryjH4ktypQSAewRiNMjANTtpgP4mLTj34bhnZX7UiM\n");
}

BOOST_AUTO_TEST_CASE(hd_private__invoke__mainnet_vector1_m_0h_1_2h_2__okay_output)
{
    BX_DECLARE_COMMAND(hd_private);
    command.set_hard_option(false);
    command.set_index_option(2);
    command.set_hd_private_key_argument({ "xprv9z4pot5VBttmtdRTWfWQmoH1taj2axGVzFqSb8C9xaxKymcFzXBDptWmT7FwuEzG3ryjH4ktypQSAewRiNMjANTtpgP4mLTj34bhnZX7UiM" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprvA2JDeKCSNNZky6uBCviVfJSKyQ1mDYahRjijr5idH2WwLsEd4Hsb2Tyh8RfQMuPh7f7RtyzTtdrbdqqsunu5Mm3wDvUAKRHSC34sJ7in334\n");
}

BOOST_AUTO_TEST_CASE(hd_private__invoke__mainnet_vector1_m_0h_1_2h_2_1000000000__okay_output)
{
    BX_DECLARE_COMMAND(hd_private);
    command.set_hard_option(false);
    command.set_index_option(1000000000);
    command.set_hd_private_key_argument({ "xprvA2JDeKCSNNZky6uBCviVfJSKyQ1mDYahRjijr5idH2WwLsEd4Hsb2Tyh8RfQMuPh7f7RtyzTtdrbdqqsunu5Mm3wDvUAKRHSC34sJ7in334" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprvA41z7zogVVwxVSgdKUHDy1SKmdb533PjDz7J6N6mV6uS3ze1ai8FHa8kmHScGpWmj4WggLyQjgPie1rFSruoUihUZREPSL39UNdE3BBDu76\n");
}

// https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-2

BOOST_AUTO_TEST_CASE(hd_private__invoke__mainnet_vector2_m_0__okay_output)
{
    BX_DECLARE_COMMAND(hd_private);
    command.set_hard_option(false);
    command.set_index_option(0);
    command.set_hd_private_key_argument({ "xprv9s21ZrQH143K31xYSDQpPDxsXRTUcvj2iNHm5NUtrGiGG5e2DtALGdso3pGz6ssrdK4PFmM8NSpSBHNqPqm55Qn3LqFtT2emdEXVYsCzC2U" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprv9vHkqa6EV4sPZHYqZznhT2NPtPCjKuDKGY38FBWLvgaDx45zo9WQRUT3dKYnjwih2yJD9mkrocEZXo1ex8G81dwSM1fwqWpWkeS3v86pgKt\n");
}

BOOST_AUTO_TEST_CASE(hd_private__invoke__mainnet_vector2_m_0_2147483647h__okay_output)
{
    BX_DECLARE_COMMAND(hd_private);
    command.set_hard_option(true);
    command.set_index_option(2147483647);
    command.set_hd_private_key_argument({ "xprv9vHkqa6EV4sPZHYqZznhT2NPtPCjKuDKGY38FBWLvgaDx45zo9WQRUT3dKYnjwih2yJD9mkrocEZXo1ex8G81dwSM1fwqWpWkeS3v86pgKt" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprv9wSp6B7kry3Vj9m1zSnLvN3xH8RdsPP1Mh7fAaR7aRLcQMKTR2vidYEeEg2mUCTAwCd6vnxVrcjfy2kRgVsFawNzmjuHc2YmYRmagcEPdU9\n");
}

BOOST_AUTO_TEST_CASE(hd_private__invoke__mainnet_vector2_m_0_2147483647h_1__okay_output)
{
    BX_DECLARE_COMMAND(hd_private);
    command.set_hard_option(false);
    command.set_index_option(1);
    command.set_hd_private_key_argument({ "xprv9wSp6B7kry3Vj9m1zSnLvN3xH8RdsPP1Mh7fAaR7aRLcQMKTR2vidYEeEg2mUCTAwCd6vnxVrcjfy2kRgVsFawNzmjuHc2YmYRmagcEPdU9" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprv9zFnWC6h2cLgpmSA46vutJzBcfJ8yaJGg8cX1e5StJh45BBciYTRXSd25UEPVuesF9yog62tGAQtHjXajPPdbRCHuWS6T8XA2ECKADdw4Ef\n");
}

BOOST_AUTO_TEST_CASE(hd_private__invoke__mainnet_vector2_m_0_2147483647h_1_2147483646h__okay_output)
{
    BX_DECLARE_COMMAND(hd_private);
    command.set_hard_option(true);
    command.set_index_option(2147483646);
    command.set_hd_private_key_argument({ "xprv9zFnWC6h2cLgpmSA46vutJzBcfJ8yaJGg8cX1e5StJh45BBciYTRXSd25UEPVuesF9yog62tGAQtHjXajPPdbRCHuWS6T8XA2ECKADdw4Ef" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprvA1RpRA33e1JQ7ifknakTFpgNXPmW2YvmhqLQYMmrj4xJXXWYpDPS3xz7iAxn8L39njGVyuoseXzU6rcxFLJ8HFsTjSyQbLYnMpCqE2VbFWc\n");
}

BOOST_AUTO_TEST_CASE(hd_private__invoke__mainnet_vector2_m_0_2147483647h_1_2147483646h_2__okay_output)
{
    BX_DECLARE_COMMAND(hd_private);
    command.set_hard_option(false);
    command.set_index_option(2);
    command.set_hd_private_key_argument({ "xprvA1RpRA33e1JQ7ifknakTFpgNXPmW2YvmhqLQYMmrj4xJXXWYpDPS3xz7iAxn8L39njGVyuoseXzU6rcxFLJ8HFsTjSyQbLYnMpCqE2VbFWc" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprvA2nrNbFZABcdryreWet9Ea4LvTJcGsqrMzxHx98MMrotbir7yrKCEXw7nadnHM8Dq38EGfSh6dqA9QWTyefMLEcBYJUuekgW4BYPJcr9E7j\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()