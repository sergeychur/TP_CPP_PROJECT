#include "Game.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(720, 440), "RTS");
    window.setVerticalSyncEnabled(true);

    Game game(window);
    game.start();

    return 0;
}