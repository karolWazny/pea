#ifndef SDIZO2_TEXTFILEREADER_H
#define SDIZO2_TEXTFILEREADER_H

#include <memory>
#include <string>
#include <fstream>
#include <iostream>

class TextFileReader {
public:
    std::shared_ptr<int32_t[]> fromFile(const std::string& filename);

private:
    void read(const std::string&);

    std::string name;
    std::string edgeWeightType;
    std::string edgeWeightFormat;

    std::shared_ptr<int32_t[]> fileContent;
};

#endif //SDIZO2_TEXTFILEREADER_H
