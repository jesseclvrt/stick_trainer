#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>

int main() {
    //VARIABLES
    int range = 6;
    srand(time(NULL));
    int dx = (rand() % range) - (range / 2);
    int dy = (rand() % range) - (range / 2);
    int horiz = 1280;
    int vert = 720;
    int frames = 0;

    //SETUP
    sf::RenderWindow window(sf::VideoMode(horiz, vert), "Joystick Trainer");
    sf::Texture tarTex;
    sf::Texture crossTex;
    if (!tarTex.loadFromFile("res/target.png")
            || !crossTex.loadFromFile("res/crosshair.png")) {
        return 1;
    }
    tarTex.setSmooth(true);
    sf::Sprite tarSprite;
    tarSprite.setTexture(tarTex);
    tarSprite.setOrigin(128.f, 128.f);
    tarSprite.setScale(.5, .5);
    tarSprite.setPosition(horiz / 2, vert / 2);
    sf::Sprite crossSprite;
    crossSprite.setTexture(crossTex);

    //GAME LOOP
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear(sf::Color::Blue);
        sf::Vector2f pos = tarSprite.getPosition();
        if (frames > 150) {
            frames = 0;
            dx = (rand() % range) - (range / 2);
            dy = (rand() % range) - (range / 2);
        }
        if (pos.x > horiz) { // go left
            dx = (rand() % range) - range;
        } else if (pos.x < 0) {
            dx = rand() % range;
        }
        if (pos.y > vert) { // go up
            dy = (rand() % range) - range;
        } else if (pos.y < 0) {
            dy = rand() % range;
        }
        tarSprite.setPosition(pos.x + dx, pos.y + dy);
        window.draw(tarSprite);
        window.display();
        frames++;
        usleep(16666);
    }
    return 0;
}