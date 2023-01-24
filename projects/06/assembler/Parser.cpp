#include <iostream>
#include <string>

#include "Command.h"
#include "Parser.h"

Command* Parser::parse(const std::string& code_line)
{
    // Skip comments
    if (code_line.rfind("//", 0) == 0)
    {
        std::cout << "Skipping comment\n";
        return nullptr;
    }

    // Skip empty lines
    if (code_line.empty() || code_line.find_first_not_of(' ') == std::string::npos)
    {
        std::cout << "Skipping empty line\n";
        return nullptr;
    }

    std::cout << code_line << '\n';

    return new Command { };
}
