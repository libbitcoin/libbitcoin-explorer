#ifndef SX_CONFIG_HPP
#define SX_CONFIG_HPP

#include <map>
#include <string>
#include <boost/filesystem.hpp>

// Address string cross-compile as char and std::string are non-unicode on
// Windows, which pre-dates unicode so char is ANSI and wchar_t is UCS-16.
// TODO: centralize this in cross-compile header(s).
#if defined(_WIN32) && defined(UNICODE)
typedef wchar_t tchar;
typedef std::wstring tstring;
typedef boost::filesystem::wpath tpath;
#else
#define L
typedef char tchar;
typedef std::string tstring;
typedef boost::filesystem::path tpath;
#endif

typedef std::map<std::string, std::string> config_map_type;
void load_config(config_map_type& config);

#endif