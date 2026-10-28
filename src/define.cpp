/**
 * Copyright (c) 2011-2026 libbitcoin developers
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
#include <bitcoin/explorer/define.hpp>

// define.hpp is the common include for /explorer.
// All non-explorer headers include define.hpp.
// Explorer inclusions are chained as follows.

// define         : <bitcoin/system>

// Other directory common includes are not internally chained.
// Each header includes only its required common headers.

// client         : define
// /config        : define
// utility        : define
// command        : /config utility
// dispatch       : define
// display        : command
// /commands      : command                        [generated.hpp]
// generated      : /commands
// json           : define
// parser         : command
// version        : <generated>

// When a symbol is unexplainably undefined, its defining include is probably
// creating the circularity.
