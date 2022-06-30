#ifndef SCANNER_HH
#define SCANNER_HH

#include <vector>
#include <string>
#include <unordered_map>
#include "token.hh"

namespace Lox
{

    

class Scanner {
    std::vector<Token> tokens;
    std::string source;
    std::string buffer;
    size_t position = 0;
    int current_line = 1;

    void get_token();
    bool peek(char next_char);
    bool is_number();
    bool is_separator();
    void add_single(TokenType token_type, std::string token_name);
    void add_double(TokenType token_type, std::string token_name);
    void handle_comment();
    void handle_numeric_literal();
    void handle_string_literal();
    void handle_lexical_item();
    void add_lexical_item(std::string item);

    const std::unordered_map<std::string, TokenType> keywords{
        {"AND", AND},
        {"CLASS", CLASS},
        {"ELSE", ELSE},
        {"FALSE", FALSE},
        {"FUN", FUN},
        {"FOR", FOR},
        {"IF", IF},
        {"NIL", NIL},
        {"OR", OR},
        {"PRINT", PRINT},
        {"RETURN", RETURN},
        {"SUPER", SUPER},
        {"THIS", THIS},
        {"TRUE", TRUE},
        {"VAR", VAR},
        {"WHILE", WHILE}
    };

public:
    explicit Scanner(std::string source)  { this->source = std::move(source); }

    const std::vector<Token>& get_tokens() const { return tokens; }
    void start_scan();

};


}



#endif