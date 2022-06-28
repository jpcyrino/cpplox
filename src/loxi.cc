#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "loxi.hh"

namespace Lox
{

int LoxI::run_file(char* file_name)
{
    std::ifstream script(file_name);
    std::ostringstream os;
    while(script.good()){
        os << (char) script.get();
    }
    script.close();
    run(os.str());
    return 0;
}

int LoxI::run_prompt()
{
    std::string line;
    std::cout << "> ";
    while(std::getline(std::cin, line))
    {
        run(line);
        std::cout << "> ";
    }
    return 0;
}

void LoxI::run(std::string source)
{
    std::cout << source << std::endl;
}

}