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
#include "command.hpp"

SX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(hd_pub__invoke)

// https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-1

// public derivation

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector1_public_m_0h__failure_error)
{
    // $ sx hd-pub xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gZ29ESFjqJoCu1Rupje8YtGqsefD265TMg7usUDFdp6W1EGMcet8 0 --hard
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(true);
    command.set_index_option(0);
    command.set_key_argument({ "xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gZ29ESFjqJoCu1Rupje8YtGqsefD265TMg7usUDFdp6W1EGMcet8" });
    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
    SX_REQUIRE_ERROR(SX_HD_PUB_HARD_OPTION_CONFLICT "\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector1_public_m_0h_1__okay_output)
{
    // $ sx hd-pub xpub68Gmy5EdvgibQVfPdqkBBCHxA5htiqg55crXYuXoQRKfDBFA1WEjWgP6LHhwBZeNK1VTsfTFUHCdrfp1bgwQ9xv5ski8PX9rL2dZXvgGDnw 1
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(false);
    command.set_index_option(1);
    command.set_key_argument({ "xpub68Gmy5EdvgibQVfPdqkBBCHxA5htiqg55crXYuXoQRKfDBFA1WEjWgP6LHhwBZeNK1VTsfTFUHCdrfp1bgwQ9xv5ski8PX9rL2dZXvgGDnw" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub6ASuArnXKPbfEwhqN6e3mwBcDTgzisQN1wXN9BJcM47sSikHjJf3UFHKkNAWbWMiGj7Wf5uMash7SyYq527Hqck2AxYysAA7xmALppuCkwQ\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector1_public_m_0h_1_2h__failure_error)
{
    // $ sx hd-pub xpub6ASuArnXKPbfEwhqN6e3mwBcDTgzisQN1wXN9BJcM47sSikHjJf3UFHKkNAWbWMiGj7Wf5uMash7SyYq527Hqck2AxYysAA7xmALppuCkwQ 2 --hard
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(true);
    command.set_index_option(2);
    command.set_key_argument({ "xpub6ASuArnXKPbfEwhqN6e3mwBcDTgzisQN1wXN9BJcM47sSikHjJf3UFHKkNAWbWMiGj7Wf5uMash7SyYq527Hqck2AxYysAA7xmALppuCkwQ" });
    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
    SX_REQUIRE_ERROR(SX_HD_PUB_HARD_OPTION_CONFLICT "\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector1_public_m_0h_1_2h_2__okay_output)
{
    // $ sx hd-pub xpub6D4BDPcP2GT577Vvch3R8wDkScZWzQzMMUm3PWbmWvVJrZwQY4VUNgqFJPMM3No2dFDFGTsxxpG5uJh7n7epu4trkrX7x7DogT5Uv6fcLW5 2
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(false);
    command.set_index_option(2);
    command.set_key_argument({ "xpub6D4BDPcP2GT577Vvch3R8wDkScZWzQzMMUm3PWbmWvVJrZwQY4VUNgqFJPMM3No2dFDFGTsxxpG5uJh7n7epu4trkrX7x7DogT5Uv6fcLW5" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub6FHa3pjLCk84BayeJxFW2SP4XRrFd1JYnxeLeU8EqN3vDfZmbqBqaGJAyiLjTAwm6ZLRQUMv1ZACTj37sR62cfN7fe5JnJ7dh8zL4fiyLHV\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector1_public_m_0h_1_2h_2_1000000000__okay_output)
{
    // $ sx hd-pub xpub6FHa3pjLCk84BayeJxFW2SP4XRrFd1JYnxeLeU8EqN3vDfZmbqBqaGJAyiLjTAwm6ZLRQUMv1ZACTj37sR62cfN7fe5JnJ7dh8zL4fiyLHV 2
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(false);
    command.set_index_option(1000000000);
    command.set_key_argument({ "xpub6FHa3pjLCk84BayeJxFW2SP4XRrFd1JYnxeLeU8EqN3vDfZmbqBqaGJAyiLjTAwm6ZLRQUMv1ZACTj37sR62cfN7fe5JnJ7dh8zL4fiyLHV" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub6H1LXWLaKsWFhvm6RVpEL9P4KfRZSW7abD2ttkWP3SSQvnyA8FSVqNTEcYFgJS2UaFcxupHiYkro49S8yGasTvXEYBVPamhGW6cFJodrTHy\n");
}

// private derivation

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector1_private_m_0h__okay_output)
{
    // $ sx hd-pub xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi 0 --hard
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(true);
    command.set_index_option(0);
    command.set_key_argument({ "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub68Gmy5EdvgibQVfPdqkBBCHxA5htiqg55crXYuXoQRKfDBFA1WEjWgP6LHhwBZeNK1VTsfTFUHCdrfp1bgwQ9xv5ski8PX9rL2dZXvgGDnw\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector1_private_m_0h_1__okay_output)
{
    // $ sx hd-pub xprv9uHRZZhk6KAJC1avXpDAp4MDc3sQKNxDiPvvkX8Br5ngLNv1TxvUxt4cV1rGL5hj6KCesnDYUhd7oWgT11eZG7XnxHrnYeSvkzY7d2bhkJ7 1
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(false);
    command.set_index_option(1);
    command.set_key_argument({ "xprv9uHRZZhk6KAJC1avXpDAp4MDc3sQKNxDiPvvkX8Br5ngLNv1TxvUxt4cV1rGL5hj6KCesnDYUhd7oWgT11eZG7XnxHrnYeSvkzY7d2bhkJ7" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub6ASuArnXKPbfEwhqN6e3mwBcDTgzisQN1wXN9BJcM47sSikHjJf3UFHKkNAWbWMiGj7Wf5uMash7SyYq527Hqck2AxYysAA7xmALppuCkwQ\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector1_private_m_0h_1_2h__okay_output)
{
    // $ sx hd-pub xprv9wTYmMFdV23N2TdNG573QoEsfRrWKQgWeibmLntzniatZvR9BmLnvSxqu53Kw1UmYPxLgboyZQaXwTCg8MSY3H2EU4pWcQDnRnrVA1xe8fs 2 --hard
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(true);
    command.set_index_option(2);
    command.set_key_argument({ "xprv9wTYmMFdV23N2TdNG573QoEsfRrWKQgWeibmLntzniatZvR9BmLnvSxqu53Kw1UmYPxLgboyZQaXwTCg8MSY3H2EU4pWcQDnRnrVA1xe8fs" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub6D4BDPcP2GT577Vvch3R8wDkScZWzQzMMUm3PWbmWvVJrZwQY4VUNgqFJPMM3No2dFDFGTsxxpG5uJh7n7epu4trkrX7x7DogT5Uv6fcLW5\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector1_private_m_0h_1_2h_2__okay_output)
{
    // $ sx hd-pub xprv9z4pot5VBttmtdRTWfWQmoH1taj2axGVzFqSb8C9xaxKymcFzXBDptWmT7FwuEzG3ryjH4ktypQSAewRiNMjANTtpgP4mLTj34bhnZX7UiM 2
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(false);
    command.set_index_option(2);
    command.set_key_argument({ "xprv9z4pot5VBttmtdRTWfWQmoH1taj2axGVzFqSb8C9xaxKymcFzXBDptWmT7FwuEzG3ryjH4ktypQSAewRiNMjANTtpgP4mLTj34bhnZX7UiM" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub6FHa3pjLCk84BayeJxFW2SP4XRrFd1JYnxeLeU8EqN3vDfZmbqBqaGJAyiLjTAwm6ZLRQUMv1ZACTj37sR62cfN7fe5JnJ7dh8zL4fiyLHV\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector1_private_m_0h_1_2h_2_1000000000__okay_output)
{
    // $ sx hd-pub xprvA2JDeKCSNNZky6uBCviVfJSKyQ1mDYahRjijr5idH2WwLsEd4Hsb2Tyh8RfQMuPh7f7RtyzTtdrbdqqsunu5Mm3wDvUAKRHSC34sJ7in334 2
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(false);
    command.set_index_option(1000000000);
    command.set_key_argument({ "xprvA2JDeKCSNNZky6uBCviVfJSKyQ1mDYahRjijr5idH2WwLsEd4Hsb2Tyh8RfQMuPh7f7RtyzTtdrbdqqsunu5Mm3wDvUAKRHSC34sJ7in334" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub6H1LXWLaKsWFhvm6RVpEL9P4KfRZSW7abD2ttkWP3SSQvnyA8FSVqNTEcYFgJS2UaFcxupHiYkro49S8yGasTvXEYBVPamhGW6cFJodrTHy\n");
}

// https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vector-2

// public derivation

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector2_public_m_0__okay_output)
{
    // $ sx hd-pub xpub661MyMwAqRbcFW31YEwpkMuc5THy2PSt5bDMsktWQcFF8syAmRUapSCGu8ED9W6oDMSgv6Zz8idoc4a6mr8BDzTJY47LJhkJ8UB7WEGuduB 0
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(false);
    command.set_index_option(0);
    command.set_key_argument({ "xpub661MyMwAqRbcFW31YEwpkMuc5THy2PSt5bDMsktWQcFF8syAmRUapSCGu8ED9W6oDMSgv6Zz8idoc4a6mr8BDzTJY47LJhkJ8UB7WEGuduB" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub69H7F5d8KSRgmmdJg2KhpAK8SR3DjMwAdkxj3ZuxV27CprR9LgpeyGmXUbC6wb7ERfvrnKZjXoUmmDznezpbZb7ap6r1D3tgFxHmwMkQTPH\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector2_public_m_0_2147483647h__failure_error)
{
    // $ sx hd-pub xpub69H7F5d8KSRgmmdJg2KhpAK8SR3DjMwAdkxj3ZuxV27CprR9LgpeyGmXUbC6wb7ERfvrnKZjXoUmmDznezpbZb7ap6r1D3tgFxHmwMkQTPH 2147483647 --hard
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(true);
    command.set_index_option(2147483647);
    command.set_key_argument({ "xpub69H7F5d8KSRgmmdJg2KhpAK8SR3DjMwAdkxj3ZuxV27CprR9LgpeyGmXUbC6wb7ERfvrnKZjXoUmmDznezpbZb7ap6r1D3tgFxHmwMkQTPH" });
    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
    SX_REQUIRE_ERROR(SX_HD_PUB_HARD_OPTION_CONFLICT "\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector2_public_m_0_2147483647h_1__okay_output)
{
    // $ sx hd-pub xpub6ASAVgeehLbnwdqV6UKMHVzgqAG8Gr6riv3Fxxpj8ksbH9ebxaEyBLZ85ySDhKiLDBrQSARLq1uNRts8RuJiHjaDMBU4Zn9h8LZNnBC5y4a 1
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(false);
    command.set_index_option(1);
    command.set_key_argument({ "xpub6ASAVgeehLbnwdqV6UKMHVzgqAG8Gr6riv3Fxxpj8ksbH9ebxaEyBLZ85ySDhKiLDBrQSARLq1uNRts8RuJiHjaDMBU4Zn9h8LZNnBC5y4a" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub6DF8uhdarytz3FWdA8TvFSvvAh8dP3283MY7p2V4SeE2wyWmG5mg5EwVvmdMVCQcoNJxGoWaU9DCWh89LojfZ537wTfunKau47EL2dhHKon\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector2_public_m_0_2147483647h_1_2147483646h__failure_error)
{
    // $ sx hd-pub xpub6DF8uhdarytz3FWdA8TvFSvvAh8dP3283MY7p2V4SeE2wyWmG5mg5EwVvmdMVCQcoNJxGoWaU9DCWh89LojfZ537wTfunKau47EL2dhHKon 2147483646 --hard
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(true);
    command.set_index_option(2147483646);
    command.set_key_argument({ "xpub6DF8uhdarytz3FWdA8TvFSvvAh8dP3283MY7p2V4SeE2wyWmG5mg5EwVvmdMVCQcoNJxGoWaU9DCWh89LojfZ537wTfunKau47EL2dhHKon" });
    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
    SX_REQUIRE_ERROR(SX_HD_PUB_HARD_OPTION_CONFLICT "\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector2_public_m_0_2147483647h_1_2147483646h_2__okay_output)
{
    // $ sx hd-pub xpub6ERApfZwUNrhLCkDtcHTcxd75RbzS1ed54G1LkBUHQVHQKqhMkhgbmJbZRkrgZw4koxb5JaHWkY4ALHY2grBGRjaDMzQLcgJvLJuZZvRcEL 2
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(false);
    command.set_index_option(2);
    command.set_key_argument({ "xpub6ERApfZwUNrhLCkDtcHTcxd75RbzS1ed54G1LkBUHQVHQKqhMkhgbmJbZRkrgZw4koxb5JaHWkY4ALHY2grBGRjaDMzQLcgJvLJuZZvRcEL" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub6FnCn6nSzZAw5Tw7cgR9bi15UV96gLZhjDstkXXxvCLsUXBGXPdSnLFbdpq8p9HmGsApME5hQTZ3emM2rnY5agb9rXpVGyy3bdW6EEgAtqt\n");
}

// private derivation

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector2_private_m_0__okay_output)
{
    // $ sx hd-pub xprv9s21ZrQH143K31xYSDQpPDxsXRTUcvj2iNHm5NUtrGiGG5e2DtALGdso3pGz6ssrdK4PFmM8NSpSBHNqPqm55Qn3LqFtT2emdEXVYsCzC2U 0
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(false);
    command.set_index_option(0);
    command.set_key_argument({ "xprv9s21ZrQH143K31xYSDQpPDxsXRTUcvj2iNHm5NUtrGiGG5e2DtALGdso3pGz6ssrdK4PFmM8NSpSBHNqPqm55Qn3LqFtT2emdEXVYsCzC2U" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub69H7F5d8KSRgmmdJg2KhpAK8SR3DjMwAdkxj3ZuxV27CprR9LgpeyGmXUbC6wb7ERfvrnKZjXoUmmDznezpbZb7ap6r1D3tgFxHmwMkQTPH\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector2_private_m_0_2147483647h__okay_output)
{
    // $ sx hd-pub xprv9vHkqa6EV4sPZHYqZznhT2NPtPCjKuDKGY38FBWLvgaDx45zo9WQRUT3dKYnjwih2yJD9mkrocEZXo1ex8G81dwSM1fwqWpWkeS3v86pgKt 2147483647 --hard
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(true);
    command.set_index_option(2147483647);
    command.set_key_argument({ "xprv9vHkqa6EV4sPZHYqZznhT2NPtPCjKuDKGY38FBWLvgaDx45zo9WQRUT3dKYnjwih2yJD9mkrocEZXo1ex8G81dwSM1fwqWpWkeS3v86pgKt" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub6ASAVgeehLbnwdqV6UKMHVzgqAG8Gr6riv3Fxxpj8ksbH9ebxaEyBLZ85ySDhKiLDBrQSARLq1uNRts8RuJiHjaDMBU4Zn9h8LZNnBC5y4a\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector2_private_m_0_2147483647h_1__okay_output)
{
    // $ sx hd-pub xprv9wSp6B7kry3Vj9m1zSnLvN3xH8RdsPP1Mh7fAaR7aRLcQMKTR2vidYEeEg2mUCTAwCd6vnxVrcjfy2kRgVsFawNzmjuHc2YmYRmagcEPdU9 1
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(false);
    command.set_index_option(1);
    command.set_key_argument({ "xprv9wSp6B7kry3Vj9m1zSnLvN3xH8RdsPP1Mh7fAaR7aRLcQMKTR2vidYEeEg2mUCTAwCd6vnxVrcjfy2kRgVsFawNzmjuHc2YmYRmagcEPdU9" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub6DF8uhdarytz3FWdA8TvFSvvAh8dP3283MY7p2V4SeE2wyWmG5mg5EwVvmdMVCQcoNJxGoWaU9DCWh89LojfZ537wTfunKau47EL2dhHKon\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector2_private_m_0_2147483647h_1_2147483646h__okay_output)
{
    // $ sx hd-pub xprv9zFnWC6h2cLgpmSA46vutJzBcfJ8yaJGg8cX1e5StJh45BBciYTRXSd25UEPVuesF9yog62tGAQtHjXajPPdbRCHuWS6T8XA2ECKADdw4Ef 2147483646 --hard
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(true);
    command.set_index_option(2147483646);
    command.set_key_argument({ "xprv9zFnWC6h2cLgpmSA46vutJzBcfJ8yaJGg8cX1e5StJh45BBciYTRXSd25UEPVuesF9yog62tGAQtHjXajPPdbRCHuWS6T8XA2ECKADdw4Ef" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub6ERApfZwUNrhLCkDtcHTcxd75RbzS1ed54G1LkBUHQVHQKqhMkhgbmJbZRkrgZw4koxb5JaHWkY4ALHY2grBGRjaDMzQLcgJvLJuZZvRcEL\n");
}

BOOST_AUTO_TEST_CASE(hd_pub__invoke__mainnet_vector2_private_m_0_2147483647h_1_2147483646h_2__okay_output)
{
    // $ sx hd-pub xprvA1RpRA33e1JQ7ifknakTFpgNXPmW2YvmhqLQYMmrj4xJXXWYpDPS3xz7iAxn8L39njGVyuoseXzU6rcxFLJ8HFsTjSyQbLYnMpCqE2VbFWc 2
    SX_DECLARE_COMMAND(hd_pub);
    command.set_hard_option(false);
    command.set_index_option(2);
    command.set_key_argument({ "xprvA1RpRA33e1JQ7ifknakTFpgNXPmW2YvmhqLQYMmrj4xJXXWYpDPS3xz7iAxn8L39njGVyuoseXzU6rcxFLJ8HFsTjSyQbLYnMpCqE2VbFWc" });
    SX_REQUIRE_OKAY(command.invoke(input, output, error));
    SX_REQUIRE_OUTPUT("xpub6FnCn6nSzZAw5Tw7cgR9bi15UV96gLZhjDstkXXxvCLsUXBGXPdSnLFbdpq8p9HmGsApME5hQTZ3emM2rnY5agb9rXpVGyy3bdW6EEgAtqt\n");
}

BOOST_AUTO_TEST_SUITE_END()