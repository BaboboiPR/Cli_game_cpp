#include <iostream>
#include "game.cpp"
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    using namespace std;

    gameloop game;
    game.game_loop();


    return 0;
}
