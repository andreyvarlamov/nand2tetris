#ifndef SYNTAXERROR_H
#define SYNTAXERROR_H

#include <exception>
#include <string>

class SyntaxError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

#endif
