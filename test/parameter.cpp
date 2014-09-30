/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
// #include "precompile.hpp"
#include <iostream>
#include <utility>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <bitcoin/explorer.hpp>

namespace libbitcoin {
namespace parameter {

using namespace bc::explorer;

enum opt
{
    short_long = 0,
    shorty,
    longy,
    simple,
    defaulty,
    required,
    vector,
    multitoken
};

static void load_test_options(options_metadata& options)
{
    using namespace boost::filesystem;
    using namespace boost::program_options;
    options.add_options()
        ("short_long,s", "Long and short name.")
        (",m", "Short name only.")
        ("longy", "Long name only.")
        ("simple", value<std::string>(), "Simple string.")
        ("defaulty", value<bool>()->default_value(true), "Defaulted bool.")
        ("required", value<path>()->required(), "Required path.")
        /* The enumerability of the data types does not control multiple,
           instance behavior but it is necessary to capture multiples. */
        ("VECTOR", value<std::vector<std::string>>(), "String vector.")
        ("multitoken", value<int>()->multitoken(), "Multi-token int.");
}

static void load_test_arguments(argument_list& arguments)
{
    arguments.push_back(argument_pair("longy", 1));
    arguments.push_back(argument_pair("simple", 2));
    arguments.push_back(argument_pair("defaulty", 3));
    arguments.push_back(argument_pair("required", 4));
    arguments.push_back(argument_pair("VECTOR", 5));
    arguments.push_back(argument_pair("multitoken", -1));
}

#define BX_TEST_PARAMETER_SETUP(index) \
    options_metadata options; \
    load_test_options(options); \
    argument_list names; \
    load_test_arguments(names); \
    auto option = *(options.options()[index]); \
    bc::explorer::parameter parameter

#define BX_TEST_PARAMETER_OPTIONS_SETUP(index) \
    options_metadata options; \
    load_test_options(options); \
    auto option = *(options.options()[index]); \
    bc::explorer::parameter parameter

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(parameter__position)

BOOST_AUTO_TEST_CASE(parameter__position__short_and_long__returns_not)
{
    BX_TEST_PARAMETER_SETUP(opt::short_long);
    auto result = parameter.position(option, names);
    BOOST_REQUIRE(result == -1);
}

BOOST_AUTO_TEST_CASE(parameter__position__short_only__returns_not)
{
    BX_TEST_PARAMETER_SETUP(opt::shorty);
    auto result = parameter.position(option, names);
    BOOST_REQUIRE(result == -1);
}

BOOST_AUTO_TEST_CASE(parameter__position__long_only__returns_expected_position)
{
    BX_TEST_PARAMETER_SETUP(opt::longy);
    auto result = parameter.position(option, names);
    BOOST_REQUIRE(result == 0);
}

BOOST_AUTO_TEST_CASE(parameter__position__simple__returns_expected_position)
{
    BX_TEST_PARAMETER_SETUP(opt::simple);
    auto result = parameter.position(option, names);
    BOOST_REQUIRE(result == 1);
}

BOOST_AUTO_TEST_CASE(parameter__position__defaulty__returns_expected_position)
{
    BX_TEST_PARAMETER_SETUP(opt::defaulty);
    auto result = parameter.position(option, names);
    BOOST_REQUIRE(result == 2);
}

BOOST_AUTO_TEST_CASE(parameter__position__required__returns_expected_position)
{
    BX_TEST_PARAMETER_SETUP(opt::required);
    auto result = parameter.position(option, names);
    BOOST_REQUIRE(result == 3);
}

BOOST_AUTO_TEST_CASE(parameter__position__vector__returns_expected_position)
{
    BX_TEST_PARAMETER_SETUP(opt::vector);
    auto result = parameter.position(option, names);
    BOOST_REQUIRE(result == 4);
}

BOOST_AUTO_TEST_CASE(parameter__position__multitoken__returns_expected_position)
{
    BX_TEST_PARAMETER_SETUP(opt::multitoken);
    auto result = parameter.position(option, names);
    BOOST_REQUIRE(result == 5);
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(parameter__initialize)

BOOST_AUTO_TEST_CASE(parameter__initialize__short_long__sets_limit_0)
{
    BX_TEST_PARAMETER_SETUP(opt::short_long);
    parameter.initialize(option, names);
    BOOST_REQUIRE(parameter.get_position() == -1);
    BOOST_REQUIRE(parameter.get_args_limit() == 0);
    BOOST_REQUIRE(parameter.get_required() == false);
    BOOST_REQUIRE(parameter.get_short_name() == 's');
    BOOST_REQUIRE(parameter.get_canonical_name() == "--short_long");
    BOOST_REQUIRE(parameter.get_format_name() == "-s [ --short_long ]");
    BOOST_REQUIRE(parameter.get_format_parameter() == "");
    BOOST_REQUIRE(parameter.get_description() == "Long and short name.");
}

BOOST_AUTO_TEST_CASE(parameter__initialize__short_only__sets_limit_0)
{
    BX_TEST_PARAMETER_SETUP(opt::shorty);
    parameter.initialize(option, names);
    BOOST_REQUIRE(parameter.get_position() == -1);
    BOOST_REQUIRE(parameter.get_args_limit() == 0);
    BOOST_REQUIRE(parameter.get_required() == false);
    BOOST_REQUIRE(parameter.get_short_name() == 'm');
    BOOST_REQUIRE(parameter.get_canonical_name() == "-m");
    BOOST_REQUIRE(parameter.get_format_name() == "-m");
    BOOST_REQUIRE(parameter.get_format_parameter() == "");
    BOOST_REQUIRE(parameter.get_description() == "Short name only.");
}

BOOST_AUTO_TEST_CASE(parameter__initialize__long_only__sets_limit_0)
{
    BX_TEST_PARAMETER_SETUP(opt::longy);
    parameter.initialize(option, names);
    BOOST_REQUIRE(parameter.get_position() == 0);
    BOOST_REQUIRE(parameter.get_args_limit() == 0);
    BOOST_REQUIRE(parameter.get_required() == false);
    BOOST_REQUIRE(parameter.get_short_name() == '\0');
    BOOST_REQUIRE(parameter.get_canonical_name() == "--longy");
    BOOST_REQUIRE(parameter.get_format_name() == "--longy");
    BOOST_REQUIRE(parameter.get_format_parameter() == "");
    BOOST_REQUIRE(parameter.get_description() == "Long name only.");
}

BOOST_AUTO_TEST_CASE(parameter__initialize__simple__sets_limit_1)
{
    BX_TEST_PARAMETER_SETUP(opt::simple);
    parameter.initialize(option, names);
    BOOST_REQUIRE(parameter.get_position() == 1);
    BOOST_REQUIRE(parameter.get_args_limit() == 1);
    BOOST_REQUIRE(parameter.get_required() == false);
    BOOST_REQUIRE(parameter.get_short_name() == '\0');
    BOOST_REQUIRE(parameter.get_canonical_name() == "--simple");
    BOOST_REQUIRE(parameter.get_format_name() == "--simple");
    BOOST_REQUIRE(parameter.get_format_parameter() == "arg");
    BOOST_REQUIRE(parameter.get_description() == "Simple string.");
}

BOOST_AUTO_TEST_CASE(parameter__initialize__defaulted__sets_limit_1)
{
    BX_TEST_PARAMETER_SETUP(opt::defaulty);
    parameter.initialize(option, names);
    BOOST_REQUIRE(parameter.get_position() == 2);
    BOOST_REQUIRE(parameter.get_args_limit() == 1);
    BOOST_REQUIRE(parameter.get_required() == false);
    BOOST_REQUIRE(parameter.get_short_name() == '\0');
    BOOST_REQUIRE(parameter.get_canonical_name() == "--defaulty");
    BOOST_REQUIRE(parameter.get_format_name() == "--defaulty");
    /* The (=1) appears to be the default value (as int), i.e. (=true) */
    BOOST_REQUIRE(parameter.get_format_parameter() == "arg (=1)");
    BOOST_REQUIRE(parameter.get_description() == "Defaulted bool.");
}

BOOST_AUTO_TEST_CASE(parameter__initialize__required__sets_limit_1)
{
    BX_TEST_PARAMETER_SETUP(opt::required);
    parameter.initialize(option, names);
    BOOST_REQUIRE(parameter.get_position() == 3);
    BOOST_REQUIRE(parameter.get_args_limit() == 1);
    BOOST_REQUIRE(parameter.get_required() == true);
    BOOST_REQUIRE(parameter.get_short_name() == '\0');
    BOOST_REQUIRE(parameter.get_canonical_name() == "--required");
    BOOST_REQUIRE(parameter.get_format_name() == "--required");
    BOOST_REQUIRE(parameter.get_format_parameter() == "arg");
    BOOST_REQUIRE(parameter.get_description() == "Required path.");
}

BOOST_AUTO_TEST_CASE(parameter__initialize__vector__sets_limit_1)
{
    BX_TEST_PARAMETER_SETUP(opt::vector);
    parameter.initialize(option, names);
    BOOST_REQUIRE(parameter.get_position() == 4);
    BOOST_REQUIRE(parameter.get_args_limit() == 1);
    BOOST_REQUIRE(parameter.get_required() == false);
    BOOST_REQUIRE(parameter.get_short_name() == '\0');
    BOOST_REQUIRE(parameter.get_canonical_name() == "--VECTOR");
    BOOST_REQUIRE(parameter.get_format_name() == "--VECTOR");
    BOOST_REQUIRE(parameter.get_format_parameter() == "arg");
    BOOST_REQUIRE(parameter.get_description() == "String vector.");
}

BOOST_AUTO_TEST_CASE(parameter__initialize__multitoken__sets_unlimited)
{
    BX_TEST_PARAMETER_SETUP(opt::multitoken);
    parameter.initialize(option, names);
    BOOST_REQUIRE(parameter.get_position() == 5);
    BOOST_REQUIRE(parameter.get_args_limit() == 0x7d00);
    BOOST_REQUIRE(parameter.get_required() == false);
    BOOST_REQUIRE(parameter.get_short_name() == '\0');
    BOOST_REQUIRE(parameter.get_canonical_name() == "--multitoken");
    BOOST_REQUIRE(parameter.get_format_name() == "--multitoken");
    BOOST_REQUIRE(parameter.get_format_parameter() == "arg");
    BOOST_REQUIRE(parameter.get_description() == "Multi-token int.");
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(parameter__canonical)

BOOST_AUTO_TEST_CASE(parameter__canonical__short_and_long__matches_dash_long)
{
    BX_TEST_PARAMETER_OPTIONS_SETUP(opt::short_long);
    auto result = parameter.canonical(option);
    BOOST_REQUIRE(result == "--short_long");
}

BOOST_AUTO_TEST_CASE(parameter__canonical__short_only__matches_dash_short)
{
    BX_TEST_PARAMETER_OPTIONS_SETUP(opt::shorty);
    auto result = parameter.canonical(option);
    BOOST_REQUIRE(result == "-m");
}

BOOST_AUTO_TEST_CASE(parameter__canonical__long_only__matches_dash_long)
{
    BX_TEST_PARAMETER_OPTIONS_SETUP(opt::longy);
    auto result = parameter.canonical(option);
    BOOST_REQUIRE(result == "--longy");
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(parameter__clean_canonical)

BOOST_AUTO_TEST_CASE(parameter__clean_canonical__short_and_long__matches_long)
{
    BX_TEST_PARAMETER_OPTIONS_SETUP(opt::short_long);
    auto result = parameter.clean_canonical(option);
    BOOST_REQUIRE(result == "short_long");
}

BOOST_AUTO_TEST_CASE(parameter__clean_canonical__short_only__matches_short)
{
    BX_TEST_PARAMETER_OPTIONS_SETUP(opt::shorty);
    auto result = parameter.clean_canonical(option);
    BOOST_REQUIRE(result == "m");
}

BOOST_AUTO_TEST_CASE(parameter__clean_canonical__long_only__matches_long)
{
    BX_TEST_PARAMETER_OPTIONS_SETUP(opt::longy);
    auto result = parameter.clean_canonical(option);
    BOOST_REQUIRE(result == "longy");
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(parameter__has_short_name)

BOOST_AUTO_TEST_CASE(parameter__has_short_name__short_and_long__returns_true)
{
    BX_TEST_PARAMETER_OPTIONS_SETUP(opt::short_long);
    auto result = parameter.has_short_name(option);
    BOOST_REQUIRE(result);
}

BOOST_AUTO_TEST_CASE(parameter__has_short_name__short_only__returns_true)
{
    BX_TEST_PARAMETER_OPTIONS_SETUP(opt::shorty);
    auto result = parameter.has_short_name(option);
    BOOST_REQUIRE(result);
}

BOOST_AUTO_TEST_CASE(parameter__has_short_name__long_only__returns_false)
{
    BX_TEST_PARAMETER_OPTIONS_SETUP(opt::longy);
    auto result = parameter.has_short_name(option);
    BOOST_REQUIRE(!result);
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //
BOOST_AUTO_TEST_SUITE(parameter__short_name)

BOOST_AUTO_TEST_CASE(parameter__short_name__short_and_long__returns_short)
{
    BX_TEST_PARAMETER_OPTIONS_SETUP(opt::short_long);
    auto result = parameter.short_name(option);
    BOOST_REQUIRE(result = 's');
}

BOOST_AUTO_TEST_CASE(parameter__short_name__short_only__returns_short)
{
    BX_TEST_PARAMETER_OPTIONS_SETUP(opt::shorty);
    auto result = parameter.short_name(option);
    BOOST_REQUIRE(result = 'm');
}

BOOST_AUTO_TEST_CASE(parameter__short_name__long_only__returns_null)
{
    BX_TEST_PARAMETER_OPTIONS_SETUP(opt::longy);
    auto result = parameter.short_name(option);
    BOOST_REQUIRE(result == 0x00);
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace parameter
} // namespace libbitcoin