#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <string>
#include <vector>

#include "Instruction.h"

namespace Translate
{
    constexpr bool ENABLE_DEBUG = false;
    std::vector<std::string> translate(std::vector<Instruction*> instructions);
    std::string translate_a_inst(AInstruction* a_inst);
    std::string translate_c_inst(CInstruction* c_inst);
}

#endif
