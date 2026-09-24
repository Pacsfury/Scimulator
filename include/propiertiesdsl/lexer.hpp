#pragma once
#include <string>
#include <variant>
#include <vector>

struct Node {
    std::string key;
    std::variant<int, bool, float, std::string> value;
};

std::vector<Node> lex(std::string input);