#include "command_parser.hpp"
#include <sstream>
#include <vector>
#include <string>

namespace parser {
    std::vector<std::string> parse_command(const std::string& command){
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(command);
        while(tokenStream >> token){
            tokens.push_back(token);
        }
        return tokens;
    }
}
