#include "program/Main.h"
#include "program/PeaSetup.h"
#include "program/testers/SATester.h"
#include "program/testers/TSTester.h"

int main() {
    /*auto setup = PeaSetup();
    return Main(setup).run();*/
    SATester().test();
    int i;
    std::cin >> i;
}
