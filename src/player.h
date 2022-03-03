#pragma once

#include <SFML/Graphics.hpp>

#define MOVE_SPEED 5
#define PLAYER_WIDTH 25 
#define PLAYER_HEIGHT 100

class Player
{
public:
    Player(int xPos);
    void render(sf::RenderWindow* window);
    void update();

    int score = 0;
    sf::Vector2f pos;
    bool m_useArrows = false;
private:
    sf::RectangleShape* m_rect;
};