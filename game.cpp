#include <iostream>
#include "game.h"

Player::Player(int id) : id(id), score(0),gameFinished(false) {}

void Player::playPiece(Piece* piece) {
    if (piece->playCount > 0) {
        piece->playCount--;
        score += 10;
    } else {
        std::cout << "Piece " << piece->id << " has no more plays left!\n";
    }
}

Piece::Piece(int id, int playCount, int rows, int cols)
    : id(id), playCount(playCount), rows(rows), cols(cols) {
    shape = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        shape[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            shape[i][j] = 0;
        }
    }
}

Piece::~Piece() {
    for (int i = 0; i < rows; ++i) {
        delete[] shape[i];
    }
    delete[] shape;
}

void Piece::rotate() {
    int** rotatedShape = new int*[cols];
    for (int i = 0; i < cols; ++i) {
        rotatedShape[i] = new int[rows];
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotatedShape[j][rows - i - 1] = shape[i][j];
        }
    }

    for (int i = 0; i < rows; ++i) {
        delete[] shape[i];
    }
    delete[] shape;

    shape = rotatedShape;
    std::swap(rows, cols);
}

Game::Game() {
    loadPieces();
    setupPlayers();
    choosePlayOrder();  // Ask the player if they want to go first or last

}

Game::~Game() {
    for (Piece* piece : pieces) {
        delete piece;
    }
    for (Player* player : players) {
        delete player;
    }
}

void Game::loadPieces() {
    Piece* piece1 = new Piece(1, 3, 2, 1);
    piece1->shape[0][0] = 1;
    piece1->shape[1][0] = 1;
    pieces.push_back(piece1);

    Piece* piece2 = new Piece(2, 3, 2, 2);
    piece2->shape[0][0] = 1;
    piece2->shape[0][1] = 1;
    piece2->shape[1][0] = 1;
    piece2->shape[1][1] = 1;
    pieces.push_back(piece2);

    Piece* piece3 = new Piece(3, 2, 3, 1);
    piece3->shape[0][0] = 1;
    piece3->shape[1][0] = 1;
    piece3->shape[2][0] = 1;
    pieces.push_back(piece3);
}

void Game::setupPlayers() {
    players.push_back(new Player(0));
    for (int i = 1; i <= 3; ++i) {
        players.push_back(new Player(i));
    }

    for (Player* player : players) {
        player->pieces = pieces;
    }
}

void Game::choosePlayOrder() {
    int choice;
    std::cout << "Do you want to play first or last? (1 for first, 2 for last): ";
    std::cin >> choice;

    if (choice == 1) {
        playerTurnOrder = {0, 1, 2, 3};  // You play first
    } else {
        playerTurnOrder = {1, 2, 3, 0};  // You play last
    }
}

void Game::displayPieces() {
    for (const Piece* piece : pieces) {
        std::cout << "Piece ID: " << piece->id << ", Play Count: " << piece->playCount << "\n";
        for (int i = 0; i < piece->rows; ++i) {
            for (int j = 0; j < piece->cols; ++j) {
                std::cout << piece->shape[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

void Game::playGame() {
    bool gameFinished=false;
    while (!gameFinished) {  // Example turn loop for 10 rounds
        for (int playerId : playerTurnOrder) {
            Player* player = players[playerId];
            std::cout << "Player " << player->id << "'s turn:\n";
            if (!player->pieces.empty()) {
                player->playPiece(player->pieces[0]);
            }
            std::cout << "Player " << player->id << " score: " << player->score << "\n";
        }
    }
}
