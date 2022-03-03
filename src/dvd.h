#pragma once

#include <SFML/Graphics.hpp>
#include "application.h"

#define SPRITE_WIDTH 100
#define SPRITE_HEIGHT 50
#define DEFAULT_SPEED 5

class Application;

class DVD
{
public:
    DVD();
    void update();
    void render(sf::RenderWindow* window);

    Player* g_player;
    Player* g_player2;
    Application* m_parent;
private:
    void reset();

    sf::Texture* m_dvdTex;
    sf::Sprite* m_sprite;
    sf::Vector2f m_pos;
    sf::Vector2f m_speed;
};