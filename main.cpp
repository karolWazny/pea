#include "program/Main.h"
#include "program/PeaSetup.h"

int main() {
    auto setup = PeaSetup();
    return Main(setup).run();
}
