#include <string>
#include <vector>

#include "CodeLine.h"

namespace FileIO
{
    std::vector<CodeLine> get_code_lines(const std::string& filename);
    void save_code_lines(const std::vector<std::string>& code_line,
        const std::string& filename);
}
