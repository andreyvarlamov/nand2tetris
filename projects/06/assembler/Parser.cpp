#include <algorithm>
#include <cctype>
#include <exception>
#include <iostream>
#include <string>

#include "Instruction.h"
#include "Parser.h"

bool Parser::enable_debug = false;

Instruction* Parser::parse(std::string code_line)
{
    if (enable_debug)
    {
        std::cout << code_line << '|';
    }

    // Skip comments
    if (code_line.rfind("//", 0) == 0)
    {
        if (enable_debug)
        {
            std::cout << " :: Comment\n";
        }
        return nullptr;
    }

    // Skip empty lines
    if (code_line.empty() || code_line.find_first_not_of(' ') == std::string::npos)
    {
        if (enable_debug)
        {
            std::cout << " :: Empty\n";
        }
        return nullptr;
    }

    // Strip the code_line of any whitespace
    code_line.erase(remove_if(code_line.begin(), code_line.end(),
                              [](unsigned char c){ return std::isspace(c); }
                             ), code_line.end());

    if (code_line.rfind("@", 0) == 0)
    {
        // A-Instruction

        if (enable_debug)
        {
            std::cout << " :: A. ";
        }

        std::string value { code_line.substr(1) };

        // Make sure there are no non-digit characters after @
        if (value.find_first_not_of("0123456789") != std::string::npos)
        {
            throw std::runtime_error { "Parser error: Invalid A-Instruction" };
        }

        if (enable_debug)
        {
            std::cout << "value = " << value << '\n';
        }
        return new AInstruction { Instruction::OpType::A, value };
    }
    else
    {
        // If not an A-Instruction, assume it's a C-Instruction

        if (enable_debug)
        {
            std::cout << " :: C. ";
        }

        std::string dest { };
        std::string eq_rhs { };

        std::string::size_type eq_index { code_line.find_first_of('=') };
        if (eq_index != std::string::npos)
        {
            dest = code_line.substr(0, eq_index);
            eq_rhs = code_line.substr(eq_index + 1);
        }
        else
        {
            eq_rhs = code_line;
        }

        std::string comp { };
        std::string jmp { };

        std::string::size_type semicolon_index { eq_rhs.find_first_of(';') };

        if (semicolon_index != std::string::npos)
        {
            comp = eq_rhs.substr(0, semicolon_index);
            jmp = eq_rhs.substr(semicolon_index + 1);
        }
        else
        {
            comp = eq_rhs;
        }

        if (enable_debug)
        {
            std::cout << "comp = " << comp << "; dest = " << dest << "; jmp = " << jmp << '\n';
        }

        // If both comp and jmp are empty, there's a syntax error
        if (comp.empty() && jmp.empty())
        {
            throw std::runtime_error { "Parser error: Invalid C-Instruction" };
        }

        return new CInstruction { Instruction::OpType::C, comp, dest, jmp };
    }

    return new Instruction { };
}
