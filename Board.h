#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H


#include <string>
#include <map>
#include <vector>
#include "Textures.h"
#include "Renderer.h"
#include <optional>

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

struct Move {
    int to;
    int from;
};

class Board {
private:
    Renderer boardRenderer;
    Renderer piecesRenderer;
    Move lastMove = {-1, -1};

    void drawBoard();

    void drawPieces();

    static int getKing(Player player, std::vector<Item> *board);

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
    int selectedPiece = -1;

    void initialise();

    void draw();

    void dispose();

    void generateBoard(const std::string &fen);

    static Item *getItem(int position, std::vector<Item> *board);

    static Item *getItem(int file, int rank, std::vector<Item> *board);

    static std::vector<int> getMoves(Item *item, std::vector<Item> *board, bool legalMoves);

    static std::vector<Move> getPlayerMoves(Player player, std::vector<Item> *board);

    bool move(Move move);

    static bool resultsInCheck(Move move, std::vector<Item> board, Player player);

    static bool isInCheck(std::vector<Item> *board, Player player);
};


#endif
