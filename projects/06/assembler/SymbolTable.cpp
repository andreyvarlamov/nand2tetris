#include <iostream>
#include <map>
#include <string>

#include "SymbolTable.h"
#include "SyntaxError.h"

SymbolTable::SymbolTable()
{
    m_symbols = std::map<std::string, int>
    {
        { "SP",    0  },
        { "LCL",   1  },
        { "ARG",   2  },
        { "THIS",  3  },
        { "THAT",  4  },

        { "R0",  0  },
        { "R1",  1  },
        { "R2",  2  },
        { "R3",  3  },
        { "R4",  4  },
        { "R5",  5  },
        { "R6",  6  },
        { "R7",  7  },
        { "R8",  8  },
        { "R9",  9  },
        { "R10", 10 },
        { "R11", 11 },
        { "R12", 12 },
        { "R13", 13 },
        { "R14", 14 },
        { "R15", 15 },

        { "SCREEN", 16384 },
        { "KBD",    24576 },
    };

    current_ram_pointer = 16;
}

void SymbolTable::push_label(std::string label, int line_num)
{
    if (m_symbols.find(label) != m_symbols.end())
    {
        throw SyntaxError { "Symbol Table already contains symbol: " + label + "." };
    }

    m_symbols[label] = line_num;
}

int SymbolTable::get_or_assign_symbol(std::string symbol)
{
    int symbol_value { };

    if (m_symbols.find(symbol) != m_symbols.end())
    {
         symbol_value = m_symbols[symbol];
    }
    else
    {
        m_symbols[symbol] = current_ram_pointer;
        symbol_value = current_ram_pointer;
        ++current_ram_pointer;
    }

    return symbol_value;
}

void SymbolTable::print()
{
    std::cout << "\nPrinting Symbol Table\n";

    for (auto symbol : m_symbols)
    {
        std::cout << symbol.first << ": " << symbol.second << '\n';
    }
}
