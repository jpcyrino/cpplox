#include <fstream>
#include <iostream>
#include "loxi.hh"

int main(int argc, char** argv)
{
    return (argc > 1) ? Lox::LoxI::run_file(argv[1]) : Lox::LoxI::run_prompt();
}
