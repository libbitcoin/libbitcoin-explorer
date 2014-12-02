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
.echo "Generating test/generated__find.cpp..."
.output "../test/generated__find.cpp"
.copyleft()
#include <boost/test/unit_test.hpp>

#include <bitcoin/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace bc::explorer;
using namespace bc::explorer::commands;

BOOST_AUTO_TEST_SUITE(generated)
BOOST_AUTO_TEST_SUITE(generated__find)
.for command by symbol

BOOST_AUTO_TEST_CASE(generated__find__$(symbol:c)__returns_object)
{
    BOOST_REQUIRE(find("$(symbol)") != nullptr);
}
.endfor

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
.endtemplate