#include "TextFileReader.h"

std::shared_ptr<int32_t[]> TextFileReader::fromFile(const std::string& filename) {
    read(filename);
    auto output = fileContent;
    return output;
}

void TextFileReader::read(const std::string& filename) {
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
