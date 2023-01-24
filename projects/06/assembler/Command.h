#ifndef COMMAND_H
#define COMMAND_H

#include <string>

struct Command
{
    enum class OpType
    {
        A,
        C
    };

    OpType optype;
};

struct CommandA : public Command
{
    std::string value;
};

struct CommandC : public Command
{
    std::string dest;
    std::string comp;
    std::string jump;
};

#endif
