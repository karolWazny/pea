#ifndef PEA_STRINGUTILS_H
#define PEA_STRINGUTILS_H

#include <algorithm>
#include <cctype>
#include <locale>

// trim from start (in place)
static inline void ltrim(std::string &s);

// trim from end (in place)
static inline void rtrim(std::string &s);

// trim from both ends (in place)
static inline void trim(std::string &s);

// trim from start (copying)
static inline std::string ltrim_copy(std::string s);

// trim from end (copying)
static inline std::string rtrim_copy(std::string s);

// trim from both ends (copying)
static inline std::string trim_copy(std::string s);

char asciiToLower(char in);

char asciiToUpper(char in);

std::string toLower_copy(const std::string&);

std::string toUpper_copy(const std::string&);

std::string& toLower(std::string&);

std::string& toUpper(std::string&);

#endif //PEA_STRINGUTILS_H
