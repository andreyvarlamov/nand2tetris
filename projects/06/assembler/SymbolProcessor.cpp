#include "SymbolProcessor.h"

#include <vector>

#include "CodeLine.h"

std::vector<CodeLine> SymbolProcessor::process_symbols(const std::vector<CodeLine>& code_lines)
{
    std::vector<CodeLine> no_labels { scan_labels(code_lines) };
    return std::vector<CodeLine> { replace_symbols(no_labels) };
}

std::vector<CodeLine> SymbolProcessor::scan_labels(const std::vector<CodeLine>& code_lines)
{
    std::vector<CodeLine> no_labels { };

    return no_labels;
}

std::vector<CodeLine> SymbolProcessor::replace_symbols(const std::vector<CodeLine>& code_lines)
{
    std::vector<CodeLine> no_symbols { };

    return no_symbols;
}
