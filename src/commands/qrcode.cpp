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

#include <bitcoin/explorer/commands/qrcode.hpp>

#include <iostream>
#include <bitcoin/explorer/define.hpp>

#if defined WITH_QRENCODE && defined WITH_LIBPNG
#include "png.h"
#include "qrencode.h"
#endif

using namespace bc::explorer;
using namespace bc::explorer::commands;

/*
  The following constants and write_png method are based on:

  https://github.com/fukuchi/libqrencode/blob/3.4/qrenc.c
*/

#if defined WITH_QRENCODE && defined WITH_LIBPNG
static constexpr int dpi = 72;
static constexpr int version = 0;
static constexpr int margin = 2;
static constexpr QRencodeMode hint = QR_MODE_8;
static constexpr QRecLevel level = QR_ECLEVEL_L;
static constexpr int casesensitive = 1;
static constexpr int INCHES_PER_METER = (100.0 / 2.54);
static constexpr unsigned int fg_color[4] = {0, 0, 0, 255};
static constexpr unsigned int bg_color[4] = {255, 255, 255, 255};


static bool write_png(QRcode *qrcode, uint32_t size, std::string outfile);
#endif

console_result qrcode::invoke(std::ostream& output, std::ostream& error)
{
#if defined WITH_QRENCODE && defined WITH_LIBPNG
    // Bound parameters.
    const auto& address = get_payment_address_argument();
    const auto& filename = get_filename_argument();
    const auto& size = get_size_option();

    std::string qr_string = "bitcoin:" + address.encoded();

    QRcode* qrcode = QRcode_encodeString(
        qr_string.c_str(), version, level, hint, casesensitive);

    if (qrcode && write_png(qrcode, size, filename.c_str()))
        return console_result::okay;

    error << BX_QRCODE_WRITE_ERROR << std::endl;
    return console_result::failure;
#else
    error << BX_QRCODE_REQUIRES_QRENCODE_AND_LIBPNG << std::endl;
    return console_result::failure;
#endif
}

#if defined WITH_QRENCODE && defined WITH_LIBPNG
static bool write_png(QRcode *qrcode, uint32_t size, std::string outfile)
{
    static FILE *fp; // avoid clobbering by setjmp.
    png_structp png_ptr;
    png_infop info_ptr;
    png_colorp palette;
    png_byte alpha_values[2];
    unsigned char *row, *p, *q;
    int x, y, xx, yy, bit;
    int realwidth;

    realwidth = (qrcode->width + margin * 2) * size;
    row = (unsigned char *)malloc((realwidth + 7) / 8);
    if(row == NULL) {
        return false;
    }

    if(outfile[0] == '-' && outfile[1] == '\0') {
        fp = stdout;
    } else {
        fp = fopen(outfile.c_str(), "wb");
        if(fp == NULL) {
            return false;
        }
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(png_ptr == NULL) {
        return false;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if(info_ptr == NULL) {
        return false;
    }

    if(setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return false;
    }

    palette = (png_colorp) malloc(sizeof(png_color) * 2);
    if(palette == NULL) {
        return false;
    }
    palette[0].red   = fg_color[0];
    palette[0].green = fg_color[1];
    palette[0].blue  = fg_color[2];
    palette[1].red   = bg_color[0];
    palette[1].green = bg_color[1];
    palette[1].blue  = bg_color[2];
    alpha_values[0] = fg_color[3];
    alpha_values[1] = bg_color[3];
    png_set_PLTE(png_ptr, info_ptr, palette, 2);
    png_set_tRNS(png_ptr, info_ptr, alpha_values, 2, NULL);

    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr,
                 realwidth, realwidth,
                 1,
                 PNG_COLOR_TYPE_PALETTE,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);
    png_set_pHYs(png_ptr, info_ptr,
                 dpi * INCHES_PER_METER,
                 dpi * INCHES_PER_METER,
                 PNG_RESOLUTION_METER);
    png_write_info(png_ptr, info_ptr);

    /* top margin */
    memset(row, 0xff, (realwidth + 7) / 8);
    for(y=0; y<margin * size; y++) {
        png_write_row(png_ptr, row);
    }

    /* data */
    p = qrcode->data;
    for(y=0; y<qrcode->width; y++) {
        bit = 7;
        memset(row, 0xff, (realwidth + 7) / 8);
        q = row;
        q += margin * size / 8;
        bit = 7 - (margin * size % 8);
        for(x=0; x<qrcode->width; x++) {
            for(xx=0; xx<size; xx++) {
                *q ^= (*p & 1) << bit;
                bit--;
                if(bit < 0) {
                    q++;
                    bit = 7;
                }
            }
            p++;
        }
        for(yy=0; yy<size; yy++) {
            png_write_row(png_ptr, row);
        }
    }
    /* bottom margin */
    memset(row, 0xff, (realwidth + 7) / 8);
    for(y=0; y<margin * size; y++) {
        png_write_row(png_ptr, row);
    }

    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    fclose(fp);
    free(row);
    free(palette);

    return true;
}
#endif
