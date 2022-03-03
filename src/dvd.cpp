#include "dvd.h"
#include "application.h"
#include "util.h"

DVD::DVD()
{
    // Texture setup
    m_dvdTex = new sf::Texture;
    m_dvdTex->loadFromFile("res/dvd.png");

    // Sprite setup
    m_sprite = new sf::Sprite(*m_dvdTex, sf::IntRect(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
    m_sprite->setTexture(*m_dvdTex);
    m_sprite->setPosition(WIDTH/2, HEIGHT/2);
    m_pos = m_sprite->getPosition();

    // Start the "ball" off in a random direction
    int xDir = Util::random(0, 1);
    int yDir = Util::random(0, 1);
    if(xDir == 0)
        m_speed.x = DEFAULT_SPEED;
    else
        m_speed.x = DEFAULT_SPEED*-1;
    if(yDir == 0)
        m_speed.y = DEFAULT_SPEED;
    else
        m_speed.y = DEFAULT_SPEED*-1;
}

void DVD::update()
{
    // Player 1 top collision
    if( m_pos.x <= g_player->pos.x+PLAYER_WIDTH && 
        m_pos.y <= g_player->pos.y+PLAYER_HEIGHT && 
        m_pos.y >= g_player->pos.y
    )
        m_speed.x = m_speed.x*-1;
    // Player 1 bottom collision
    else if( m_pos.x <= g_player->pos.x+PLAYER_WIDTH && 
        m_pos.y+SPRITE_HEIGHT <= g_player->pos.y+PLAYER_HEIGHT && 
        m_pos.y+SPRITE_HEIGHT >= g_player->pos.y
    )
        m_speed.x = m_speed.x*-1;

    // Player 2 top collision
    if( m_pos.x+SPRITE_WIDTH >= g_player2->pos.x &&
        m_pos.y <= g_player2->pos.y+PLAYER_HEIGHT && 
        m_pos.y >= g_player2->pos.y
    )
        m_speed.x = m_speed.x*-1;
    // Player 2 bottom collision
    else if( m_pos.x+SPRITE_WIDTH >= g_player2->pos.x &&
        m_pos.y+SPRITE_HEIGHT <= g_player2->pos.y+PLAYER_HEIGHT && 
        m_pos.y+SPRITE_HEIGHT >= g_player2->pos.y
    )
        m_speed.x = m_speed.x*-1;

    // Handle X wall collision
    m_pos.x += m_speed.x;
    if(m_pos.x >= WIDTH-SPRITE_WIDTH || m_pos.x <= 0) {
        m_speed.x = m_speed.x*-1;
        reset();
        return;
    }

    // Handle Y wall collision
    m_pos.y += m_speed.y;
    if(m_pos.y >= HEIGHT-SPRITE_HEIGHT || m_pos.y <= 0) {
        m_speed.y = m_speed.y*-1;
        if(m_speed.y < 8)
            m_speed.y *= 1.02f;
    }

    m_sprite->setPosition(sf::Vector2f(m_pos.x, m_pos.y));
}

void DVD::reset()
{
    // Add score and determine next movement direction
    if(m_pos.x <= 0) {
        g_player2->score++;
        m_speed.x = DEFAULT_SPEED;
    }
    else {
        g_player->score++;
        m_speed.x = DEFAULT_SPEED*-1;
    }

    // Recenter the sprite
    m_sprite->setPosition(WIDTH/2-SPRITE_WIDTH/2, HEIGHT/2-SPRITE_HEIGHT/2);
    m_pos = m_sprite->getPosition();

    // Get a random Y direction
    int yDir = Util::random(0, 1);
    if(yDir == 0)
        m_speed.y = DEFAULT_SPEED;
    else
        m_speed.y = DEFAULT_SPEED*-1;

    m_parent->gameOver();
}

void DVD::render(sf::RenderWindow* window)
{
    window->draw(*m_sprite);
}