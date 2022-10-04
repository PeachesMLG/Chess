#include <glad/glad.h>
#include <iostream>

#include "Textures.h"
#include "dependencies/stb/stb_image.h"


void generateTexture(char const *path, int textureUnit) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glBindTextureUnit(textureUnit, texture);
}

void Textures::initialise() {
    generateTexture("/home/chris/CLionProjects/Chess/assets/wr.png", 0);
    generateTexture("/home/chris/CLionProjects/Chess/assets/wb.png", 1);
    generateTexture("/home/chris/CLionProjects/Chess/assets/wn.png", 2);
    generateTexture("/home/chris/CLionProjects/Chess/assets/wq.png", 3);
    generateTexture("/home/chris/CLionProjects/Chess/assets/wk.png", 4);
    generateTexture("/home/chris/CLionProjects/Chess/assets/wp.png", 5);

    generateTexture("/home/chris/CLionProjects/Chess/assets/br.png", 6);
    generateTexture("/home/chris/CLionProjects/Chess/assets/bb.png", 7);
    generateTexture("/home/chris/CLionProjects/Chess/assets/bn.png", 8);
    generateTexture("/home/chris/CLionProjects/Chess/assets/bq.png", 9);
    generateTexture("/home/chris/CLionProjects/Chess/assets/bk.png", 10);
    generateTexture("/home/chris/CLionProjects/Chess/assets/bp.png", 11);
}
