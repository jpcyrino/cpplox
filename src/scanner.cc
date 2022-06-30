#include <string>
#include <iostream>
#include "scanner.hh"

namespace Lox
{

void Scanner::start_scan()
{
    while(position < source.size())
    {
        get_token();
    }
}

void Scanner::get_token()
{
    switch(source[position]) 
    {
        case '\n':
            current_line++;
            position++;
            break;
        case ' ':
        case '\t':
        case '\r':
            position++;
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
            handle_lexical_item();
            break;
    }

}

void Scanner::add_single(TokenType token_type, std::string token_name)
{
    tokens.emplace_back(Token(token_type, std::move(token_name), current_line));
    position++;
}

void Scanner::add_double(TokenType token_type, std::string token_name)
{
    add_single(token_type, std::move(token_name));
    position += 2;
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
        position++;       
    }
}

void Scanner::handle_string_literal()
{
    buffer = "";
    position++;
    while(source[position] != '"')
    {
        if(position >= source.size())
        {
            // TODO: proper error handler
            std::cout << "Error line " << current_line << ": missing trailing \" for string.\n";
            return;
        }
        buffer += source[position];
        position++;
    }
    position++;
    tokens.emplace_back(Token(STRING, buffer, "string literal '" + buffer + "'", current_line));
}

bool Scanner::is_number()
{
    return (source[position] >= '0') && (source[position] <= '9');
}

bool Scanner::is_separator()
{
    switch(source[position])
    {
        case ' ':
        case '\t':
        case '\r':
        case '\n':
        case '(':
        case ')':
        case '{':
        case '}':
        case ';':
        case '.':
        case '+':
        case '-':
        case '*':
        case '/':
        case '=':
        case '!':
        case '>':
        case '<':
        case '"':
            return true;
        default:
            return false;
    }
}

void Scanner::handle_lexical_item()
{
    if(is_number())
    {
        handle_numeric_literal();
        return;
    }
    buffer = "";
    while(!is_separator())
    {
        if(position >= source.size()) break;
        buffer += source[position];
        position++;
    }
    add_lexical_item(buffer);
}

void Scanner::handle_numeric_literal()
{
    bool first_dot = false;
    buffer = "";
    while (is_number())
    {
        buffer += source[position];
        if (peek('.') && !first_dot) {
            first_dot = true;
            position++;
            buffer += source[position];
        }
        position++;
    }
    tokens.emplace_back(NUMBER, std::stod(buffer), "numeric literal " + buffer, current_line);
}

void Scanner::add_lexical_item(std::string item)
{
    for (auto& c : item) c = std::toupper(c);
    
    try
    {
        add_single(keywords.at(item), "keyword " + item);
    }
    catch (std::out_of_range e)
    {
        tokens.emplace_back(IDENTIFIER, item, "identifier " + item, current_line);
    }
}

}