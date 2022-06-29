#ifndef TOKEN_HH
#define TOKEN_HH

#include <string>

namespace Lox
{

enum TokenType {
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, 
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    BANG, BANG_EQUAL, 
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    IDENTIFIER, STRING, NUMBER,

    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    EOFILE
};

class Token {
    const TokenType type;
    const std::string name;
    const double numeric_value;
    const std::string string_value; 
    const int line;
public:
    Token(TokenType token, std::string token_name, int line) : 
        type(token), name(token_name), line(line), numeric_value(0) {}
    Token(TokenType token, double value, std::string token_name, int line) : 
        type(token), name(token_name), line(line), numeric_value(value) {}
    Token(TokenType token, std::string value, std::string token_name, int line) :
        type(token), name(token_name), line(line), numeric_value(0), string_value(value) {}
    TokenType get_type() const { return type; }
    std::string get_message() const { return name; }
    int get_line() const { return line; }
    double get_numeric_value() const;
    std::string get_string_value() const;
};

}


#endif