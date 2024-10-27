#include <iostream>
#include "game.h"

int main() {
    Game game;

    std::cout << "Initial Pieces:\n";
    game.displayPieces();

    game.playGame();

    return 0;
}
