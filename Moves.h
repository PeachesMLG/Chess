#ifndef CHESS_MOVES_H
#define CHESS_MOVES_H

#include <vector>
#include "Board.h"

class Moves {
public:
    static void getPawnMoves(Item *item, std::vector<int> *moves, Board* board);
    static void getKnightMoves(Item *item, std::vector<int> *moves, Board* board);
    static void getKingMoves(Item *item, std::vector<int> *moves, Board* board);
    static void getBishopMoves(Item *item, std::vector<int> *moves, Board* board);
    static void getRookMoves(Item *item, std::vector<int> *moves, Board* board);
    static void getQueenMoves(Item *item, std::vector<int> *moves, Board* board);
};


#endif //CHESS_MOVES_H
