#include <algorithm>
#include <string>
#include <vector>

#include "CodeLine.h"
#include "Preprocess.h"

namespace Preprocess
{
    std::vector<CodeLine> preprocess(const std::vector<CodeLine>& code_lines)
    {
        std::vector<CodeLine> preprocessed_lines { };

        for (CodeLine code_line : code_lines)
        {
            // Skip comments
            if (code_line.code.rfind("//", 0) == 0)
            {
                continue;
            }

            // Skip empty lines
            if (code_line.code.empty() || code_line.code.find_first_not_of(' ') == std::string::npos)
            {
                continue;
            }

            std::string stripped_line { code_line.code };
            stripped_line.erase(remove_if(stripped_line.begin(), stripped_line.end(),
                                      [](unsigned char c){ return std::isspace(c); }
                                     ), stripped_line.end());

            preprocessed_lines.push_back(CodeLine { code_line.line, stripped_line });
        }

        return preprocessed_lines;
    }
}
