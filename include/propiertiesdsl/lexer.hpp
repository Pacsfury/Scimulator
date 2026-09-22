#pragma once
#include <string>
#include <vector>
#include <variant>

struct Node {
    std::string key;
    std::variant<int, bool, float, std::string> value;
};

std::vector<Node> lex(std::string input);