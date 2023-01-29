#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <vector>

#include "CodeLine.h"
#include "Instruction.h"

namespace Parse
{
    constexpr bool ENABLE_DEBUG = true;
    std::vector<Instruction*> parse(const std::vector<CodeLine>& code_lines);
    Instruction* parse_line(CodeLine code_line);
    void delete_instructions(std::vector<Instruction*> instructions);
}

#endif
