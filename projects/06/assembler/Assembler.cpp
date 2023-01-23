#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Parser.h"

std::vector<std::string> get_code_lines(const std::string& filename)
{
    std::ifstream file;
    file.open(filename);

    std::vector<std::string> code_lines { };

    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            code_lines.push_back(line);
        }

        file.close();
    }
    else
    {
        throw std::runtime_error("Failed to open file to read.");
    }

    return code_lines;
}

void save_code_lines(const std::vector<std::string>& code_lines,
        const std::string& filename)
{
    std::ofstream file;
    file.open(filename);
    if (file.is_open())
    {
        for (std::string line : code_lines)
        {
            file << line << '\n';
        }

        file.close();
    }
    else
    {
        throw std::runtime_error("Failed to open file to write.");
    }
}

int main()
{
    std::cout << "Starting assembler!\n";

    std::vector<std::string> code_lines;

    try
    {
        code_lines = get_code_lines("input/Add.asm");
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << '\n';
        return 1;
    }

    Parser parser { code_lines };
    std::vector<std::string> parsed_lines = parser.parse();

    try
    {
        save_code_lines(parsed_lines, "output/Add.hack");
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << '\n';
        return 1;
    }

    return 0;
}
