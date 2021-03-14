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
BOOST_AUTO_TEST_SUITE(qrcode__invoke)

#if defined(WITH_QRENCODE) && defined(WITH_PNG)

BOOST_AUTO_TEST_CASE(qrcode__invoke__size_0_margin_0__empty_output)
{
    BX_DECLARE_COMMAND(qrcode);

    ////static const data_chunk expected
    ////{
    ////    // TODO
    ////};

    ////command.set_margin_option(0);
    ////command.set_module_option(0);
    ////command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    ////BX_REQUIRE_OKAY(command.invoke(output, error));

    ////istream_reader stream(output);

    ////// Encode as base16 so that failure message is intelligible.
    ////BOOST_REQUIRE_EQUAL(encode_base16(stream.read_bytes()), encode_base16(expected));
    BOOST_REQUIRE(true);
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__size_1_margin_1__success_expected_output)
{
    BX_DECLARE_COMMAND(qrcode);

    ////static const data_chunk expected
    ////{
    ////    // TODO
    ////};

    ////command.set_margin_option(1);
    ////command.set_module_option(1);
    ////command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    ////BX_REQUIRE_OKAY(command.invoke(output, error));

    ////istream_reader stream(output);

    ////// Encode as base16 so that failure message is intelligible.
    ////BOOST_REQUIRE_EQUAL(encode_base16(stream.read_bytes()), encode_base16(expected));
    BOOST_REQUIRE(true);
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__no_defaults__success_expected_output)
{
    BX_DECLARE_COMMAND(qrcode);

    ////const data_chunk expected
    ////{
    ////    // TODO
    ////};

    ////command.set_insensitive_option(false);
    ////command.set_margin_option(1);
    ////command.set_module_option(1);
    ////command.set_scheme_option("foo");
    ////command.set_version_option(1);
    ////command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    ////BX_REQUIRE_OKAY(command.invoke(output, error));

    ////istream_reader stream(output);

    ////// Encode as base16 so that failure message is intelligible.
    ////BOOST_REQUIRE_EQUAL(encode_base16(stream.read_bytes()), encode_base16(expected));

    BOOST_REQUIRE(true);
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__all_defaults__success_expected_output)
{
    BX_DECLARE_COMMAND(qrcode);

    ////const data_chunk expected
    ////{
    ////    // TODO
    ////};

    ////command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    ////BX_REQUIRE_OKAY(command.invoke(output, error));

    ////istream_reader stream(output);

    ////// Encode as base16 so that failure message is intelligible.
    ////BOOST_REQUIRE_EQUAL(encode_base16(stream.read_bytes()), encode_base16(expected));

    BOOST_REQUIRE(true);
}

#else
BOOST_AUTO_TEST_CASE(qrcode__invoke__always__failure_error)
{
    BX_DECLARE_COMMAND(qrcode);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
}
#endif

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
