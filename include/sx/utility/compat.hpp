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
#ifndef SX_COMPAT_H
#define SX_COMPAT_H

#include <boost/filesystem.hpp>

/* This doesn't go far enough, but it helps make things work for ASCII input. */
//#ifdef _WIN32
//    #define WIDE(s) L#s
//    typedef wchar_t tchar;
//    typedef std::wstring tstring;
//    typedef boost::filesystem::wpath tpath;
//#else
//    #define WIDE(s) s
//    typedef char tchar;
//    typedef std::string tstring;
//    typedef boost::filesystem::path tpath;
//#endif

/* This allows std::uniform_int_distribution platform differences. */
#ifdef _MSC_VER
    typedef uint16_t min_uniform_dist_size;
#else
    typedef uint8_t min_uniform_dist_size;
#endif

#endif