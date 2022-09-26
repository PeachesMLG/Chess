#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "stb_image.h"
#include "Board.h"
#include "Texture.h"

Board board;

Game::Game(const std::string &fen) {
    board.generateFromFen(fen);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int Game::run() {
    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1200, 1200, "Chess", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glMatrixMode(GL_PROJECTION);
    glEnable(GL_TEXTURE_2D);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        return -1;

    Texture texture = Texture("/home/chris/CLionProjects/Chess/Assets/wr.bmp");

    while (!glfwWindowShouldClose(window)) {
        int screenWidth, screenHeight;
        glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
        glLoadIdentity();
        glOrtho(0.0f, screenWidth, 0.0f, screenHeight, 0.0f, 1.0f);
        int height = screenHeight / 8;
        int width = screenWidth / 8;

        /* Render here */
//        board.drawBoard(window);
//        board.drawPieces(window);
        int file = 0;
        int rank = 0;
        glBindTexture(GL_TEXTURE_2D, texture.textureID);
        glActiveTexture(GL_TEXTURE0);
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

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
