#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "Instruction.h"

namespace Parse
{
    constexpr bool ENABLE_DEBUG = true;
    std::vector<Instruction*> parse(const std::vector<std::string>& code_lines);
    Instruction* parse_line(std::string code_line);
    void delete_instructions(std::vector<Instruction*> instructions);
}
#endif
