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
            if (code_line.code.find("//") == 0)
            {
                continue;
            }

            // Skip empty lines
            if (code_line.code.empty() || code_line.code.find_first_not_of(' ') == std::string::npos)
            {
                continue;
            }

            // Remove comments from code lines
            std::string resultant_line { code_line.code };

            resultant_line = resultant_line.substr(0, resultant_line.find("//"));

            resultant_line.erase(remove_if(resultant_line.begin(), resultant_line.end(),
                                      [](unsigned char c){ return std::isspace(c); }
                                     ), resultant_line.end());

            preprocessed_lines.push_back(CodeLine { code_line.line, resultant_line });
        }

        return preprocessed_lines;
    }
}
