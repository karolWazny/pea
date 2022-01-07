#include "stringutils.h"

// trim from start (in place)
void ltrim(std::string &s){
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

char asciiToLower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

char asciiToUpper(char in) {
    if (in <= 'z' && in >= 'a')
        return in + ('Z' - 'z');
    return in;
}

std::string& toLower(std::string& data){
    std::transform(data.begin(), data.end(), data.begin(), asciiToLower);
    return data;
}

std::string& toUpper(std::string& data){
    std::transform(data.begin(), data.end(), data.begin(), asciiToUpper);
    return data;
}

std::string toLower_copy(const std::string& data){
    std::string copy = data;
    toLower(copy);
    return copy;
};

std::string toUpper_copy(const std::string& data){
    std::string copy = data;
    toUpper(copy);
    return copy;
};

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

