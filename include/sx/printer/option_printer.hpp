/* (c) 2012 Radman Games. */

#ifndef RAD_PRETTYOPTIONPRINTER_HPP
#define RAD_PRETTYOPTIONPRINTER_HPP

#include <boost/program_options.hpp>
#include <sx/printer/custom_option_description.hpp>

namespace rad {

class option_printer
{
public:
    void add(const custom_option_description& description);

    // Print the single line application usage description
    std::string usage();

    std::string positionalOptionDetails();
    std::string optionDetails();

public:
    static void printStandardAppDesc(const std::string& appName, 
        std::ostream& out,
        boost::program_options::options_description description,
        boost::program_options::positional_options_description* 
            positional=NULL);
    static void formatRequiredOptionError(
        boost::program_options::required_option& error);

private:
    std::vector<custom_option_description> options_;
    std::vector<custom_option_description> positionalOptions_;
};

} // rad

#endif 
