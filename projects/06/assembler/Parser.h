#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "Command.h"

class Parser
{
private:

public:
    static Command* parse(const std::string& code_line);
};

#endif
