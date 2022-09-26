#include <string>
#include <iostream>
#include "Game.h"

int main() {
    std::string position;
    std::cout << "Enter FEN Chess Notation! (Enter for Default Starting Position)" << std::endl;
//    std::getline(std::cin, position);
    if (position.empty())position = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::cout << "Starting Game..." << std::endl;
    Game game = Game(position);
    return game.run();
}