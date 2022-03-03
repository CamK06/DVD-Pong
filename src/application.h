#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "player.h"
#include "dvd.h"

#define WIDTH 1289
#define HEIGHT 727
#define NUM_SPRITES 1

class DVD;

class Application
{
public:
    Application();
    int run();
    void gameOver();

    sf::RenderWindow* m_window;
    
private:
    Player* m_player;
    Player* m_player2;
    DVD* m_dvd;
    std::vector<sf::RectangleShape*> m_dottedLine;
    sf::Font* m_comicSans;
    sf::Text* m_scoreText1;
    sf::Text* m_scoreText2;

    void update();
    void updateScore();
    void render();
    void handleEvents();
};