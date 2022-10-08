#ifndef CHESS_RENDERER_H
#define CHESS_RENDERER_H

#include "Textures.h"

struct Color {
    float r, g, b;
};

struct Vertex {
    int Position[3];
    float Color[4];
    float TextureCord[2];
    float TextureId;
};

class Renderer {
private:
    unsigned int VBO, VAO, EBO;
    Vertex vertices[256];
    unsigned int indices[384];
public:
    void initialise();
    void clear();
    void render(int position, Color color, float TextureId);
    void draw();
    void dispose();
};


#endif //CHESS_RENDERER_H
