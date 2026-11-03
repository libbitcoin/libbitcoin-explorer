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
.echo "Generating test/generated__parse.cpp..."
.output "../test/generated__parse.cpp"
.copyleft()

#include <bitcoin/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;

BC_AUTO_TEST_SUITE(generated)
BC_AUTO_TEST_SUITE(generated__parse)
.for command by symbol
.   tokens = 1
.   for command.option
.       if (normalize_type(true(), !true(), type) = "bool")
.           tokens = tokens + 1
.       else
.           tokens = tokens + 2
.       endif
.   endfor
.   for command.argument
.       tokens = tokens + 1
.   endfor

BC_AUTO_TEST_CASE(generated__parse__$(symbol:c)__okay)
{
    $(symbol:c) command;
    std::string message;
    std::stringstream input;
    const char* argv[]
    {
        "$(symbol)",
.   for command.option
.       option_type = normalize_type(true(), !true(), type)
.       if (option_type = "bool")
        "--$(name:lower,c)",
.       else
        "--$(name:lower,c)", "$(sample_value(option_type))",
.       endif
.   endfor
.   for command.argument
.       argument_type = normalize_type(!true(), !true(), type)
        "$(sample_value(argument_type))",
.   endfor
    };

    parser metadata(command);
    BC_REQUIRE(metadata.parse(message, input, $(tokens), argv));
    BC_REQUIRE(message.empty());
    BC_REQUIRE(!metadata.help());
}
.endfor

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
.endtemplate
