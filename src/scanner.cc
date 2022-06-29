#include <iostream>
#include <string>
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
            peek('/') ? handle_comment() : add_single(SLASH, "symbol '/'");
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
        case '"':
            handle_string_literal();
            break;
        default:
            handle_numeric_literal();
            handle_lexical_item();
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

void Scanner::handle_comment()
{
    while(!peek('\n'))
    {
        if(position >= source.size()) break;
        start++;
        position++;       
    }
}

void Scanner::handle_string_literal()
{
    position++;
    start = position;
    while(source[position] != '"')
    {
        position++;
        if(position >= source.size())
        {
            throw_scanner_error("Missing trailing \" at string literal");
            return;
        }
    }
    std::string string_literal = source.substr(start, position-start);
    tokens.push_back(Token(STRING, string_literal, "string literal '" + string_literal + "'", current_line));
    start = position + 1;
}


void Scanner::throw_scanner_error(std::string message)
{
    std::cout << "Scanner error at line " << current_line << ": " << message << std::endl;
    position = source.size();
}

bool Scanner::is_number()
{
    return (source[position] >= '0') && (source[position] <= '9');
}

void Scanner::handle_numeric_literal()
{
    if(!is_number()) return;
    bool found_decimal = false;
    while(is_number())
    {
        if(peek('.')){
            position++;
            if(found_decimal) {
                throw_scanner_error("invalid numeric literal " + source.substr(start,position-start+1));
                return;
            }
            found_decimal = true;
        }
        position++;
    }
    std::string number_literal = source.substr(start, position-start);
    double numeric_value = std::stod(number_literal);
    tokens.push_back(Token(NUMBER, numeric_value, "number literal " + number_literal, current_line));
    start = position;
}

void Scanner::handle_lexical_item()
{
    if(is_number()) return;
    start++;
}




}