/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
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
#ifndef BX_PARSER_HPP
#define BX_PARSER_HPP

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {

/// Parse configurable values from environment variables, settings file, and
/// command line positional and non-positional options.
class BCX_API parser
  : public config::parser
{
public:
    /// Construct the parser for the given command.
    parser(command& instance);

    /// Parse all configuration into member settings.
    virtual bool parse(std::string& out_error, std::istream& input,
        int argc, const char* argv[]);

    virtual bool help() const;

    /// Load command line options (named).
    virtual options_metadata load_options();

    /// Load command line arguments (positional).
    virtual arguments_metadata load_arguments();

    /// Load configuration file settings.
    virtual options_metadata load_settings();

    /// Load environment variable settings.
    virtual options_metadata load_environment();

protected:
    virtual void load_command_variables(variables_map& variables,
        std::istream& input, int argc, const char* argv[]);

private:
    static std::string system_config_directory();
    static boost::filesystem::path default_config_path();

    bool help_;
    command& instance_;
};

} // namespace explorer
} // namespace libbitcoin

#endif
