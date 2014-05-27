#ifndef SX_COMPAT_H
#define SX_COMPAT_H

#include <boost/filesystem.hpp>

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

#endif