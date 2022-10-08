#include "Shader.h"
#include "Renderer.h"

void Renderer::initialise() {
    for (int position = 0; position < 64; ++position) {
        indices[(position * 6) + 0] = (position * 4) + 0;
        indices[(position * 6) + 1] = (position * 4) + 1;
        indices[(position * 6) + 2] = (position * 4) + 3;
        indices[(position * 6) + 3] = (position * 4) + 1;
        indices[(position * 6) + 4] = (position * 4) + 2;
        indices[(position * 6) + 5] = (position * 4) + 3;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), nullptr, GL_DYNAMIC_DRAW);

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


void Renderer::clear() {
    for (auto & vertex : vertices) {
        vertex = {};
    }
}

void Renderer::render(int position, Color color, float TextureId) {
    int file = position % 8;
    int rank = position / 8;

    vertices[(position * 4) + 0] = {file + 0, rank + 0, 0, color.r, color.g, color.b, 1.0f, 0.0f, 1.0f, TextureId};
    vertices[(position * 4) + 1] = {file + 0, rank + 1, 0, color.r, color.g, color.b, 1.0f, 0.0f, 0.0f, TextureId};
    vertices[(position * 4) + 2] = {file + 1, rank + 1, 0, color.r, color.g, color.b, 1.0f, 1.0f, 0.0f, TextureId};
    vertices[(position * 4) + 3] = {file + 1, rank + 0, 0, color.r, color.g, color.b, 1.0f, 1.0f, 1.0f, TextureId};
}

void Renderer::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 384, GL_UNSIGNED_INT, nullptr);
}

void Renderer::dispose() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
