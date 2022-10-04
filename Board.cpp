#include <vector>
#include "Board.h"
#include "Shader.h"
#include "Textures.h"


Color colors[] = {
        {0.463f, 0.588f, 0.337f},
        {0.933f, 0.933f, 0.824f},
};

std::map<char, Piece> pieces = {
        {'r', Rook,},
        {'b', Bishop,},
        {'n', Knight,},
        {'q', Queen,},
        {'k', King,},
        {'p', Pawn,}
};

unsigned int VBO, VAO, EBO;

Board::Board() {
    Vertex vertices[256];
    unsigned int indices[384];

    for (int i = 0; i < 64; ++i) {
        int file = i % 8;
        int rank = i / 8;
        Color color = colors[(file + rank) % 2];
        vertices[(i * 4) + 0] = {file + 0, rank + 0, 0, color.r, color.g, color.b, 1.0f, 1.0f, 1.0f, -1};
        vertices[(i * 4) + 1] = {file + 0, rank + 1, 0, color.r, color.g, color.b, 1.0f, 1.0f, 0.0f, -1};
        vertices[(i * 4) + 2] = {file + 1, rank + 1, 0, color.r, color.g, color.b, 1.0f, 0.0f, 0.0f, -1};
        vertices[(i * 4) + 3] = {file + 1, rank + 0, 0, color.r, color.g, color.b, 1.0f, 0.0f, 1.0f, -1};

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

void Board::drawPieces() {
    unsigned int PVBO, PVAO, PEBO;
    Vertex vertices[256];
    unsigned int indices[384];

    for (Item item : gameBoard) {
        int file = item.position % 8;
        int rank = item.position / 8;
        Color color = colors[(file + rank) % 2];
        float texture = getTexture(item);
        vertices[(item.position * 4) + 0] = {file + 0, rank + 0, 0, color.r, color.g, color.b, 1.0f, 0.0f, 1.0f, texture};
        vertices[(item.position * 4) + 1] = {file + 0, rank + 1, 0, color.r, color.g, color.b, 1.0f, 0.0f, 0.0f, texture};
        vertices[(item.position * 4) + 2] = {file + 1, rank + 1, 0, color.r, color.g, color.b, 1.0f, 1.0f, 0.0f, texture};
        vertices[(item.position * 4) + 3] = {file + 1, rank + 0, 0, color.r, color.g, color.b, 1.0f, 1.0f, 1.0f, texture};

        indices[(item.position * 6) + 0] = (item.position * 4) + 0;
        indices[(item.position * 6) + 1] = (item.position * 4) + 1;
        indices[(item.position * 6) + 2] = (item.position * 4) + 3;
        indices[(item.position * 6) + 3] = (item.position * 4) + 1;
        indices[(item.position * 6) + 4] = (item.position * 4) + 2;
        indices[(item.position * 6) + 5] = (item.position * 4) + 3;
    }
    glGenVertexArrays(1, &PVAO);
    glGenBuffers(1, &PVBO);
    glGenBuffers(1, &PEBO);

    glBindVertexArray(PVAO);

    glBindBuffer(GL_ARRAY_BUFFER, PVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, Color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TextureCord));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, TextureId));
    glEnableVertexAttribArray(3);

    glBindVertexArray(PVAO);
    glDrawElements(GL_TRIANGLES, 384, GL_UNSIGNED_INT, nullptr);
}

void Board::generateBoard(const std::string& fen) {
    std::cout << "Loading Position: " << fen << std::endl;
    std::stringstream stringStream(fen);
    std::vector<std::string> fenData;
    while (stringStream.good()) {
        std::string substr;
        getline(stringStream, substr, ' ');
        fenData.push_back(substr);
    }
    int file = 0;
    int rank = 7;
    for (char character: fenData[0]) {
        if (character == '/') {
            file = 0;
            rank--;
            continue;
        }
        if (std::isdigit(character)) {
            file += std::stoi(std::string(1, character));
            continue;
        }
        Player player = ((character >= 65) && (character <= 90)) ? White : Black;
        Item item = {player, pieces.find(tolower(character))->second, rank * 8 + file};
        gameBoard.emplace_back(item);
        file++;
    }
    playerTurn = tolower(fenData[1][0]) == 'w' ? White : Black;
}

void Board::dispose() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
