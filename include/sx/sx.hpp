/*
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
#ifndef SX_SX_HPP
#define SX_SX_HPP

// Convenience header that includes everything.
// Not to be used internally. For API users.
// This is intended primarily for test.
#include <sx/command.hpp>
#include <sx/dispatch.hpp>
#include <sx/display.hpp>
#include <sx/generated.hpp>
#ifdef HAVE_OBELISK
    #include <sx/obelisk.hpp>
#endif
#include <sx/serializer/byte.hpp>
#include <sx/serializer/bytes.hpp>
#include <sx/serializer/point.hpp>
#include <sx/serializer/secret.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/compat.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/environment.hpp>
#include <sx/utility/parameter.hpp>
#include <sx/utility/printer.hpp>

#endif