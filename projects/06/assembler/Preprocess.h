#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <vector>

#include "CodeLine.h"

namespace Preprocess
{
    std::vector<CodeLine> preprocess(const std::vector<CodeLine>& code_lines);
}

#endif
