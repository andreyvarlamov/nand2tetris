#include <bitset>
#include <iostream>
#include <map>
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

        for (Instruction* instruction : instructions)
        {
            std::string translated_line { };

            try
            {
                if (instruction->optype == Instruction::OpType::A)
                {
                    translated_line =
                        translate_a_inst(static_cast<AInstruction*>(instruction));
                }
                else
                {
                    translated_line =
                        translate_c_inst(static_cast<CInstruction*>(instruction));
                }
            }
            catch (SyntaxError ex)
            {
                throw SyntaxError { "While translating: instruction "
                    + std::to_string(instruction->line_index)
                    + ": " + ex.what() };
            }

            translated_lines.push_back(translated_line);
        }

        return translated_lines;
    }

    std::string translate_a_inst(AInstruction* a_inst)
    {
        if (ENABLE_DEBUG)
        {
            std::cout << "A. value = " << a_inst->value << '\n';
        }

        std::string b_value_str { };
        try
        {
            int value { std::stoi(a_inst->value) };
            std::bitset<15> b_value { static_cast<unsigned int>(value) };
            b_value_str = b_value.to_string();
        }
        catch (...)
        {
            throw SyntaxError { "A-Instruction: Failed to convert value of @." };
        }

        return "0" + b_value_str;
    }

    std::string translate_c_inst(CInstruction* c_inst)
    {
        if (ENABLE_DEBUG)
        {
            std::cout << "C. dest = " << c_inst->dest 
                      << "; comp = " << c_inst->comp
                      << "; jmp = " << c_inst->jmp << '\n';
        }

        std::map<std::string, std::string> dest_dict
        {
            { ""   , "000" },
            { "M"  , "001" },
            { "D"  , "010" },
            { "MD" , "011" },
            { "A"  , "100" },
            { "AM" , "101" },
            { "AD" , "110" },
            { "AMD", "111" }
        };

        std::map<std::string, std::string> comp_dict
        {
            { ""   , "0000000" }, // when no comp it will actually do D&A,
                                  // but it doesnt matter because the only
                                  // sensible scenario in which comp is nothing
                                  // is ';JMP'
            { "0"  , "0101010" },
            { "1"  , "0111111" },
            { "-1" , "0111010" },
            { "D"  , "0001100" },
            { "A"  , "0110000" },
            { "!D" , "0001101" },
            { "!A" , "0110001" },
            { "-D" , "0001111" },
            { "-A" , "0110011" },
            { "D+1", "0011111" },
            { "A+1", "0110111" },
            { "D-1", "0001110" },
            { "A-1", "0110010" },
            { "D+A", "0000010" },
            { "D-A", "0010011" },
            { "A-D", "0000111" },
            { "D&A", "0000000" },
            { "D|A", "0010101" },

            { "M"  , "1110000" },
            { "!M" , "1110001" },
            { "-M" , "1110011" },
            { "M+1", "1110111" },
            { "M-1", "1110010" },
            { "D+M", "1000010" },
            { "D-M", "1010011" },
            { "M-D", "1000111" },
            { "D&M", "1000000" },
            { "D|M", "1010101" }
        };

        std::map<std::string, std::string> jmp_dict
        {
            { ""   , "000" },
            { "JGT", "001" },
            { "JEQ", "010" },
            { "JGE", "011" },
            { "JLT", "100" },
            { "JNE", "101" },
            { "JLE", "110" },
            { "JMP", "111" },
        };

        if (dest_dict.find(c_inst->dest) == dest_dict.end())
        {
            throw SyntaxError { "C-Instruction: Invalid dest." };
        }
        else if (comp_dict.find(c_inst->comp) == comp_dict.end())
        {
            throw SyntaxError { "C-Instruction: Invalid comp." };
        }
        else if (jmp_dict.find(c_inst->jmp) == jmp_dict.end())
        {
            throw SyntaxError { "C-Instruction: Invalid jmp." };
        }

        return "111" + comp_dict[c_inst->comp] + dest_dict[c_inst->dest]
            + jmp_dict[c_inst->jmp];
    }
}
