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
#ifndef BX_DEFINE_HPP
#define BX_DEFINE_HPP

#include <cstdint>
#include <cstddef>
#include <boost/dynamic_bitset.hpp>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/client.hpp>

// We use the generic helper definitions in libbitcoin to define BCX_API
// and BCX_INTERNAL. BCX_API is used for the public API symbols. It either DLL
// imports or DLL exports (or does nothing for static build) BCX_INTERNAL is
// used for non-api symbols.

#if defined BCX_STATIC
    #define BCX_API
    #define BCX_INTERNAL
#elif defined BCX_DLL
    #define BCX_API      BC_HELPER_DLL_EXPORT
    #define BCX_INTERNAL BC_HELPER_DLL_LOCAL
#else
    #define BCX_API      BC_HELPER_DLL_IMPORT
    #define BCX_INTERNAL BC_HELPER_DLL_LOCAL
#endif

/**
 * The name of this program.
 */
#define BX_PROGRAM_NAME "bx"

/**
 * Delimiter for use in word splitting serialized input and output points.
 */
#define BX_TX_POINT_DELIMITER ":"

/**
 * Default delimiter for use in word splitting and joining operations.
 */
#define BX_SENTENCE_DELIMITER " "

/**
 * Environment variable prefix for integrated environment variables.
 */
#define BX_ENVIRONMENT_VARIABLE_PREFIX "BX_"

/**
 * Conventional command line argument sentinel for indicating that a file
 * should be read from STDIN or written to STDOUT.
 */
#define BX_STDIO_PATH_SENTINEL "-"

namespace libbitcoin {
namespace explorer {

/**
 * Space-saving namespaces.
 */
namespace ph = std::placeholders;
namespace po = boost::program_options;
namespace pt = boost::property_tree;

/**
 * Space-saving, clarifying and/or differentiating external type equivalents.
 */
typedef boost::format format;
typedef bc::system::chain::transaction tx_type;
typedef bc::system::chain::input tx_input_type;
typedef bc::system::chain::output tx_output_type;

/**
 * The minimum safe length of a seed in bits (multiple of 8).
 */
BC_CONSTEXPR size_t minimum_seed_bits = 128;

/**
 * The minimum safe length of a seed in bytes (16).
 */
BC_CONSTEXPR size_t minimum_seed_size = minimum_seed_bits / bc::byte_bits;

/**
 * Suppported output encoding engines.
 */
enum class encoding_engine
{
    info,
    json,
    xml,
    data
};

} // namespace explorer
} // namespace libbitcoin

#endif
