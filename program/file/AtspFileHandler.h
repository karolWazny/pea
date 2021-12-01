#ifndef SDIZO2_TEXTFILEREADER_H
#define SDIZO2_TEXTFILEREADER_H

#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include "FileHandler.h"

class AtspFileHandler : public FileHandler{
public:
    std::shared_ptr<int32_t[]> fromFile(const std::string& filename) override;
    void toFile(const TSPInputMatrix& matrix, std::string filename) override;

private:
    void read(const std::string&);

    std::string name;
    std::string edgeWeightType;
    std::string edgeWeightFormat;

    std::shared_ptr<int32_t[]> fileContent;
};

#endif //SDIZO2_TEXTFILEREADER_H
