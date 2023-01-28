#include <string>
#include <vector>

#include "Instruction.h"

namespace Translate
{
    constexpr bool ENABLE_DEBUG = true;
    std::vector<std::string> translate(std::vector<Instruction*> instructions);
    std::string translate_instruction(Instruction* instruction);
}
