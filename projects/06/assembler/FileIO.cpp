#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>

#include "CodeLine.h"
#include "FileIO.h"

namespace FileIO
{
    std::vector<CodeLine> get_code_lines(const std::string& filename)
    {
        std::ifstream file;
        file.open(filename);

        std::vector<CodeLine> code_lines { };

        if (file.is_open())
        {
            int index { };
            std::string line;
            while (getline(file, line))
            {
                line.erase(line.find_last_not_of(" \n\r\t") + 1);
                code_lines.push_back(CodeLine { index + 1, line });
                ++index;
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
}
