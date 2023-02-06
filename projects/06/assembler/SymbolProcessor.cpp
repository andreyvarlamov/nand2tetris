#include "SymbolProcessor.h"

// TODO: Remove
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "CodeLine.h"
#include "SymbolTable.h"
#include "SyntaxError.h"

std::vector<CodeLine> SymbolProcessor::process_symbols(const std::vector<CodeLine>& code_lines)
{
    if (ENABLE_DEBUG)
    {
        std::cout << "\nProcessing symbols..." << '\n';
    }

    std::vector<CodeLine> no_labels { };
    std::vector<CodeLine> no_symbols { };

    try
    {
        no_labels = scan_labels(code_lines);
    }
    catch (SyntaxError ex)
    {
        throw SyntaxError { "While scanning labels: " + std::string { ex.what() } };
    }

    try
    {
        no_symbols = replace_symbols(no_labels);
    }
    catch (SyntaxError ex)
    {
        throw SyntaxError { "While replacing symbols: " + std::string { ex.what() } };
    }

    if (ENABLE_DEBUG)
    {
        m_symbol_table.print();
    }

    if (ENABLE_DEBUG)
    {
        std::cout << "\nPrinting symbolless code" << '\n';
        for (CodeLine code_line : no_symbols)
        {
            std::cout << code_line.line << ": " << code_line.code << '\n';
        }
    }

    return no_symbols;
}

std::vector<CodeLine> SymbolProcessor::scan_labels(const std::vector<CodeLine>& code_lines)
{
    if (ENABLE_DEBUG)
    {
        std::cout << "\nScanning labels..." << '\n';
    }

    std::vector<CodeLine> no_labels { };
    int no_label_line_index { };

    for (CodeLine code_line : code_lines)
    {
        std::string::size_type first_open_parenthesis { code_line.code.find_first_of('(') };
        std::string::size_type last_open_parenthesis { code_line.code.find_last_of('(') };
        std::string::size_type first_closed_parenthesis { code_line.code.find_first_of(')') };
        std::string::size_type first_non_digit { code_line.code.find_first_not_of("0123456789()") };
        if (first_open_parenthesis == 0)
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
            else
            {
                throw SyntaxError { "Line " + std::to_string(code_line.line)
                    + ": Invalid label" };
            }
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
    if (ENABLE_DEBUG)
    {
        std::cout << "\nReplacing symbols..." << '\n';
    }

    std::vector<CodeLine> no_symbols { };

    for (CodeLine code_line : code_lines)
    {
        if (code_line.code.find_first_of('@') == 0)
        {
            // Further analyze all A-Instructions
            std::string a_value { code_line.code.substr(1) };

            // That have a non-digit character
            // TODO: Should be just alpha characters
            if (a_value.find_first_not_of("0123456789") != std::string::npos)
            {
                if (a_value.find_first_not_of("012345689") == 0)
                {
                    // If it starts with non-digit character, that's a symbol
                    int symbol_value { m_symbol_table.get_or_assign_symbol(a_value) };
                    std::string no_symbols_code { '@' + std::to_string(symbol_value) };
                    no_symbols.push_back(CodeLine { code_line.line, no_symbols_code });
                }
                else
                {
                    // If it starts with a digit, that's not valid
                    throw SyntaxError { "Line " + std::to_string(code_line.line)
                        + ": Variable name cannot start with a digit." };
                }
            }
            else
            {
                // All A-Instructions that don't non-digit characters can be
                // added with no changes
                no_symbols.push_back(code_line);
            }
        }
        else
        {
            // Non A-Instructions can be added with no changes
            no_symbols.push_back(code_line);
        }
    }

    return no_symbols;
}
