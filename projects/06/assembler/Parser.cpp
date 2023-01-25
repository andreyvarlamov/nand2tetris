#include <exception>
#include <iostream>
#include <string>

#include "Instruction.h"
#include "Parser.h"

Instruction* Parser::parse(const std::string& code_line)
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
        // A-Instruction
        std::cout << " :: A. ";
        if (code_line.substr(1).find_first_not_of("0123456789 ") != std::string::npos)
        {
            throw std::runtime_error { "Syntax error: Invalid A-Instruction" };
        }
        std::string value { code_line.substr(1) };
        std::cout << "value = " << value << '\n';
        return new AInstruction { Instruction::OpType::A, value };
    }
    else
    {
        // If not an A-Instruction, assume it's a C-Instruction
        std::cout << " :: C\n";
        return new CInstruction { Instruction::OpType::C, "dest", "comp", "jmp" };
    }



    return new Instruction { };
}
