#include "Board.h"
#include "Shader.h"


Color colors[] = {
        {0.463f, 0.588f, 0.337f},
        {0.933f, 0.933f, 0.824f},
};

unsigned int VBO, VAO, EBO;

Board::Board() {
    Vertex vertices[256];
    unsigned int indices[384];

    for (int i = 0; i < 64; ++i) {
        int file = i % 8;
        int rank = i / 8;
        Color color = colors[(file + rank) % 2];
        vertices[(i * 4) + 0] = {file + 0, rank + 0, 0, color.r, color.g, color.b, 1.0f, 1.0f, 1.0f, -1.0f};
        vertices[(i * 4) + 1] = {file + 0, rank + 1, 0, color.r, color.g, color.b, 1.0f, 1.0f, 0.0f, -1.0f};
        vertices[(i * 4) + 2] = {file + 1, rank + 1, 0, color.r, color.g, color.b, 1.0f, 0.0f, 0.0f, -1.0f};
        vertices[(i * 4) + 3] = {file + 1, rank + 0, 0, color.r, color.g, color.b, 1.0f, 0.0f, 1.0f, -1.0f};

        indices[(i * 6) + 0] = (i * 4) + 0;
        indices[(i * 6) + 1] = (i * 4) + 1;
        indices[(i * 6) + 2] = (i * 4) + 3;
        indices[(i * 6) + 3] = (i * 4) + 1;
        indices[(i * 6) + 4] = (i * 4) + 2;
        indices[(i * 6) + 5] = (i * 4) + 3;
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TextureCord));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TextureId));
    glEnableVertexAttribArray(3);
}

void Board::drawBoard() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 384, GL_UNSIGNED_INT, nullptr);
}

void Board::dispose() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
