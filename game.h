#ifndef GAME_H
#define GAME_H

#include <vector>

class Piece;

class Player {
public:
    int id;
    int score;
    bool gameFinished;
    std::vector<Piece*> pieces;

    Player(int id);
    void playPiece(Piece* piece);
};

class Piece {
public:
    int id;
    int playCount;
    int rows, cols;
    int** shape;

    Piece(int id, int playCount, int rows, int cols);
    ~Piece();
    void rotate();
};

class Game {
private:
    std::vector<Piece*> pieces;
    std::vector<Player*> players;
    std::vector<int> playerTurnOrder;  // Sequence of player IDs for the turn order

public:
    Game();
    ~Game();

    void loadPieces();
    void setupPlayers();
    void choosePlayOrder();    // New method to choose play order
    void playGame();
    void displayPieces();
};

#endif
