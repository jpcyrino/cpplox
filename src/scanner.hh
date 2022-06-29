#ifndef SCANNER_HH
#define SCANNER_HH

#include <vector>
#include <string>
#include "token.hh"

namespace Lox
{

class Scanner {
    std::vector<Token> tokens;
    const std::string source;
    size_t start = 0;
    size_t position = 0;
    int current_line = 1;

    void get_token();
    bool peek(char next_char);
    void add_single(TokenType token_type, std::string token_name);
    void add_double(TokenType token_type, std::string token_name);
    void handle_comment();
    void handle_numeric_literal();
    void handle_string_literal();

    void throw_scanner_error(std::string message);

public:
    Scanner(const std::string& source) : source(source) {}

    const std::vector<Token>& get_tokens() const { return tokens; }
    void start_scan();

};


}



#endif