#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>

using namespace sf;

namespace vars {
    int range = 6;
    int dx = (rand() % range) - (range / 2);
    int dy = (rand() % range) - (range / 2);
    int horiz = 1280;
    int vert = 720;
    int frames = 0;
}

//Texture[0] = Target
//Texture[1] = Crosshair
Texture* createTextures() {
    Texture* textures = new Texture[2];
    textures[0] = Texture();
    textures[1] = Texture();
    if (!textures[0].loadFromFile("res/target.png")
            || !textures[1].loadFromFile("res/crosshair.png")) {
        return NULL;
    }
    textures[0].setSmooth(true);
    return textures;
}

//Sprite[0] = Target
//Sprite[1] = Crosshair
Sprite* createSprites(Texture* textures) {

    using namespace vars;

    Sprite* sprites = new Sprite[2];

    //TARGET sprites[0]
    sprites[0].setTexture(textures[0]);
    sprites[0].setOrigin(128.f, 128.f);
    sprites[0].setScale(.5, .5);
    sprites[0].setPosition(horiz / 2, vert / 2);
    
    //CROSSHAIR sprites[1]
    sprites[1].setTexture(textures[1]);
    return sprites;
}

void gameLoop(RenderWindow* window, Sprite* sprites) {
    
    using namespace vars;

    while (window->isOpen()) {
        
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();
                return;
            }
        }

        window->clear(sf::Color::Blue);
        Vector2f pos = sprites[0].getPosition();
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
        sprites[0].setPosition(pos.x + dx, pos.y + dy);
        window->draw(sprites[0]);
        window->display();
        frames++;
        
        usleep(16666);
    }
}

void cleanUp(Texture* textures, Sprite* sprites) {
    delete[] textures;
    delete[] sprites;
}

int main() {

    using namespace vars;

    //SETUP
    srand(time(NULL));
    RenderWindow* window = new RenderWindow(VideoMode(horiz, vert), "Joystick Trainer");
    Texture* textures = createTextures();
    Sprite* sprites = createSprites(textures);

    gameLoop(window, sprites);

    cleanUp(textures, sprites);

    return 0;
}