#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Instruction.h"
#include "Parse.h"
#include "SyntaxError.h"
#include "Translate.h"

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
            line.erase(line.find_last_not_of(" \n\r\t") + 1);
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

std::string get_file_name(const std::string& file_path)
{
    std::string file_full_name { file_path.substr(file_path.find_last_of('/') + 1) };
    std::string file_name { };

    std::string::size_type dot_index { file_full_name.find_last_of('.') };

    if (dot_index != std::string::npos
        && file_full_name.substr(dot_index + 1) == "asm")
    {
        file_name = file_full_name.substr(0, dot_index);
    }

    return file_name;
}

int main(int argc, char* argv[])
{
    std::cout << "Starting assembler!\n";

    // Handle file name argv
    if (argc != 2)
    {
        std::cerr << "Invalid number of arguments." << '\n';
        return 1;
    }

    std::string file_path { argv[1] };

    std::string file_name { get_file_name(file_path) };

    if (file_name == "")
    {
        std::cerr << "Invalid file name." << '\n';
        return 1;
    }

    // Get code lines from file
    std::vector<std::string> code_lines;

    try
    {
        code_lines = get_code_lines(file_path);
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << '\n';
        return 1;
    }

    try
    {
        std::vector<Instruction*> instructions { Parse::parse(code_lines) };
        Parse::delete_instructions(instructions);
    }
    catch (SyntaxError ex)
    {
        std::cerr << "SyntaxError: " << ex.what() << '\n';
        return 1;
    }

    // Save machine code to output file
    std::vector<std::string> parsed_lines { code_lines };

    try
    {
        save_code_lines(parsed_lines, "output/" + file_name + ".hack");
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << '\n';
        return 1;
    }

    return 0;
}
