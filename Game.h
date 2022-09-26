//
// Created by chris on 25/09/22.
//

#ifndef CHESS_GAME_H
#define CHESS_GAME_H


#include <string>

class Game {
public:
    Game(const std::string& fen);
    static int run();
};


#endif //CHESS_GAME_H
