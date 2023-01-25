#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "Instruction.h"

class Parser
{
private:

public:
    static Instruction* parse(std::string code_line);
};

#endif
