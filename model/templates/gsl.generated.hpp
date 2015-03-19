.template 0
###############################################################################
# Copyright (c) 2011-2015 libbitcoin developers (see COPYING).
#
# GSL generate libbitcoin-explorer source files.
# This file contains no localizable resources.
#
# This is a code generator built using the iMatix GSL code generation
# language. See https://github.com/imatix/gsl for details.
###############################################################################
.endtemplate
.template 1
.echo "Generating include/bitcoin/explorer/generated.hpp..."
.output "../include/bitcoin/explorer/generated.hpp"
.copyleft()
#ifndef BX_GENERATED_HPP
#define BX_GENERATED_HPP

#include <functional>
#include <memory>
#include <string>
#include <bitcoin/explorer/command.hpp>
.for command by symbol
#include <bitcoin/explorer/commands/$(symbol).hpp>
.endfor
#include <bitcoin/explorer/define.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {
.for resource
.   for string by name
.       if first()

/**
 * Various shared localizable strings.
 */
.       endif
#define $(name:upper,c) \\
    "$(value)"
.   endfor
.endfor

/**
 * Invoke a specified function on all commands.
 * @param[in]  func  The function to invoke on all commands.
 */
BCX_API void broadcast(
    const std::function<void(std::shared_ptr<command>)> func);

/**
 * Find the command identified by the specified symbolic command name.
 * @param[in]  symbol  The symbolic command name.
 * @return             An instance of the command or nullptr if not found.
 */
BCX_API std::shared_ptr<command> find(const std::string& symbol);

/**
 * Find the new name of the formerly-named command.
 * @param[in]  former  The former symbolic command name.
 * @return             The current name of the formerly-named command.
 */
BCX_API std::string formerly(const std::string& former);

} // namespace explorer
} // namespace libbitcoin

#endif
.endtemplate
