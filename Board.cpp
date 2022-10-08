#include <vector>
#include "Board.h"
#include "Shader.h"
#include "Renderer.h"
#include "Moves.h"
#include <algorithm>

Color colors[] = {
        {0.463f, 0.588f, 0.337f}, // Black
        {0.933f, 0.933f, 0.824f}, // White
        {0.73f,  0.79f,  0.16f}, // Black (Selected)
        {0.96f,  0.96f,  0.41f}, // White (Selected)
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
    std::vector<int> moves;
    Item *item = getItem(selectedPiece);
    getMoves(item, &moves);
    for (int i = 0; i < 64; ++i) {
        bool isMove = std::find(moves.begin(), moves.end(), i) != moves.end();
        bool isLastMove = lastMove.to == i || lastMove.from == i;
        int offset = selectedPiece == i || isMove || isLastMove ? 2 : 0;
        int file = i % 8;
        int rank = i / 8;
        boardRenderer.render(i, colors[offset + (file + rank) % 2], -1);
    }
    boardRenderer.draw();
}

void Board::drawPieces() {
    piecesRenderer.clear();
    for (Item item: gameBoard) {
        piecesRenderer.render(item.position, colors[0], getTexture(item));
    }
    piecesRenderer.draw();
}

void Board::draw() {
    drawBoard();
    drawPieces();
}

void Board::generateBoard(const std::string &fen) {
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


Item *Board::getItem(int position) {
    for (Item &item: gameBoard) {
        if (item.position == position) return &item;
    }
    return nullptr;
}

Item *Board::getItem(int file, int rank) {
    for (Item &item: gameBoard) {
        int itemFile = item.position % 8;
        int itemRank = item.position / 8;
        if (itemFile == file && itemRank == rank)return &item;
    }
    return nullptr;
}

void Board::getMoves(Item *item, std::vector<int> *moves) {
    if (item == nullptr)return;
    if (item->piece == Pawn) Moves::getPawnMoves(item, moves, this);
    if (item->piece == Knight) Moves::getKnightMoves(item, moves, this);
    if (item->piece == King) Moves::getKingMoves(item, moves, this);
    if (item->piece == Bishop) Moves::getBishopMoves(item, moves, this);
    if (item->piece == Rook) Moves::getRookMoves(item, moves, this);
    if (item->piece == Queen) Moves::getQueenMoves(item, moves, this);
}

bool Board::move(Move move) {
    std::vector<int> moves;
    getMoves(getItem(move.from), &moves);
    if (std::find(moves.begin(), moves.end(), move.to) == moves.end()) return false;
    std::erase_if(gameBoard, [&](const Item &item) {
        return item.position == move.to;
    });
    getItem(move.from)->position = move.to;
    lastMove = move;
    playerTurn = playerTurn == White ? Black : White;
    return true;
}
