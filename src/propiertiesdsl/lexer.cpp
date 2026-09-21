#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../../include/propiertiesdsl/lexer.hpp"

std::vector<Node> lex(std::string input) {
    std::stringstream ss(input);
    std::string line;
    std::vector<Node> propierties;

    while (std::getline(ss, line, '\n')) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) continue;

        size_t i = 0;
        std::string buf = "";
        
        while (i < line.length() && line[i] != '=') {
            buf += line[i];
            i++;
        }
        
        if (i >= line.length()) continue; 

        i++;
        if (i >= line.length()) continue;
        
        char type = line[i];
        i++;

        std::string vbuf = "";
        while (i < line.length()) {
            vbuf += line[i];
            i++;
        }

        Node n;
        n.key = buf;
        
        switch (type) {
            case '?': // Bool
                n.value = (vbuf == "t"); 
                break;
            case '#': // Int
                n.value = std::stoi(vbuf);
                break;
            case '.': // Float
                n.value = std::stof(vbuf);
                break;
            case '_': // String
                n.value = vbuf;
                break;
            default:
                break;
        }
        
        propierties.push_back(n);
    }
    return propierties;
}
