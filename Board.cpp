#include <vector>
#include "Board.h"
#include "Shader.h"
#include "Renderer.h"

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

void Board::initialise() {
    boardRenderer.initialise();
    piecesRenderer.initialise();
}

void Board::drawBoard() {
    boardRenderer.clear();
    for (int i = 0; i < 64; ++i) {
        int file = i % 8;
        int rank = i / 8;
        boardRenderer.render(i, colors[(file + rank) % 2], -1);
    }
    boardRenderer.draw();
}

void Board::drawPieces() {
    piecesRenderer.clear();
    for (Item item : gameBoard) {
        piecesRenderer.render(item.position, colors[0], getTexture(item));
    }
    piecesRenderer.draw();
}

void Board::draw(){
    drawBoard();
    drawPieces();
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
    boardRenderer.dispose();
    piecesRenderer.dispose();
}
