#include "Moves.h"

bool isEmpty(int file, int rank, std::vector<Item> *board) {
    if (file < 0 || file > 7) return false;
    if (rank < 0 || rank > 7) return false;
    Item *occupiedItem = Board::getItem(file, rank, board);
    return occupiedItem == nullptr;
}

bool isEnemy(Item *item, int file, int rank, std::vector<Item> *board) {
    if (file < 0 || file > 7) return false;
    if (rank < 0 || rank > 7) return false;
    Item *occupiedItem = Board::getItem(file, rank, board);
    return occupiedItem != nullptr && occupiedItem->player != item->player;
}

bool isEmptyOrEnemy(Item *item, int file, int rank, std::vector<Item> *board) {
    return isEmpty(file, rank, board) || isEnemy(item, file, rank, board);
}

int getPosition(int file, int rank) {
    return (rank * 8) + file;
}

void Moves::getPawnMoves(Item *item, std::vector<int> *moves, std::vector<Item> *board) {
    int file = item->position % 8;
    int rank = item->position / 8;

    bool isFirst = rank == (item->player == White ? 1 : 6);
    int direction = item->player == White ? 1 : -1;

    if (isEnemy(item, file - 1, rank + (1 * direction), board)) {
        moves->push_back(getPosition(file - 1, rank + (1 * direction)));
    }
    if (isEnemy(item, file + 1, rank + (1 * direction), board)) {
        moves->push_back(getPosition(file + 1, rank + (1 * direction)));
    }

    bool infront = isEmpty(file, rank + (1 * direction), board);
    bool twoInfront = isEmpty(file, rank + (2 * direction), board);
    if (infront) {
        moves->push_back(getPosition(file, rank + (1 * direction)));
    }
    if (isFirst && infront && twoInfront) {
        moves->push_back(getPosition(file, rank + (2 * direction)));
    }
}

void Moves::getKnightMoves(Item *item, std::vector<int> *moves, std::vector<Item> *board) {
    int file = item->position % 8;
    int rank = item->position / 8;
    if (isEmptyOrEnemy(item, file + 2, rank - 1, board))moves->push_back(getPosition(file + 2, rank - 1));
    if (isEmptyOrEnemy(item, file - 2, rank - 1, board))moves->push_back(getPosition(file - 2, rank - 1));
    if (isEmptyOrEnemy(item, file + 1, rank - 2, board))moves->push_back(getPosition(file + 1, rank - 2));
    if (isEmptyOrEnemy(item, file - 1, rank - 2, board))moves->push_back(getPosition(file - 1, rank - 2));
    if (isEmptyOrEnemy(item, file + 2, rank + 1, board))moves->push_back(getPosition(file + 2, rank + 1));
    if (isEmptyOrEnemy(item, file - 2, rank + 1, board))moves->push_back(getPosition(file - 2, rank + 1));
    if (isEmptyOrEnemy(item, file + 1, rank + 2, board))moves->push_back(getPosition(file + 1, rank + 2));
    if (isEmptyOrEnemy(item, file - 1, rank + 2, board))moves->push_back(getPosition(file - 1, rank + 2));
}

void Moves::getKingMoves(Item *item, std::vector<int> *moves, std::vector<Item> *board) {
    int file = item->position % 8;
    int rank = item->position / 8;
    if (isEmptyOrEnemy(item, file - 1, rank + 1, board))moves->push_back(getPosition(file - 1, rank + 1));
    if (isEmptyOrEnemy(item, file + 0, rank + 1, board))moves->push_back(getPosition(file + 0, rank + 1));
    if (isEmptyOrEnemy(item, file + 1, rank + 1, board))moves->push_back(getPosition(file + 1, rank + 1));
    if (isEmptyOrEnemy(item, file - 1, rank + 0, board))moves->push_back(getPosition(file - 1, rank + 0));
    if (isEmptyOrEnemy(item, file + 1, rank + 0, board))moves->push_back(getPosition(file + 1, rank + 0));
    if (isEmptyOrEnemy(item, file - 1, rank - 1, board))moves->push_back(getPosition(file - 1, rank - 1));
    if (isEmptyOrEnemy(item, file + 0, rank - 1, board))moves->push_back(getPosition(file + 0, rank - 1));
    if (isEmptyOrEnemy(item, file + 1, rank - 1, board))moves->push_back(getPosition(file + 1, rank - 1));
}

void Moves::getBishopMoves(Item *item, std::vector<int> *moves, std::vector<Item> *board) {
    int file = item->position % 8;
    int rank = item->position / 8;
    for (int i = 1; i <= 8; ++i) {
        if (!isEmptyOrEnemy(item, file + i, rank + i, board))break;
        moves->push_back(getPosition(file + i, rank + i));
        if (isEnemy(item, file + i, rank + i, board))break;
    }
    for (int i = 1; i <= 8; ++i) {
        if (!isEmptyOrEnemy(item, file - i, rank + i, board))break;
        moves->push_back(getPosition(file - i, rank + i));
        if (isEnemy(item, file - i, rank + i, board))break;
    }
    for (int i = 1; i <= 8; ++i) {
        if (!isEmptyOrEnemy(item, file + i, rank - i, board))break;
        moves->push_back(getPosition(file + i, rank - i));
        if (isEnemy(item, file + i, rank - i, board))break;
    }
    for (int i = 1; i <= 8; ++i) {
        if (!isEmptyOrEnemy(item, file - i, rank - i, board))break;
        moves->push_back(getPosition(file - i, rank - i));
        if (isEnemy(item, file - i, rank - i, board))break;
    }
}

void Moves::getRookMoves(Item *item, std::vector<int> *moves, std::vector<Item> *board) {
    int file = item->position % 8;
    int rank = item->position / 8;
    for (int i = 1; i <= 8; ++i) {
        if (!isEmptyOrEnemy(item, file, rank + i, board))break;
        moves->push_back(getPosition(file, rank + i));
        if (isEnemy(item, file, rank + i, board))break;
    }
    for (int i = 1; i <= 8; ++i) {
        if (!isEmptyOrEnemy(item, file, rank - i, board))break;
        moves->push_back(getPosition(file, rank - i));
        if (isEnemy(item, file, rank - i, board))break;
    }
    for (int i = 1; i <= 8; ++i) {
        if (!isEmptyOrEnemy(item, file + i, rank, board))break;
        moves->push_back(getPosition(file + i, rank));
        if (isEnemy(item, file + i, rank, board))break;
    }
    for (int i = 1; i <= 8; ++i) {
        if (!isEmptyOrEnemy(item, file - i, rank, board))break;
        moves->push_back(getPosition(file - i, rank));
        if (isEnemy(item, file - i, rank, board))break;
    }
}

void Moves::getQueenMoves(Item *item, std::vector<int> *moves, std::vector<Item> *board) {
    getBishopMoves(item, moves, board);
    getRookMoves(item, moves, board);
}
