#include <iostream>
#include <string>

#include "Command.h"
#include "Parser.h"

Command* Parser::parse(const std::string& code_line)
{
    std::cout << "Parsing... " << code_line << '\n';

    return new Command { };
}
