#include <fstream>
#include <iostream>

int runFile(char* fileName);

int runPrompt(void);

int main(int argc, char** argv)
{
    return (argc > 1) ? runFile(argv[1]) : runPrompt();
}

int runFile(char* fileName)
{
    std::cout << fileName << std::endl;
    return 0;
}

int runPrompt()
{
    std::cout << "this is the prompt" << std::endl;
    return 0;
}