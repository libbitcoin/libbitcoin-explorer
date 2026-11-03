.template 0
###############################################################################
# Copyright (c) 2011-2023 libbitcoin developers (see COPYING).
#
# GSL generate libbitcoin-explorer source files.
# This file contains no localizable resources.
#
# This is a code generator built using the iMatix GSL code generation
# language. See https://github.com/imatix/gsl for details.
###############################################################################
.endtemplate
.template 1
.echo "Generating test/generated__help.cpp..."
.output "../test/generated__help.cpp"
.copyleft()

#include <bitcoin/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace bc::explorer;
using namespace bc::explorer::commands;

BC_AUTO_TEST_SUITE(generated)
BC_AUTO_TEST_SUITE(generated__help)
.for command by symbol

BC_AUTO_TEST_CASE(generated__help__$(symbol:c)__okay_output)
{
    std::stringstream input, output, error;
    const char* argv[]{ "$(symbol)", "--help" };
    BC_REQUIRE_EQUAL(dispatch_command(2, argv, input, output, error), console_result::okay);
    BC_REQUIRE(!output.str().empty());
    BC_REQUIRE(error.str().empty());
}
.endfor

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
.endtemplate
