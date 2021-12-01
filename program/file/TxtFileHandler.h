#ifndef PEA_TXTFILEHANDLER_H
#define PEA_TXTFILEHANDLER_H


#include "FileHandler.h"

class TxtFileHandler : public FileHandler{
public:
    std::shared_ptr<int32_t[]> fromFile(const std::string& filename) override;
    void toFile(const TSPInputMatrix& matrix, std::string filename) override;
};


#endif //PEA_TXTFILEHANDLER_H
