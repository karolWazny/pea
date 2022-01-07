//
// Created by admin on 07.01.2022.
//

#include <string>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include "timestring.h"

std::string formattedTimeString(const std::string& format){
    std::stringstream output;
    const auto timePoint = std::chrono::system_clock::now();
    const auto t_c = std::chrono::system_clock::to_time_t(timePoint);
    output << std::put_time(std::localtime(&t_c), format.c_str());
    auto outputString = output.str();
    return outputString;
}

std::string dateTimeStringFilenameFormat(){
    auto outputString = formattedTimeString("%F_%T");
    std::replace(outputString.begin(), outputString.end(), ':', '-');
    return outputString;
}

std::string dateTimeString(){
    return formattedTimeString("%F %T");
}

std::string dateString(){
    return formattedTimeString("%F");
}

std::string timeString(){
    return formattedTimeString("%T");
}