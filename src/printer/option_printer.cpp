/* (c) 2012 Radman Games. */

#include <boost/program_options.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <sx/printer/option_printer.hpp>

using namespace boost;
using namespace algorithm;
using namespace program_options;

namespace printer {

void option_printer::add(const custom_option_description& description)
{
    description.isPositional_ ? positionalOptions_.push_back(description) :
        options_.push_back(description);
}

std::string option_printer::usage()
{
    // simple flags that have a short version
    bool firstShortOption = true;

    std::stringstream description("[");

    for (auto option: options_)
    {
        if (option.hasShort_ && !option.hasArgument_ && !option.required_)
        {
            if (firstShortOption)
            {
                description << "-";
                firstShortOption = false;
            }

            description << option.optionDisplayName_[1];
        }
    }

    description << "] ";

    // simple flags that DO NOT have a short version
    for (auto option: options_)
        if (!option.hasShort_ && !option.hasArgument_ && !option.required_)
            description << "[" << option.optionDisplayName_ << "] ";

    // options with arguments
    for (auto option: options_)
        if (option.hasArgument_ && !option.required_)
            description << "[" << option.optionDisplayName_ << " ARG] ";

    // required options with arguments
    for (auto option: options_)
        if (option.hasArgument_ && option.required_)
            description << option.optionDisplayName_ << " ARG ";

    // positional option
    for (auto option: positionalOptions_)
        description << option.optionDisplayName_ << " ";
    return description.str();

}

std::string option_printer::positionalOptionDetails()
{
    std::stringstream output;
    for (auto option: positionalOptions_)
        output << option.getOptionUsageString() << std::endl;
    return output.str();
}

std::string option_printer::optionDetails()
{
    std::stringstream output;
    for (auto option: options_)
        output << option.getOptionUsageString() << std::endl;
    return output.str();
}

void option_printer::printStandardAppDesc(const std::string& application,
    std::ostream& out, options_description description, 
    positional_options_description* positional)
{
    option_printer printer;
    for (auto option: description.options())
    {
        custom_option_description current(option);
        current.checkIfPositional(*positional);
        printer.add(current);
    }

    out << "USAGE: " << application << " " << printer.usage()
        << std::endl
        << std::endl
        << "-- Option Descriptions --"
        << std::endl
        << std::endl
        << "Positional arguments:"
        << std::endl
        << printer.positionalOptionDetails()
        << std::endl
        << "Option Arguments: "
        << std::endl
        << printer.optionDetails()
        << std::endl;
}

void option_printer::formatRequiredOptionError(required_option& error)
{
    auto current = error.get_option_name();
    erase_regex(current, regex("^-+"));
    error.set_option_name(current);
}

} // rad