#include <iomanip>
#include "AtspFileHandler.h"

std::shared_ptr<int32_t[]> AtspFileHandler::fromFile(const std::string& filename) {
    read(filename);
    auto output = fileContent;
    return output;
}

void AtspFileHandler::read(const std::string& filename) {
    std::ifstream stream;
    stream.open(filename);
    std::string buffer;
    int dimension = 0;
    while(!stream.eof()) {
        stream >> buffer;
        if(buffer == "DIMENSION:"){
            stream >> dimension;
        } else if(buffer == "EDGE_WEIGHT_TYPE:") {
            stream >> edgeWeightType;
        } else if(buffer == "EDGE_WEIGHT_FORMAT:") {
            stream >> edgeWeightFormat;
        } else if(buffer == "EDGE_WEIGHT_SECTION" && dimension){
            size_t dataSize = dimension * dimension + 1;
            fileContent = std::shared_ptr<int32_t[]>(new int32_t[dataSize]);
            fileContent[0] = dimension;
            for(int i = 1; i < dataSize; i++){
                stream >> fileContent[i];
            }
        } else {
            std::getline(stream, buffer);
        }
    }
}

void AtspFileHandler::toFile(const TSPInputMatrix& matrix, std::string filename) {
    std::ofstream stream;
    stream.open(filename);

    stream << "NAME: " << filename << std::endl;

    stream << "TYPE: ATSP\nCOMMENT:\nDIMENSION: " << std::to_string(matrix.size()) << std::endl;

    stream << "EDGE_WEIGHT_TYPE: EXPLICIT\nEDGE_WEIGHT_FORMAT: FULL_MATRIX\nEDGE_WEIGHT_SECTION" << std::endl;

    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.size(); j++){
            stream << std::right << std::setw(5) << std::to_string(matrix.getDistance(i, j)) << " ";
        }
        stream << std::endl;
    }

    stream << "EOF";
}
