#ifndef CHESS_TEXTURES_H
#define CHESS_TEXTURES_H

enum TextureTypes {
    White_Rook,
    White_Bishop,
    White_Knight,
    White_Queen,
    White_King,
    White_Pawn,
    Black_Rook,
    Black_Bishop,
    Black_Knight,
    Black_Queen,
    Black_King,
    Black_Pawn,
};

class Textures {
public:
    static void initialise();
};


#endif //CHESS_TEXTURES_H
