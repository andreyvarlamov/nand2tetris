#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

struct Instruction
{
    enum class OpType
    {
        A,
        C
    };

    OpType optype;
    int line_index;
};

struct AInstruction : public Instruction
{
    std::string value;
};

struct CInstruction : public Instruction
{
    std::string dest;
    std::string comp;
    std::string jmp;
};

#endif
