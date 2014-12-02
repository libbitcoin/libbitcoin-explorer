.template 0
###############################################################################
# Copyright (c) 2011-2014 libbitcoin developers (see COPYING).
#
# GSL generate libbitcoin-explorer source files.
# This file contains no localizable resources.
#
# This is a code generator built using the iMatix GSL code generation
# language. See https://github.com/imatix/gsl for details.
###############################################################################
.endtemplate
.template 1
.echo "Generating test/generated__formerly.cpp..."
.output "../test/generated__formerly.cpp"
.copyleft()
#include <boost/test/unit_test.hpp>

#include <bitcoin/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace bc::explorer;
using namespace bc::explorer::commands;

BOOST_AUTO_TEST_SUITE(generated)
BOOST_AUTO_TEST_SUITE(generated__formerly)
.for command by symbol
.   if (!is_empty(formerly))

BOOST_AUTO_TEST_CASE(generated__formerly__$(symbol:c)_was_$(formerly:c)__returns_object)
{
    BOOST_REQUIRE_EQUAL(formerly("$(formerly)"), $(symbol:c)::symbol());
}
.   endif
.endfor

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
.endtemplate