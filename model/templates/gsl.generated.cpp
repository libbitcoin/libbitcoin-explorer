.template 0
###############################################################################
# Copyright (c) 2011-2018 libbitcoin developers (see COPYING).
#
# GSL generate libbitcoin-explorer source files.
# This file contains no localizable resources.
#
# This is a code generator built using the iMatix GSL code generation
# language. See https://github.com/imatix/gsl for details.
###############################################################################
.endtemplate
.template 1
.echo "Generating src/generated.cpp..."
.output "../src/generated.cpp"
.copyleft()
#include <bitcoin/explorer/generated.hpp>

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <bitcoin/explorer/command.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {

using namespace std;
using namespace po;
using namespace boost::filesystem;
using namespace commands;

void broadcast(const function<void(shared_ptr<command>)> func)
{
.for command by symbol
    func(make_shared<$(symbol:c)>());
.endfor
}

shared_ptr<command> find(const string& symbol)
{
.for command by symbol
    if (symbol == $(symbol:c)::symbol())
        return make_shared<$(symbol:c)>();
.endfor

    return nullptr;
}

std::string formerly(const string& former)
{
.for command by symbol
.   if (!is_empty(formerly))
    if (former == $(symbol:c)::formerly())
        return $(symbol:c)::symbol();
.   endif
.endfor

    return "";
}

} // namespace explorer
} // namespace libbitcoin
.endtemplate
