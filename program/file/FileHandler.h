#ifndef PEA_FILEHANDLER_H
#define PEA_FILEHANDLER_H


#include <memory>
#include <string>
#include "../../tspalgorithms/TSPInputMatrix.h"

class FileHandler {
public:
    virtual std::shared_ptr<int32_t[]> fromFile(const std::string& filename) = 0;
    virtual void toFile(const TSPInputMatrix& matrix, std::string filename) = 0;
};


#endif //PEA_FILEHANDLER_H
