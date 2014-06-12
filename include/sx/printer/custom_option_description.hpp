/* (c) 2012 Radman Games. */

#ifndef RAD_CUSTOMOPTIONDESCRIPTION_HPP
#define RAD_CUSTOMOPTIONDESCRIPTION_HPP

#include <string>
#include <boost/program_options.hpp>

namespace printer {

class custom_option_description
{
public:
    custom_option_description(
        boost::shared_ptr<boost::program_options::option_description> option);

    void checkIfPositional(
        const boost::program_options::positional_options_description& 
        positional);

    std::string getOptionUsageString();

public:
    std::string optionID_;
    std::string optionDisplayName_;
    std::string optionDescription_;
    std::string optionFormatName_;

    bool required_;
    bool hasShort_;
    bool hasArgument_;
    bool isPositional_;
};

} // rad

#endif
