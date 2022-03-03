#include "player.h"
#include "application.h"

Player::Player(int xPos = 10)
{
    m_rect = new sf::RectangleShape();
    m_rect->setFillColor(sf::Color::White);
    m_rect->setPosition(sf::Vector2f(10, HEIGHT/2));
    m_rect->setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));

    pos.x = xPos;
    pos.y = HEIGHT/2;
}

void Player::render(sf::RenderWindow* window)
{
    window->draw(*m_rect);
}

void Player::update()
{
    // Handle movement
    if(!m_useArrows) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if(pos.y < HEIGHT-100)
                pos.y += MOVE_SPEED;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if(pos.y > 0)
                pos.y -= MOVE_SPEED;
        }
    }
    else {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if(pos.y < HEIGHT-100)
                pos.y += MOVE_SPEED;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if(pos.y > 0)
                pos.y -= MOVE_SPEED;
        }
    }
    m_rect->setPosition(pos);
}