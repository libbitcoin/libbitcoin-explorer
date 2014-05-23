#ifndef SX_ENVIRONMENT_HPP
#define SX_ENVIRONMENT_HPP

#include <boost/filesystem.hpp>

// On windows std::string is non-unicode (char is ANSI and wchar_t is UCS-16).
#ifdef _WIN32
    typedef wchar_t tchar;
    typedef std::wstring tstring;
    typedef boost::filesystem::wpath tpath;
#else
    #define L
    typedef char tchar;
    typedef std::string tstring;
    typedef boost::filesystem::path tpath;
#endif

tstring home_directory();
tstring sx_config_path();

#endif