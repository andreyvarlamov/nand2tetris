#include "SymbolProcessor.h"

// TODO: Remove
#include <iostream>
#include <string>
#include <vector>

#include "CodeLine.h"
#include "SymbolTable.h"
#include "SyntaxError.h"

std::vector<CodeLine> SymbolProcessor::process_symbols(const std::vector<CodeLine>& code_lines)
{
    std::vector<CodeLine> no_labels { };
    std::vector<CodeLine> no_symbols { };

    try
    {
        no_labels = scan_labels(code_lines);
    }
    catch (SyntaxError ex)
    {
        throw SyntaxError { "While scanning labels: line "
            + std::to_string(code_lines.line) + ": " + ex.what() };
    }

    try
    {
        no_symbols = replace_symbols(no_labels);
    }
    catch (SyntaxError ex)
    {
        throw SyntaxError { "While replacing symbols: line "
            + std::to_string(code_lines.line) + ": " + ex.what() };
    }

    std::cout << "\nPrinting Symbol Table\n"
    for (const std::map<std::string, int>::iterator& const& symbol : m_symbols)
    {
        std::cout << symbol.first << ": " << symbol.second << '\n';
    }

    return no_symbols;
}

std::vector<CodeLine> SymbolProcessor::scan_labels(const std::vector<CodeLine>& code_lines)
{
    std::vector<CodeLine> no_labels { };
    int no_label_line_index { };

    for (CodeLine code_line : code_lines)
    {
        std::string::size_type first_open_parenthesis { code_line.code.find_first_of('(') };
        std::string::size_type last_open_parenthesis { code_line.code.find_last_of('(') };
        std::string::size_type first_closed_parenthesis { code_line.code.find_first_of(')') };
        std::string::size_type first_non_digit { code_line.code.find_first_not_of("0123456789()") };
        if (first_open_parenthesis != 0)
        {
            if (last_open_parenthesis == 0
                && first_closed_parenthesis == code_line.code.length() - 1
                && first_non_digit == 1)
            {
                m_symbol_table.push_label(
                        code_line.code.substr(1, code_line.code.length() - 2),
                        no_label_line_index);

                // TODO: Syntax Error if repeated labels
                // TODO: Syntax Error if label is on the last line
            }

            throw SyntaxError { "Invalid label" };
        }
        else
        {
            no_labels.push_back(code_line);
            ++no_label_line_index;
        }
    }

    return no_labels;
}

std::vector<CodeLine> SymbolProcessor::replace_symbols(const std::vector<CodeLine>& code_lines)
{
    std::vector<CodeLine> no_symbols { };

    return no_symbols;
}
