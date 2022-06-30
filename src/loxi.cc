#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "loxi.hh"
#include "token.hh"
#include "scanner.hh"

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
    std::string script_code = os.str();
    run(script_code);
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

void LoxI::run(std::string& source)
{
    auto s = Scanner(source);
    s.start_scan();
    for(auto& t : s.get_tokens())
    {
        std::cout << "Token is " << t.get_message() << " line " << t.get_line() << std::endl;
    }
}

}