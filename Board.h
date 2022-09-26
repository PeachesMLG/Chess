#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H


#include <string>
#include <vector>
#include "Item.h"
#include "GLFW/glfw3.h"

class Board {
public:
    std::vector<Item> gameBoard;
    Player playerTurn;
    void generateFromFen(const std::string& fen);
    void drawBoard(GLFWwindow *window);
    void drawPieces(GLFWwindow *window);
};


#endif //CHESS_BOARD_H
