#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <string>

class SymbolTable
{
private:
    int current_ram_pointer;
    std::map<std::string, int> m_symbols;
public:
    SymbolTable();
};

#endif
