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

BOOST_AUTO_TEST_CASE(qrcode__invoke__invalid_version__failure_error)
{
    BX_DECLARE_COMMAND(qrcode);

    command.set_version_option(bc::system::wallet::qr_code::maximum_version + 1u);
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_QRCODE_MAXIMUM_VERSION "\n");
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__invalid_margin__failure_error)
{
    BX_DECLARE_COMMAND(qrcode);

    // This maring size will create an oversized image.
    command.set_margin_option(bc::max_uint16);
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_QRCODE_MAXIMUM_SIZE "\n");
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__invalid_module__failure_error)
{
    BX_DECLARE_COMMAND(qrcode);

    // This module size will create an oversized image.
    command.set_module_option(bc::max_uint16);
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_QRCODE_MAXIMUM_SIZE "\n");
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__invalid_scheme__failure_error)
{
    BX_DECLARE_COMMAND(qrcode);

    // This scheme will create an oversized image.
    command.set_scheme_option(std::string(bc::max_uint16, 's'));
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_QRCODE_MAXIMUM_SIZE "\n");
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__margin_0_module_0_version_0_scheme_bitcoin__success_empty_image)
{
    BX_DECLARE_COMMAND(qrcode);

    static const data_chunk expected
    {
        // TIFF metadata.
        0x4d, 0x4d,
        0x00, 0x2a,
        0x00, 0x00, 0x00, 0x08,

        0x00, 0x0a,

        0x01, 0x00,
        0x00, 0x04,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x00,

        0x01, 0x01,
        0x00, 0x04,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x00,

        0x01, 0x03,
        0x00, 0x03,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x01,
        0x00, 0x00,
 
        0x01, 0x06,
        0x00, 0x03,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00,
        0x00, 0x00,
 
        0x01, 0x11,
        0x00, 0x04,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x9c,

        0x01, 0x16,
        0x00, 0x04,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x00,

        0x01, 0x17,
        0x00, 0x04,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x00,

        0x01, 0x1a,
        0x00, 0x05,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x88,

        0x01, 0x1b,
        0x00, 0x05,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x90,

        0x01, 0x28,
        0x00, 0x03,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x01,
        0x00, 0x00,

        0x00, 0x00, 0x00, 0x00,

        0x00, 0x00,

        0x00, 0x00, 0x00, 0x48,
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x48,
        0x00, 0x00, 0x00, 0x01,

        // Delimiter.
        0xba, 0xad, 0xf0, 0x0d

        // Image data (empty).
    };

    command.set_margin_option(0);
    command.set_module_option(0);
    command.set_version_option(0);
    command.set_scheme_option("bitcoin");
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_OKAY(command.invoke(output, error));

    istream_reader stream(output);

    // Encode as base16 so that failure message is intelligible.
    BOOST_REQUIRE_EQUAL(encode_base16(stream.read_bytes()), encode_base16(expected));
}

BOOST_AUTO_TEST_CASE(qrcode__invoke__non_default_values__success_expected_size)
{
    BX_DECLARE_COMMAND(qrcode);

    command.set_margin_option(8);
    command.set_module_option(16);
    command.set_version_option(3);
    command.set_scheme_option("shitcoin");
    command.set_payment_address_argument({ "12u8rC4Pxih4m59eApanRDodXcPxWiaKgg" });
    BX_REQUIRE_OKAY(command.invoke(output, error));

    istream_reader stream(output);
    BOOST_REQUIRE_EQUAL(stream.read_bytes().size(), 28956u);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
