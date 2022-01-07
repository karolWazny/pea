#ifndef PEA_STRINGUTILS_H
#define PEA_STRINGUTILS_H

#include <algorithm>
#include <cctype>
#include <locale>

// trim from start (in place)
void ltrim(std::string &s);/* {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}*/

// trim from end (in place)
void rtrim(std::string &s);

// trim from both ends (in place)
void trim(std::string &s);

// trim from start (copying)
std::string ltrim_copy(std::string s);

// trim from end (copying)
std::string rtrim_copy(std::string s);

// trim from both ends (copying)
std::string trim_copy(std::string s);

char asciiToLower(char in);

char asciiToUpper(char in);

std::string& toLower(std::string& data);
std::string& toUpper(std::string& data);

std::string toLower_copy(const std::string& data);

std::string toUpper_copy(const std::string& data);

bool hasEnding (std::string const &fullString, std::string const &ending);


#endif //PEA_STRINGUTILS_H
