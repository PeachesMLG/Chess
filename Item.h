#ifndef CHESS_ITEM_H
#define CHESS_ITEM_H

enum Player{White, Black};
enum Piece{Rook, Bishop, Knight, Queen, King, Pawn};

class Item {
public:
    Player player;
    Piece piece;
    int position;
    Item(Piece piece, Player player, int position) {
        this->piece = piece;
        this->player = player;
        this->position = position;
    }
};


#endif //CHESS_ITEM_H
