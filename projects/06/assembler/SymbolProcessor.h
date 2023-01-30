#ifndef SYMBOLPROCESSOR_H
#define SYMBOLPROCESSOR_H

#include <vector>

#include "CodeLine.h"
#include "SymbolTable.h"

class SymbolProcessor
{
private:
    SymbolTable m_symbol_table { };
    std::vector<CodeLine> scan_labels(const std::vector<CodeLine>& code_lines);
    std::vector<CodeLine> replace_symbols(const std::vector<CodeLine>& code_lines);

public:
    std::vector<CodeLine> process_symbols(const std::vector<CodeLine>& code_lines);
};

#endif
