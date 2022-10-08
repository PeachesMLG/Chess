#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H


#include <string>
#include <map>
#include <vector>
#include "Textures.h"
#include "Renderer.h"

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
    Renderer boardRenderer;
    Renderer piecesRenderer;
    void drawBoard();
    void drawPieces();

    float getTexture(Item item) {
        if (item.player == White && item.piece == Rook)return White_Rook;
        if (item.player == White && item.piece == Bishop)return White_Bishop;
        if (item.player == White && item.piece == Knight)return White_Knight;
        if (item.player == White && item.piece == Queen)return White_Queen;
        if (item.player == White && item.piece == King)return White_King;
        if (item.player == White && item.piece == Pawn)return White_Pawn;
        if (item.player == Black && item.piece == Rook)return Black_Rook;
        if (item.player == Black && item.piece == Bishop)return Black_Bishop;
        if (item.player == Black && item.piece == Knight)return Black_Knight;
        if (item.player == Black && item.piece == Queen)return Black_Queen;
        if (item.player == Black && item.piece == King)return Black_King;
        if (item.player == Black && item.piece == Pawn)return Black_Pawn;
        return -1;
    }
public:
    Player playerTurn;
    std::vector<Item> gameBoard;
    void initialise();
    void draw();
    void dispose();
    void generateBoard(const std::string &fen);
};


#endif
