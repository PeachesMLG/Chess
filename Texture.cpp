#include <string>
#include <iostream>
#include "Texture.h"

Texture::Texture(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        std::cout << "Image could not be opened" << std::endl;
        return;
    }
    if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
        std::cout << "Not a correct bmp file" << std::endl;
        return;
    }
    if (header[0] != 'B' || header[1] != 'M') {
        std::cout << "Not a correct bmp file" << std::endl;
        return;
    }
    // Read ints from the byte array
    dataPos = *(int *) &(header[0x0A]);
    imageSize = *(int *) &(header[0x22]);
    width = *(int *) &(header[0x12]);
    height = *(int *) &(header[0x16]);


    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0) imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0) dataPos = 54; // The BMP header is done that way
    // Create a buffer
    data = new unsigned char[imageSize];

    // Read the actual data from the file into the buffer
    fread(data, 1, imageSize, file);

    //Everything is in memory now, the file can be closed
    fclose(file);

    // Create one OpenGL texture
    glGenTextures(1, &textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
