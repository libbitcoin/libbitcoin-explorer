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

#include <string>

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

    istream_reader stream(output);
    BOOST_REQUIRE_EQUAL(stream.read_bytes().size(), 2676u);
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__minimal_size__success_expected)
{
    BX_DECLARE_COMMAND(qrcode);

    static const data_chunk expected
    {
        // TIFF metadata and padding.
        0x4d, 0x4d, 0x00, 0x2a,
        0x00, 0x00, 0x00, 0x08,
        0x00, 0x0a, 0x01, 0x00,
        0x00, 0x04, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x00,
        0x00, 0x1d, 0x01, 0x01,
        0x00, 0x04, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x00,
        0x00, 0x1d, 0x01, 0x03,
        0x00, 0x03, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x01,
        0x00, 0x00, 0x01, 0x06,
        0x00, 0x03, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x11,
        0x00, 0x04, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x00,
        0x00, 0x9c, 0x01, 0x16,
        0x00, 0x04, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x00,
        0x00, 0x1d, 0x01, 0x17,
        0x00, 0x04, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x00,
        0x00, 0x74, 0x01, 0x1a,
        0x00, 0x05, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x00,
        0x00, 0x88, 0x01, 0x1b,
        0x00, 0x05, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x00,
        0x00, 0x90, 0x01, 0x28,
        0x00, 0x03, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x48,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x48,
        0x00, 0x00, 0x00, 0x01,

        // Libbitcoin delimiter.
        0xba, 0xad, 0xf0, 0x0d,

        // Image data.
        0xfe, 0x4c, 0xf3, 0xf8,
        0x82, 0x3b, 0xb2, 0x08,
        0xba, 0xee, 0x82, 0xe8,
        0xba, 0x77, 0x32, 0xe8,
        0xba, 0x22, 0x22, 0xe8,
        0x82, 0x44, 0x72, 0x08,
        0xfe, 0xaa, 0xab, 0xf8,
        0x00, 0xee, 0xc0, 0x00,
        0xef, 0xb3, 0x86, 0x20,
        0x38, 0xb3, 0x3e, 0x68,
        0xe6, 0x44, 0x2c, 0xa8,
        0x1c, 0x10, 0xc8, 0x00,
        0xc6, 0x88, 0xdb, 0x58,
        0x18, 0x9c, 0xcb, 0x48,
        0x7b, 0x3a, 0x66, 0x98,
        0x9c, 0xae, 0xf1, 0x98,
        0x9b, 0x32, 0x8a, 0x28,
        0x44, 0x52, 0xea, 0x48,
        0x9f, 0x84, 0x29, 0xc8,
        0x60, 0x50, 0x51, 0xc0,
        0x87, 0x29, 0xcf, 0xc8,
        0x00, 0x9d, 0xa8, 0x88,
        0xfe, 0xfa, 0x3a, 0xa8,
        0x82, 0xcf, 0x48, 0x98,
        0xba, 0xb2, 0x8f, 0xe8,
        0xba, 0x32, 0xe1, 0xd8,
        0xba, 0xc4, 0x49, 0xa8,
        0x82, 0xb1, 0x71, 0x10,
        0xfe, 0x89, 0xde, 0x58
    };

    command.set_margin_option(0);
    command.set_pixels_option(1);
    command.set_version_option(0);
    command.set_scheme_option("");
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_OKAY(command.invoke(output, error));

    istream_reader stream(output);

    // Encode as base16 so that failure message is intelligible.
    BOOST_REQUIRE_EQUAL(encode_base16(stream.read_bytes()), encode_base16(expected));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
