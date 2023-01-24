#include <exception>
#include <iostream>
#include <string>

#include "Command.h"
#include "Parser.h"

Command* Parser::parse(const std::string& code_line)
{
    std::cout << code_line << '|';

    // Skip comments
    if (code_line.rfind("//", 0) == 0)
    {
        std::cout << " :: Comment\n";
        return nullptr;
    }

    // Skip empty lines
    if (code_line.empty() || code_line.find_first_not_of(' ') == std::string::npos)
    {
        std::cout << " :: Empty\n";
        return nullptr;
    }

    if (code_line.rfind("@", 0) == 0)
    {
        // A-Command
        std::cout << " :: A. ";
        if (code_line.substr(1).find_first_not_of("0123456789 ") != std::string::npos)
        {
            throw std::runtime_error { "Syntax error: Invalid A-Command" };
        }
        std::string value { code_line.substr(1) };
        std::cout << "value = " << value << '\n';
        return new CommandA { Command::OpType::A, value };
    }
    else
    {
        // If not A-Command, assume it's C-Command
        std::cout << " :: C\n";
        return new CommandC { Command::OpType::C, "dest", "comp", "jmp" };
    }



    return new Command { };
}
