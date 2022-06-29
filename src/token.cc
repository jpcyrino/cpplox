#include <string>
#include <stdexcept>
#include "token.hh"

namespace Lox
{

double Token::get_numeric_value() const
{
    if(type == NUMBER) return numeric_value;
    throw std::logic_error("Error: no numeric value for " + name);
}

std::string Token::get_string_value() const
{
    if(type == STRING) return string_value;
    throw std::logic_error("Error: no string value for " + name);
}


}