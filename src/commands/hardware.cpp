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

#include <bitcoin/explorer/commands/hardware.hpp>

#include <format>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

// The "try" functions are safe for instructions not compiled in.
console_result hardware::invoke(std::ostream& output, std::ostream&)
{
#if defined(HAVE_ARM)
    output << BX_HARDWARE_HEADER_ARM64 << std::endl;
    output << std::format("aes......... " BX_HARDWARE_COMPILED, try_neon_aes(), have_neon_aes) << std::endl;
    output << std::format("sha2........ " BX_HARDWARE_COMPILED, try_neon_sha2(), have_neon_sha) << std::endl;
    output << std::format("sha3........ " BX_HARDWARE_COMPILED, try_neon_sha3(), have_neon_sha3) << std::endl;
    output << std::format("neon........ " BX_HARDWARE_COMPILED, try_neon(), have_neon) << std::endl;

    if (try_neon_sha2() && !have_neon_sha)
        output << BX_HARDWARE_SHA_UNCOMPILED << std::endl;
#else
    output << BX_HARDWARE_HEADER_X64 << std::endl;
    output << std::format("aesni....... " BX_HARDWARE_COMPILED, try_aesni(), have_aesni) << std::endl;
    output << std::format("vaes........ " BX_HARDWARE_COMPILED, try_vaes(), have_vaes) << std::endl;
    output << std::format("shani....... " BX_HARDWARE_COMPILED, try_shani(), have_shani) << std::endl;
    output << std::format("sha512...... " BX_HARDWARE_COMPILED, try_sha512(), have_sha512) << std::endl;
    output << std::format("sse41....... " BX_HARDWARE_COMPILED, try_sse41(), have_sse41) << std::endl;
    output << std::format("avx2........ " BX_HARDWARE_COMPILED, try_avx2(), have_avx2) << std::endl;
    output << std::format("avx512...... " BX_HARDWARE_COMPILED, try_avx512(), have_avx512) << std::endl;
    output << std::format("avxifma..... " BX_HARDWARE_COMPILED, try_avxifma(), have_avxifma) << std::endl;
    output << std::format("avx512ifma.. " BX_HARDWARE_COMPILED, try_avx512ifma(), have_avx512ifma) << std::endl;

    if (try_shani() && !have_shani)
        output << BX_HARDWARE_SHA_UNCOMPILED << std::endl;

    if (try_avx2() && !have_avx2)
        output << BX_HARDWARE_AVX2_UNCOMPILED << std::endl;
#endif

    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
