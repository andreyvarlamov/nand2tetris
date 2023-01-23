#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

class Parser
{
private:
    std::vector<std::string> m_code_lines;

public:
    Parser(const std::vector<std::string>& code_lines);
    std::vector<std::string> parse();
};

#endif
