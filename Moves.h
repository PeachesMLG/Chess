#ifndef CHESS_MOVES_H
#define CHESS_MOVES_H

#include <vector>
#include "Board.h"

class Moves {
public:
    static void getPawnMoves(Item *item, std::vector<int> *moves, std::vector<Item> *board);
    static void getKnightMoves(Item *item, std::vector<int> *moves, std::vector<Item> *board);
    static void getKingMoves(Item *item, std::vector<int> *moves, std::vector<Item> *board);
    static void getBishopMoves(Item *item, std::vector<int> *moves, std::vector<Item> *board);
    static void getRookMoves(Item *item, std::vector<int> *moves, std::vector<Item> *board);
    static void getQueenMoves(Item *item, std::vector<int> *moves, std::vector<Item> *board);
};


#endif //CHESS_MOVES_H
