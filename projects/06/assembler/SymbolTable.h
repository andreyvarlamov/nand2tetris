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
    void push_label(std::string label, int line_num);
    int assign_and_push_symbol(std::string symbol);
    int get_or_assign_symbol(std::string symbol);
    void print();
};

#endif
