.template 0
###############################################################################
# Copyright (c) 2011-2019 libbitcoin developers (see COPYING).
#
# GSL generate libbitcoin-explorer source files.
# This file contains no localizable resources.
#
# This is a code generator built using the iMatix GSL code generation
# language. See https://github.com/imatix/gsl for details.
###############################################################################
.endtemplate
.template 1
.echo "Generating test/generated__broadcast.cpp..."
.output "../test/generated__broadcast.cpp"
.copyleft()
#include <boost/test/unit_test.hpp>

#include <bitcoin/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

BOOST_AUTO_TEST_SUITE(generated)
BOOST_AUTO_TEST_SUITE(generated__broadcast)

BOOST_AUTO_TEST_CASE(generated__broadcast__always__does_not_throw)
{
    // TODO: mocks and dependency injection required to test proper execution.
    auto func = [](std::shared_ptr<bc::explorer::command> command) -> void {};
    bc::explorer::broadcast(func);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
.endtemplate