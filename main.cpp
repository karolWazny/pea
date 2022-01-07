#include "program/Main.h"
#include "program/PeaSetup.h"

int main() {
    auto setup = PeaSetup();
    return Main(setup).run();
}

/*
#include <string>
#include <iostream>
#include <filesystem>
#include "utils/stringutils.h"

namespace fs = std::filesystem;

int main()
{
    std::filesystem::path cwd = std::filesystem::current_path();
    std::string path = cwd.string();
    for (const auto & entry : fs::directory_iterator(path)){
        if(hasEnding(entry.path().filename().string(), ".atsp"))
            std::cout << entry.path().filename().string() << std::endl;
    }
}*/
