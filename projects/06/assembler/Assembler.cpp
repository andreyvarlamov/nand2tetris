#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "CodeLine.h"
#include "FileIO.h"
#include "Instruction.h"
#include "Parse.h"
#include "Preprocess.h"
#include "SymbolProcessor.h"
#include "SyntaxError.h"
#include "Translate.h"

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
    std::vector<CodeLine> code_lines;

    try
    {
        code_lines = FileIO::get_code_lines(file_path);
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << '\n';
        return 1;
    }

    std::vector<std::string> translated_lines { };

    try
    {
        std::vector<CodeLine> preprocessed_lines { Preprocess::preprocess(code_lines) };
        SymbolProcessor symbolProcessor { };
        std::vector<CodeLine> no_symbols_lines { symbolProcessor.process_symbols(preprocessed_lines) };
//        std::vector<Instruction*> instructions { Parse::parse(no_symbols_lines) };
//        translated_lines = Translate::translate(instructions);
//        Parse::delete_instructions(instructions);
    }
    catch (SyntaxError ex)
    {
        std::cerr << "\n\nSyntaxError: " << ex.what() << "\n\n";
        return 1;
    }

    try
    {
        FileIO::save_code_lines(translated_lines, "output/" + file_name + ".hack");
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << '\n';
        return 1;
    }

    return 0;
}
