#ifndef LOXI_HH
#define LOXI_HH

#include <string>

namespace Lox {

struct LoxI {
    static int run_file(char* file_name);
    static int run_prompt();
private:
    static void run(std::string source);
};

}

#endif