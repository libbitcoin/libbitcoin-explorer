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
.echo "Generating test/generated__property.cpp..."
.output "../test/generated__property.cpp"
.copyleft()

#include <bitcoin/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;

template <typename Value>
static std::string serial(const Value& value)
{
    std::ostringstream text;
    text << value;
    return text.str();
}

template <typename Value>
static std::string serial(const std::vector<Value>& values)
{
    std::ostringstream text;
    for (const auto& value: values)
        text << value;

    return text.str();
}

BC_AUTO_TEST_SUITE(generated)
BC_AUTO_TEST_SUITE(generated__property)
.for command by symbol
.   define has_properties = (count(command.argument) + count(command.option)) > 0
.   if (has_properties)

BC_AUTO_TEST_CASE(generated__property__$(symbol:c)__round_trips)
{
    $(symbol:c) command;
.       for argument
.           is_vector = !is_default(limit, 1)
.           cpp_type = normalize_type(!true(), !true(), type)
.           vtype = vectored_type(cpp_type, is_vector)
.           variable = "$(pluralize(name, is_vector):lower,c)_argument"
.           sample = sample_value(cpp_type)
.           if (is_vector)

    const $(vtype) $(variable){ { "$(sample)" } };
.           elsif (is_unquoted_type(cpp_type))

    const $(vtype) $(variable){ $(sample) };
.           else

    const $(vtype) $(variable){ "$(sample)" };
.           endif
    command.set_$(variable)($(variable));
    BC_REQUIRE_EQUAL(serial(command.get_$(variable)()), serial($(variable)));
.       endfor
.       for option
.           is_vector = is_xml_true(multiple)
.           cpp_type = normalize_type(true(), !true(), type)
.           vtype = vectored_type(cpp_type, is_vector)
.           variable = "$(pluralize(name, is_vector):lower,c)_option"
.           sample = sample_value(cpp_type)
.           if (is_vector)

    const $(vtype) $(variable){ { "$(sample)" } };
.           elsif (is_unquoted_type(cpp_type))

    const $(vtype) $(variable){ $(sample) };
.           else

    const $(vtype) $(variable){ "$(sample)" };
.           endif
    command.set_$(variable)($(variable));
    BC_REQUIRE_EQUAL(serial(command.get_$(variable)()), serial($(variable)));
.       endfor
}
.   endif
.endfor

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
.endtemplate
