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
.echo "Generating test/generated__metadata.cpp..."
.output "../test/generated__metadata.cpp"
.copyleft()

#include <bitcoin/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;

BC_AUTO_TEST_SUITE(generated)
BC_AUTO_TEST_SUITE(generated__metadata)
.for command by symbol

BC_AUTO_TEST_CASE(generated__metadata__$(symbol:c)__returns_expected_values)
{
    $(symbol:c) command;
    BC_REQUIRE_EQUAL(command.category(), "$(category)");
.   if (is_raw_input(command))
    BC_REQUIRE(command.requires_raw_input());
.   else
    BC_REQUIRE(!command.requires_raw_input());
.   endif
.   if (is_raw_output(command.output))
    BC_REQUIRE(command.requires_raw_output());
.   else
    BC_REQUIRE(!command.requires_raw_output());
.   endif
}
.endfor

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
.endtemplate
