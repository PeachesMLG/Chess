#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Board.h"
#include "Texture.h"
#include <map>
#include <iostream>
#include <sstream>

Player playerTurn;
std::vector<Item> gameBoard;

std::map<char, Piece> pieces = {
        {'r', Rook,},
        {'b', Bishop,},
        {'n', Knight,},
        {'q', Queen,},
        {'k', King,},
        {'p', Pawn,}
};

void Board::generateFromFen(const std::string &fen) {
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
        gameBoard.emplace_back(pieces.find(tolower(character))->second, player, rank * 8 + file);
        file++;
    }
    playerTurn = tolower(fenData[1][0]) == 'w' ? White : Black;
}


void Board::drawPieces(GLFWwindow *window) {
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    int height = windowHeight / 8;
    int width = windowWidth / 8;

    for (Item item: gameBoard) {
        int file = item.position % 8;
        int rank = item.position / 8;
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2d(width * (file), height * (rank));
        glTexCoord2f(0, 1);
        glVertex2d(width * (file + 1), height * (rank));
        glTexCoord2f(1, 1);
        glVertex2d(width * (file + 1), height * (rank + 1));
        glTexCoord2f(1, 0);
        glVertex2d(width * (file), height * (rank + 1));
        glEnd();
    }
}

void Board::drawBoard(GLFWwindow *window) {
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    int height = windowHeight / 8;
    int width = windowWidth / 8;
    const struct {
        float r, g, b;
    } colors[] = {
            {0.463f, 0.588f, 0.337f},
            {0.933f, 0.933f, 0.824f},
    };
    for (int file = 0; file < 8; ++file) {
        for (int rank = 0; rank < 8; ++rank) {
            int color = (file + rank) % 2;
            glColor4f(colors[color].r, colors[color].g, colors[color].b, 1.f);
            glBegin(GL_QUADS);
            glVertex2d(width * (file), height * (rank));
            glVertex2d(width * (file + 1), height * (rank));
            glVertex2d(width * (file + 1), height * (rank + 1));
            glVertex2d(width * (file), height * (rank + 1));
            glEnd();
        }
    }
}
