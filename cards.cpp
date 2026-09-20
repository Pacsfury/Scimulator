#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../include/cards.hpp"

static const inline std::vector<std::string> CARDS = {"COMMON.livesplusone", "SPECIAL.extrapoints", "MYTHIC.coinballs"};

std::vector<std::string> deck;

void addCard(std::string card) {
    if (deck.size() < 3) {
        deck.push_back(card);
    } else {
        deck.back() = card;
    }
}

bool hasCard(std::string name) { return std::find(deck.begin(), deck.end(), name) != deck.end(); }