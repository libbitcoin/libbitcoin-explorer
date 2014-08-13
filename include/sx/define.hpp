/**
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
#ifndef DEFINE_HPP
#define DEFINE_HPP

#include <boost/dynamic_bitset.hpp>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/bitcoin.hpp>

#define PROPERTY(type, name) \
    public: virtual type get_##name() { return name##_; } \
    public: virtual void set_##name(type value) { name##_ = value; } \
    private: type name##_

#define PROPERTY_GET(type, name) \
    public: virtual type get_##name() { return name##_; } \
    private: type name##_

#define PROPERTY_SET(type, name) \
    public: virtual void set_##name(type value) { name##_ = value; } \
    private: type name##_

/**
 * Delimiter for use in word splitting serialized input and output points.
 */
#define SX_TX_POINT_DELIMITER ":"
    
/**
 * Default delimiter for use in word splitting and joining operations.
 */
#define SX_SENTENCE_DELIMITER " "

/**
 * Conventional command line argument sentinel for indicating that a file
 * should be read from STDIN or written to STDOUT.
 */

#define SX_STDIO_PATH_SENTINEL "-"

/**
 * Space-saving namespaces.
 */
namespace ph = std::placeholders;
namespace po = boost::program_options;
namespace pt = boost::property_tree;

/**
 * Space-saving, clarifying and/or differentiating external type equivalents.
 */
typedef bc::transaction_type tx_type;
typedef bc::transaction_input_type tx_input_type;
typedef bc::transaction_output_type tx_output_type;
typedef bc::blockchain::history_row balance_row;
typedef bc::blockchain::history_row history_row;
typedef boost::format format;
typedef boost::dynamic_bitset<uint8_t> bitset;
typedef po::option_description option_metadata;
typedef po::options_description options_metadata;
typedef po::positional_options_description arguments_metadata;

/**
 * The max length of the prefix in bits.
 */
constexpr size_t max_prefix = sizeof(bc::stealth_bitfield) * bc::byte_size;
    
/**
 * The noop void function.
 */
static const std::function<void()> noop = []{};

/**
* Result codes for int main().
*/
enum console_result : int
{
    failure = -1,
    okay = 0,
    invalid = 1
};

/**
 * Suppported output encoding engines.
 */
enum class encoding_engine
{
    info,
    json,
    xml,
    native
};

/**
 * Definition of the parts of a wrapped payload.
 */
struct wrapped_data
{
    uint8_t version;
    uint32_t checksum;
    bc::data_chunk payload;
};

#endif