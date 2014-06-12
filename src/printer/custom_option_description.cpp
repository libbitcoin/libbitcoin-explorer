/* (c) 2012 Radman Games. */

#include <iomanip>
#include <boost/program_options.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <sx/printer/custom_option_description.hpp>

using namespace boost;
using namespace algorithm;
using namespace program_options;

namespace printer {

const size_t LONG_NON_PREPENDED_IF_EXIST_ELSE_PREPENDED_SHORT = 0;
const size_t LONG_PREPENDED_IF_EXIST_ELSE_PREPENDED_SHORT = 1;
const size_t SHORT_PREPENDED_IF_EXIST_ELSE_LONG = 4;

const size_t SHORT_OPTION_STRING_LENGTH = 2; // -x
const size_t ADEQUATE_WIDTH_FOR_OPTION_NAME = 20;

const bool HAS_ARGUMENT = true;
const bool DOES_NOT_HAVE_ARGUMENT = false;

custom_option_description::custom_option_description(
    shared_ptr<option_description> option) :
    required_(false), hasShort_(false), hasArgument_(false),
    isPositional_(false)
{
    if ((option->canonical_display_name(SHORT_PREPENDED_IF_EXIST_ELSE_LONG)
        .size() == SHORT_OPTION_STRING_LENGTH))
    {
        hasShort_ = true;
        optionID_ = option->canonical_display_name(
            SHORT_PREPENDED_IF_EXIST_ELSE_LONG);
        optionDisplayName_ = option->canonical_display_name(
            SHORT_PREPENDED_IF_EXIST_ELSE_LONG);
    }
    else
    {
        hasShort_ = false;
        optionID_ = option->canonical_display_name(
            LONG_NON_PREPENDED_IF_EXIST_ELSE_PREPENDED_SHORT);
        optionDisplayName_ = option->canonical_display_name(
            LONG_PREPENDED_IF_EXIST_ELSE_PREPENDED_SHORT);
    }

    auto semantic = option->semantic();
    required_ = semantic->is_required();
    hasArgument_ = semantic->max_tokens() > 0 ? HAS_ARGUMENT : 
        DOES_NOT_HAVE_ARGUMENT;
    optionDescription_ = option->description();
    optionFormatName_ = option->format_name();

}

void custom_option_description::checkIfPositional(
    const positional_options_description& positional)
{
    for (unsigned int position = 0; position < positional.max_total_count();
        ++position)
    {
        if (optionID_ == positional.name_for_position(position))
        {
            erase_all(optionDisplayName_, "-");
            isPositional_ = true;
            break;
        }
    }
}

std::string custom_option_description::getOptionUsageString()
{
    std::stringstream usage;
    if (isPositional_)
        usage << "\t" << std::setw(ADEQUATE_WIDTH_FOR_OPTION_NAME) << std::left 
            << optionDisplayName_ << "\t" << optionDescription_;
    else
        usage << "\t" << std::setw(ADEQUATE_WIDTH_FOR_OPTION_NAME) << std::left 
            << optionFormatName_ << "\t" << optionDescription_;
    return usage.str();
}
} // rad
