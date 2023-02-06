#include <stdexcept>
#include <iostream>
#include <string>

#include "CodeLine.h"
#include "Instruction.h"
#include "Parse.h"
#include "SyntaxError.h"

namespace Parse
{
    std::vector<Instruction*> parse(const std::vector<CodeLine>& code_lines)
    {
        if (ENABLE_DEBUG)
        {
            std::cout << "\nParsing..." << '\n';
        }

        std::vector<Instruction*> instructions { };

        for (CodeLine code_line : code_lines)
        {
            try
            {
                Instruction* instruction = parse_line(code_line);
                if (instruction != nullptr)
                {
                    instructions.push_back(instruction);
                }
            }
            catch (const SyntaxError ex)
            {
                throw SyntaxError { "While parsing: line "
                    + std::to_string(code_line.line) + ": " + ex.what() };
            }
        }

        return instructions;
    }

    Instruction* parse_line(CodeLine code_line)
    {
        if (ENABLE_DEBUG)
        {
            std::cout << code_line.line << ".\t" << code_line.code << '|';
        }

        if (code_line.code.rfind("@", 0) == 0)
        {
            // A-Instruction

            if (ENABLE_DEBUG)
            {
                std::cout << " :: A. ";
            }

            std::string value { code_line.code.substr(1) };

            if (ENABLE_DEBUG)
            {
                std::cout << "value = " << value << '\n';
            }

            // Make sure there are no non-digit characters after @
            if (value.find_first_not_of("0123456789") != std::string::npos)
            {
                throw SyntaxError { "Invalid A-Instruction" };
            }

            return new AInstruction { Instruction::OpType::A, code_line.line, value };
        }
        else
        {
            // If not an A-Instruction, assume it's a C-Instruction

            if (ENABLE_DEBUG)
            {
                std::cout << " :: C. ";
            }

            std::string dest { };
            std::string eq_rhs { };

            std::string::size_type eq_index { code_line.code.find_first_of('=') };
            if (eq_index != std::string::npos)
            {
                dest = code_line.code.substr(0, eq_index);
                eq_rhs = code_line.code.substr(eq_index + 1);
            }
            else
            {
                eq_rhs = code_line.code;
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

            if (ENABLE_DEBUG)
            {
                std::cout << "comp = " << comp << "; dest = " << dest << "; jmp = " << jmp << '\n';
            }

            bool isValid = (!dest.empty() && !comp.empty() && !jmp.empty())
                        || ( dest.empty() && !comp.empty() && !jmp.empty())
                        || (!dest.empty() && !comp.empty() &&  jmp.empty())
                        || ( dest.empty() && !comp.empty() &&  jmp.empty())
                        || ( dest.empty() &&  comp.empty() && !jmp.empty());

            if (!isValid)
            {
                throw SyntaxError { "Invalid C-Instruction" };
            }

            return new CInstruction { Instruction::OpType::C, code_line.line, dest, comp, jmp };
        }

        return new Instruction { };
    }

    void delete_instructions(std::vector<Instruction*> instructions)
    {
        for (Instruction* instruction : instructions)
        {
            if (instruction != nullptr)
            {
                delete instruction;
                instruction = nullptr;
            }
        }
    }

}
