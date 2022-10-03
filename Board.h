#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H


struct Vertex {
    int Position[3];
    float Color[4];
    float TextureCord[2];
    float TextureId;
};

struct Color {
    float r, g, b;
};

class Board {
public:
    Board();
    void drawBoard();
    void dispose();
};


#endif
