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
.for command by symbol
.echo "Generating include/bitcoin/explorer/commands/$(symbol).hpp..."
.output "../include/bitcoin/explorer/commands/$(symbol).hpp"
.copyleft()
#ifndef BX_$(symbol:upper,c)_HPP
#define BX_$(symbol:upper,c)_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/generated.hpp>
.primitives()
#include <bitcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

.define has_options = count(command.option) > 0
.define has_arguments = count(command.argument) > 0
.
namespace libbitcoin {
namespace explorer {
namespace commands {
.for define
.   if first()

/**
 * Various localizable strings.
 */
.   endif
#define $(name:upper,c) \\
    "$(value)"
.endfor

/**
 * Class to implement the $(symbol) command.
 */
class BCX_API $(symbol:c)
  : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "$(symbol)";
    }

.if (!is_empty(formerly))
    /**
     * The symbolic (not localizable) former command name, lower case.
     */
    static const char* formerly()
    {
        return "$(formerly)";
    }
.endif

    /**
     * Destructor.
     */
    virtual ~$(symbol:c)()
    {
    }

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    virtual const char* name()
    {
        return $(symbol:c)::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    virtual const char* category()
    {
        return "$(category)";
    }

    /**
     * The localizable command description.
     */
    virtual const char* description()
    {
        return "$(description)";
    }
.if (is_xml_true(obsolete))

    /**
     * Declare whether the command has been obsoleted.
     * @return  True if the command is obsolete
     */
    virtual bool obsolete()
    {
        return true;
    }
.endif
.if (is_raw_input(command))

    /**
     * Determines if STDIN is required to be raw.
     * @return  True if the type of the STDIN argument is primitive::raw.
     */
    virtual bool requires_raw_input()
    {
        return true;
    }
.endif
.if (is_raw_output(command.output))

    /**
     * Determines if STDOUT is required to be raw.
     * @return  True if the type of the STDOUT argument is primitive::raw.
     */
    virtual bool requires_raw_output()
    {
        return true;
    }
.endif

    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    virtual system::arguments_metadata& load_arguments()
    {
        return get_argument_metadata()$(if_else_empty(!has_arguments, ";"))
.for argument
            .add("$(name)", $(limit ? "1"))$(last() ?? ";")
.endfor
    }

    /**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    virtual void load_fallbacks(std::istream& input,
        po::variables_map& variables)
    {
.for argument
.   is_vector = !is_default(limit, 1)
.   argument_type = normalize_type(!true(), !true(), type)
.   pluralized_name = pluralize(name, is_vector)
.   getter = "get_" + "$(pluralized_name:lower,c)" + "_argument()"
.#   bool_vector = if_else(is_vector, xml_true, xml_false)
.   if (is_xml_true(argument.file))
        const auto raw = requires_raw_input();
        load_path($(getter), "$(name)", variables, raw);
.   endif
.   if (is_xml_true(argument.stdin))
        const auto raw = requires_raw_input();
        load_input($(getter), "$(name)", variables, input, raw);
.   endif
.endfor
.for option
.   is_vector = is_xml_true(multiple)
.   option_type = normalize_type(true(), !true(), type)
.   pluralized_name = pluralize(name, is_vector)
.   getter = "get_" + "$(pluralized_name:lower,c)_option()"
.#   bool_vector = if_else(is_vector, xml_true, xml_false)
.   if (is_xml_true(option.file))
        //const auto raw = requires_raw_input();
        //load_path($(getter), "$(name:lower,c)", variables, raw);
.   endif
.   if (is_xml_true(option.stdin))
        //const auto raw = requires_raw_input();
        //load_input($(getter), "$(name:lower,c)", variables, input, raw);
.   endif
.endfor
    }

    /**
     * Load program option definitions.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded program option definitions.
     */
    virtual system::options_metadata& load_options()
    {
        using namespace po;
        options_description& options = get_option_metadata();
        options.add_options()
        (
            BX_HELP_VARIABLE ",h",
            value<bool>()->zero_tokens(),
            "$(help_description)"
        )
        (
            BX_CONFIG_VARIABLE ",c",
            value<boost::filesystem::path>(),
            "$(config_description)"
        )$((!has_arguments & !has_options) ?? ";")
.for option
.   define default_value = get_option_default(option, generate)?
.   short_name = shortcut ? first_char(name)
.   identifiers = name
.   identifiers += if_else(short_name = "", "", "," + short_name)
.   variable = "option_.$(name:lower,c)"
.   expression = value_semantic(is_xml_true(option.file), true(), type,\
        is_xml_true(required), is_xml_true(multiple), variable, default_value)
        (
            "$(identifiers)",
            $(expression),
            "$(description)"
        )$((last() & !has_arguments) ?? ";")
.endfor
.for argument
.   variable = "argument_.$(name:lower,c)"
.   expression = value_semantic(is_xml_true(argument.file), !true(), type,\
        is_xml_true(required), !is_default(limit, 1), variable)
        (
            "$(name)",
            $(expression),
            "$(description)"
        )$(last() ?? ";")
.endfor

        return options;
    }

    /**
     * Set variable defaults from configuration variable values.
     * @param[in]  variables  The loaded variables.
     */
    virtual void set_defaults_from_config(po::variables_map& variables)
    {
.for option where defined(option.configuration)
.   is_vector = is_xml_true(multiple)
.   option_type = normalize_type(true(), !true(), type)
.   vtype = vectored_type(option_type, is_vector)
.   pluralized_name = pluralize(name, is_vector)
.   option_variable = "$(pluralized_name:lower,c)"
.   option_name = "option_$(option_variable)"
        const auto& $(option_name) = variables["$(name)"];
        const auto& $(option_name)_config = variables["$(configuration)"];
        if ($(option_name).defaulted() && !$(option_name)_config.defaulted())
        {
            option_.$(option_variable) = $(option_name)_config.as<$(vtype)>();
        }
.   if (!last())

.   endif
.endfor
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    virtual system::console_result invoke(std::ostream& output,
        std::ostream& cerr);

    /* Properties */

.for argument
.   is_vector = !is_default(limit, 1)
.   argument_type = normalize_type(!true(), !true(), type)
.   vtype = vectored_type(argument_type, is_vector)
.   pluralized_name = pluralize(name, is_vector)
.   pluralized_argument = pluralize("argument", is_vector)
    /**
     * Get the value of the $(name) $(pluralized_argument).
     */
    virtual $(vtype)& get_$(pluralized_name:lower,c)_argument()
    {
        return argument_.$(pluralized_name:lower,c);
    }

    /**
     * Set the value of the $(name) $(pluralized_argument).
     */
    virtual void set_$(pluralized_name:lower,c)_argument(
        const $(vtype)& value)
    {
        argument_.$(pluralized_name:lower,c) = value;
    }

.endfor
.for option
.   is_vector = is_xml_true(multiple)
.   option_type = normalize_type(true(), !true(), type)
.   vtype = vectored_type(option_type, is_vector)
.   pluralized_name = pluralize(name, is_vector)
.   pluralized_option = pluralize("option", is_vector)
    /**
     * Get the value of the $(name) $(pluralized_option).
     */
    virtual $(vtype)& get_$(pluralized_name:lower,c)_option()
    {
        return option_.$(pluralized_name:lower,c);
    }

    /**
     * Set the value of the $(name) $(pluralized_option).
     */
    virtual void set_$(pluralized_name:lower,c)_option(
        const $(vtype)& value)
    {
        option_.$(pluralized_name:lower,c) = value;
    }

.endfor
private:

    /**
     * Command line argument bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct argument
    {
        argument()
.for argument
.   is_vector = !is_default(limit, 1)
.   pluralized_name = pluralize(name, is_vector)
          $(if_else(first(), ":", " ")) $(pluralized_name:lower,c)()$(!last() ?? ",")
.   endfor
        {
        }

.for argument
.   is_vector = !is_default(limit, 1)
.   argument_type = normalize_type(!true(), !true(), type)
.   vector_type = vectored_type(argument_type, is_vector)
.   pluralized_name = pluralize(name, is_vector)
        $(vector_type) $(pluralized_name:lower,c);
.endfor
    } argument_;

    /**
     * Command line option bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct option
    {
        option()
.for option
.   is_vector = is_xml_true(multiple)
.   pluralized_name = pluralize(name, is_vector)
          $(if_else(first(), ":", " ")) $(pluralized_name:lower,c)()$(!last() ?? ",")
.endfor
        {
        }

.for option
.   is_vector = is_xml_true(multiple)
.   option_type = normalize_type(true(), !true(), type)
.   vector_type = vectored_type(option_type, is_vector)
.   pluralized_name = pluralize(name, is_vector)
        $(vector_type) $(pluralized_name:lower,c);
.endfor
    } option_;
};

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

#endif
.endfor
.endtemplate
