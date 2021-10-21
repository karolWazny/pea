#ifndef PEA_PROGRAMSETUP_H
#define PEA_PROGRAMSETUP_H

#include "Program.h"


class ProgramSetup {
public:
    virtual void setup(Program& program) = 0;
};


#endif //PEA_PROGRAMSETUP_H
