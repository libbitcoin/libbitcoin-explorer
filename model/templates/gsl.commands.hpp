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
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/generated.hpp>
.primitives()
#include <bitcoin/explorer/utility/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

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
class $(symbol:c) 
    : public command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    BCX_API static const char* symbol()
    {
        return "$(symbol)";
    }

.if (!is_empty(formerly))
    /**
     * The symbolic (not localizable) former command name, lower case.
     */
    BCX_API static const char* formerly()
    {
        return "$(formerly)";
    }
.endif

    /**
     * The member symbolic (not localizable) command name, lower case.
     */
    BCX_API virtual const char* name()
    {
        return $(symbol:c)::symbol();
    }

    /**
     * The localizable command category name, upper case.
     */
    BCX_API virtual const char* category()
    {
        return "$(category)";
    }

    /**
     * The localizable command description.
     */
    BCX_API virtual const char* description()
    {
        return "$(description)";
    }
.if (is_xml_true(obsolete))

    /**
     * Declare whether the command has been obsoleted.
     * @return  True if the command is obsolete
     */
    BCX_API virtual bool obsolete()
    {
        return true;
    }
.endif

.
.# HACK: There must be a better way to count a collection.
.argument_count = 0
.for argument
.   argument_count += 1
.endfor
.option_count = 0
.for option
.   option_count += 1
.endfor
.
    /**
     * Load program argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded program argument definitions.
     */
    BCX_API virtual arguments_metadata& load_arguments()
    {
        return get_argument_metadata()$(if_else_empty(argument_count = 0, ";"))
.for argument
            .add("$(name)", $(limit ? "1"))$(last() ?? ";")
.endfor
    }

	/**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input  The input stream for loading the parameters.
     * @param[in]         The loaded variables.
     */
    BCX_API virtual void load_fallbacks(std::istream& input, 
        po::variables_map& variables)
    {
.for argument
.   is_vector = !is_default(limit, 1)
.   argument_type = normalize_type(!true(), !true(), type)
.   pluralized_name = pluralize(name, is_vector)
.   getter = "get_" + "$(pluralized_name:lower,c)" + "_argument()"
.#   bool_vector = if_else(is_vector, xml_true, xml_false)
.   if (is_xml_true(argument.file))
        load_path($(getter), "$(name)", variables);
.   endif
.   if (is_xml_true(argument.stdin))
        load_input($(getter), "$(name)", variables, input);
.   endif
.endfor
.for option
.   is_vector = is_xml_true(multiple)
.   option_type = normalize_type(true(), !true(), type)
.   pluralized_name = pluralize(name, is_vector)
.   getter = "get_" + "$(pluralized_name:lower,c)_option()"
.#   bool_vector = if_else(is_vector, xml_true, xml_false)
.   if (is_xml_true(option.file))
        //load_path($(getter), "$(name:lower,c)", variables);
.   endif
.   if (is_xml_true(option.stdin))
        //load_input($(getter), "$(name:lower,c)", variables, input);
.   endif
.endfor
    }

    /**
     * Load program option definitions.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded program option definitions.
     */
    BCX_API virtual options_metadata& load_options()
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
        )$(((argument_count = 0) & (option_count = 0 )) ?? ";")
.for option
.   short_name = shortcut ? first_char(name)
.   identifiers = name
.   identifiers += if_else(short_name = "", "", "," + short_name)
.   variable = "option_.$(name:lower,c)"
.   expression = value_semantic(is_xml_true(option.file), true(), type,\
        is_xml_true(required), is_xml_true(multiple), variable, default)
        (
            "$(identifiers)",
            $(expression),
            "$(description)"
        )$((last() & (argument_count = 0)) ?? ";")
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
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    BCX_API virtual console_result invoke(std::ostream& output,
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
    BCX_API virtual $(vtype)& get_$(pluralized_name:lower,c)_argument()
    {
        return argument_.$(pluralized_name:lower,c);
    }

    /**
     * Set the value of the $(name) $(pluralized_argument).
     */
    BCX_API virtual void set_$(pluralized_name:lower,c)_argument(
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
    BCX_API virtual $(vtype)& get_$(pluralized_name:lower,c)_option()
    {
        return option_.$(pluralized_name:lower,c);
    }

    /**
     * Set the value of the $(name) $(pluralized_option).
     */
    BCX_API virtual void set_$(pluralized_name:lower,c)_option(
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
