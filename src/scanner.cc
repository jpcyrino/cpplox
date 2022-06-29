#include <iostream>
#include "scanner.hh"

namespace Lox
{

void Scanner::start_scan()
{
    while(position < source.size())
    {
        get_token();
        position++;
    }
}

void Scanner::get_token()
{
    switch(source[position]) 
    {
        case '\n':
            current_line++;
            start++;
            break;
        case ' ':
        case '\t':
        case '\r':
            start++;
            break;
        case '(': 
            add_single(LEFT_PAREN, "symbol '('");
            break;
        case ')':
            add_single(RIGHT_PAREN, "symbol ')'");
            break;
        case '{':
            add_single(LEFT_BRACE, "symbol '{'");
            break;
        case '}':
            add_single(RIGHT_BRACE, "symbol '}'");
            break;
        case ',':
            add_single(COMMA, "symbol ','");
            break;
        case '.':
            add_single(DOT, "symbol '.'");
            break;
        case ';':
            add_single(SEMICOLON, "symbol ';'");
            break;
        case '+':
            add_single(PLUS, "symbol '+'");
            break;
        case '-':
            add_single(MINUS, "symbol '-'");
            break;
        case '/':
            add_single(SLASH, "symbol '/'");
            break;
        case '*':
            add_single(STAR, "symbol '*'");
            break;
        case '!':
            peek('=') ? add_double(BANG_EQUAL, "symbol '!='") : add_single(BANG, "symbol '!'");
            break;
        case '=':
            peek('=') ? add_double(EQUAL_EQUAL, "symbol '=='") : add_single(EQUAL, "symbol '='");
            break;
        case '>':
            peek('=') ? add_double(GREATER_EQUAL, "symbol '>='") : add_single(GREATER, "symbol '>'");
            break;
        case '<':
            peek('=') ? add_double(LESS_EQUAL, "symbol '<='") : add_single(LESS, "symbol '<'");
            break;
        default:
            break;
    }

}

void Scanner::add_single(TokenType token_type, std::string token_name)
{
    tokens.push_back(Token(token_type, token_name, current_line));
    start++;
}

void Scanner::add_double(TokenType token_type, std::string token_name)
{
    add_single(token_type, token_name);
    start++;
    position++;
}

bool Scanner::peek(char next_char)
{
    if(position + 1 >= source.size()) return false;
    if(source[position + 1] == next_char) return true;
    return false;
}








}