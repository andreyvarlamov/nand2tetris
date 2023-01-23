#include <iostream>

#include "Parser.h"

Parser::Parser(const std::vector<std::string>& code_lines)
    : m_code_lines { code_lines }
{
}

std::vector<std::string> Parser::parse()
{
    std::cout << "Parsing...\n";

    std::vector<std::string> parsed_lines { m_code_lines };
    return parsed_lines;
}
