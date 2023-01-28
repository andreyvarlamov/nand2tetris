#include <bitset>
#include <iostream>
#include <string>
#include <vector>

#include "Translate.h"
#include "Instruction.h"
#include "SyntaxError.h"

namespace Translate
{
    std::vector<std::string> translate(std::vector<Instruction*> instructions)
    {
        if (ENABLE_DEBUG)
        {
            std::cout << "\nTranslating..." << '\n';
        }

        std::vector<std::string> translated_lines { };

        for (std::size_t i = 0; i < instructions.size(); ++i)
        {
            std::string translated_line { };

            try
            {
                if (instructions[i]->optype == Instruction::OpType::A)
                {
                    translated_line =
                        translate_a_inst(static_cast<AInstruction*>(instructions[i]));
                }
                else
                {
                    translated_line =
                        translate_c_inst(static_cast<CInstruction*>(instructions[i]));
                }
            }
            catch (SyntaxError ex)
            {
                throw SyntaxError { "While translating: instruction " + std::to_string(i + 1) + ": " + ex.what() };
            }

            translated_lines.push_back(translated_line);
        }

        return translated_lines;
    }

    std::string translate_a_inst(AInstruction* a_inst)
    {
        if (ENABLE_DEBUG)
        {
            std::cout << "AInstruction. value = " << a_inst->value << '\n';
        }

        std::string b_value_str { };
        try
        {
            int value { std::stoi(a_inst->value) };
            std::bitset<15> b_value { value };
            b_value_str = b_value.to_string();
        }
        catch (...)
        {
            throw SyntaxError { "Failed to convert value of @ to int" };
        }

        return "0" + b_value_str;
    }
    std::string translate_c_inst(CInstruction* c_inst)
    {
        if (ENABLE_DEBUG)
        {
            std::cout << "CInstruction. dest = " << c_inst->dest 
                      << "; comp = " << c_inst->comp
                      << "; jmp = " << c_inst->jmp << '\n';
        }

        return "1110000000000000";
    }
}
