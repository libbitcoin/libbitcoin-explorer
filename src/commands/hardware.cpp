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
#else
    output << BX_HARDWARE_HEADER_X64 << std::endl;
#endif
    for (const auto& extension: extension_states())
        output << std::format("{:.<12} " BX_HARDWARE_COMPILED, extension.name,
            extension.platform, extension.compiled) << std::endl;

    output << std::format(BX_HARDWARE_BUILD, build_name("bx", detected_tags()),
        build_name("bx", compiled_tags())) << std::endl;

    const auto cuda = cuda_device();
    const auto compiled = batched::compiled();
    const auto unsupported = cuda && compiled && !batched::accelerated();

    if (unsupported)
    {
        output << std::format("cuda........ " BX_HARDWARE_INCOMPATIBLE, cuda, compiled) << std::endl;
    }
    else
    {
        output << std::format("cuda........ " BX_HARDWARE_COMPILED, cuda, compiled) << std::endl;

        if (cuda)
            output << std::format("cuda ecc.... " BX_HARDWARE_ENABLED, cuda_ecc(), cuda_ecc_enabled()) << std::endl;
    }

#if defined(HAVE_ARM)
    if (try_neon_sha2() && !have_neon_sha)
        output << BX_HARDWARE_SHA_UNCOMPILED << std::endl;
#else
    if (try_shani() && !have_shani)
        output << BX_HARDWARE_SHA_UNCOMPILED << std::endl;

    if (try_avx2() && !have_avx2)
        output << BX_HARDWARE_AVX2_UNCOMPILED << std::endl;
#endif

    if (cuda && !compiled)
        output << BX_HARDWARE_GPU_UNCOMPILED << std::endl;

    if (unsupported)
        output << BX_HARDWARE_UNSUPPORTED << std::endl;

    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
