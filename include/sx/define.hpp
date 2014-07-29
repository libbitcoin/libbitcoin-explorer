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

#include <boost/format.hpp>
#include <boost/program_options.hpp>

#define REGION

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

namespace ph = std::placeholders;
namespace po = boost::program_options;

typedef po::option_description option_metadata;
typedef po::options_description options_metadata;
typedef po::positional_options_description arguments_metadata;

#endif