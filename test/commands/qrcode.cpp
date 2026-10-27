/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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

BOOST_AUTO_TEST_CASE(qrcode__invoke__pixels_0__failure_error)
{
    BX_DECLARE_COMMAND(qrcode);

    // This module size will create an empty image.
    command.set_pixels_option(0);
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_QRCODE_MINIMUM_SIZE "\n");
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__invalid_pixels__failure_error)
{
    BX_DECLARE_COMMAND(qrcode);

    // This module size will create an oversized image.
    command.set_pixels_option(max_uint16);
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_QRCODE_MAXIMUM_SIZE "\n");
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__invalid_scheme__failure_error)
{
    BX_DECLARE_COMMAND(qrcode);

    // This scheme will create an oversized image.
    command.set_scheme_option(std::string(max_uint16, 's'));
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    command.set_pixels_option(8);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_QRCODE_MAXIMUM_SIZE "\n");
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__invalid_margin__failure_error)
{
    BX_DECLARE_COMMAND(qrcode);

    // This margin size will create an oversized image.
    command.set_margin_option(max_uint16);
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    command.set_pixels_option(8);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_QRCODE_MAXIMUM_SIZE "\n");
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__invalid_version__failure_error)
{
    BX_DECLARE_COMMAND(qrcode);

    // Tha maximum version is 40, so this addition does not overflow.
    command.set_version_option(wallet::qr_code::maximum_version + 1u);
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    command.set_pixels_option(8);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_QRCODE_MAXIMUM_VERSION "\n");
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__non_default_values__success_expected_size)
{
    BX_DECLARE_COMMAND(qrcode);

    command.set_margin_option(4);
    command.set_pixels_option(4);
    command.set_version_option(4);
    command.set_scheme_option("shitcoin");
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_OKAY(command.invoke(output, error));

    system::read::bytes::istream reader(output);
    BOOST_REQUIRE_EQUAL(reader.read_bytes().size(), 2728u);
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__minimal_size__success_expected)
{
    BX_DECLARE_COMMAND(qrcode);

    static const data_chunk expected
    {
        // PNG signature, header, image data and trailer.
        0x89, 0x50, 0x4e, 0x47,
        0x0d, 0x0a, 0x1a, 0x0a,
        0x00, 0x00, 0x00, 0x0d,
        0x49, 0x48, 0x44, 0x52,
        0x00, 0x00, 0x00, 0x1d,
        0x00, 0x00, 0x00, 0x1d,
        0x01, 0x00, 0x00, 0x00,
        0x00, 0x7e, 0xe8, 0x5a,
        0xa2, 0x00, 0x00, 0x00,
        0x9c, 0x49, 0x44, 0x41,
        0x54, 0x78, 0x01, 0x01,
        0x91, 0x00, 0x6e, 0xff,
        0x00, 0x01, 0xb3, 0x0c,
        0x07, 0x00, 0x7d, 0xc4,
        0x4d, 0xf7, 0x00, 0x45,
        0x11, 0x7d, 0x17, 0x00,
        0x45, 0x88, 0xcd, 0x17,
        0x00, 0x45, 0xdd, 0xdd,
        0x17, 0x00, 0x7d, 0xbb,
        0x8d, 0xf7, 0x00, 0x01,
        0x55, 0x54, 0x07, 0x00,
        0xff, 0x11, 0x3f, 0xff,
        0x00, 0x10, 0x4c, 0x79,
        0xdf, 0x00, 0xc7, 0x4c,
        0xc1, 0x97, 0x00, 0x19,
        0xbb, 0xd3, 0x57, 0x00,
        0xe3, 0xef, 0x37, 0xff,
        0x00, 0x39, 0x77, 0x24,
        0xa7, 0x00, 0xe7, 0x63,
        0x34, 0xb7, 0x00, 0x84,
        0xc5, 0x99, 0x67, 0x00,
        0x63, 0x51, 0x0e, 0x67,
        0x00, 0x64, 0xcd, 0x75,
        0xd7, 0x00, 0xbb, 0xad,
        0x15, 0xb7, 0x00, 0x60,
        0x7b, 0xd6, 0x37, 0x00,
        0x9f, 0xaf, 0xae, 0x3f,
        0x00, 0x78, 0xd6, 0x30,
        0x37, 0x00, 0xff, 0x62,
        0x57, 0x77, 0x00, 0x01,
        0x05, 0xc5, 0x57, 0x00,
        0x7d, 0x30, 0xb7, 0x67,
        0x00, 0x45, 0x4d, 0x70,
        0x17, 0x00, 0x45, 0xcd,
        0x1e, 0x27, 0x00, 0x45,
        0x3b, 0xb6, 0x57, 0x00,
        0x7d, 0x4e, 0x8e, 0xef,
        0x00, 0x01, 0x76, 0x21,
        0xa7, 0x45, 0x5a, 0x35,
        0x29, 0x9b, 0xdf, 0x03,
        0xac, 0x00, 0x00, 0x00,
        0x00, 0x49, 0x45, 0x4e,
        0x44, 0xae, 0x42, 0x60,
        0x82
    };

    command.set_margin_option(0);
    command.set_pixels_option(1);
    command.set_version_option(0);
    command.set_scheme_option("");
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_OKAY(command.invoke(output, error));

    system::read::bytes::istream reader(output);

    // Encode as base16 so that failure message is intelligible.
    BOOST_REQUIRE_EQUAL(encode_base16(reader.read_bytes()), encode_base16(expected));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
