#ifndef CHESS_TEXTURE_H
#define CHESS_TEXTURE_H


#include "GL/glew.h"

class Texture {
private:
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
// Actual RGB data
    unsigned char * data;
public:
    GLuint textureID;
    Texture(const char *filepath);
};


#endif //CHESS_TEXTURE_H
