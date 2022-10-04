#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H


#include <string>
#include <map>
#include <vector>

struct Vertex {
    int Position[3];
    float Color[4];
    float TextureCord[2];
    float TextureId;
};

struct Color {
    float r, g, b;
};

enum Player {
    White, Black
};
enum Piece {
    Rook, Bishop, Knight, Queen, King, Pawn
};

struct Item {
    Player player;
    Piece piece;
    int position;
};

class Board {
private:
    Player playerTurn;
    std::vector<Item> gameBoard;
public:
    Board();

    void drawBoard();
    void drawPieces();

    void dispose();

    void generateBoard(const std::string& fen);
};


#endif
