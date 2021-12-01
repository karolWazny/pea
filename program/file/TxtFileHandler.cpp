#include <fstream>
#include <iomanip>
#include "TxtFileHandler.h"

void TxtFileHandler::toFile(const TSPInputMatrix& matrix, std::string filename) {
    std::ofstream stream;
    stream.open(filename);

    stream << std::to_string(matrix.size()) << std::endl;

    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.size(); j++){
            stream << std::right << std::setw(5) << std::to_string(matrix.getDistance(i, j)) << " ";
        }
        stream << std::endl;
    }
}

std::shared_ptr<int32_t[]> TxtFileHandler::fromFile(const std::string &filename) {
    std::ifstream stream;
    stream.open(filename);
    std::string buffer;
    int dimension = 0;
    stream >> dimension;
    auto dataSize = dimension * dimension + 1;
    auto fileContent = std::shared_ptr<int32_t[]>(new int32_t[dataSize]);

    fileContent[0] = dimension;

    for(int i = 1; i < dataSize; i++){
        stream >> fileContent[i];
    }

    return fileContent;
}
