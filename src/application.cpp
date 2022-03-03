#include "application.h"
#include "util.h"
#include "player.h"

#include <chrono>
#include <thread>

int xPos = 0;
int yPos = 0;
int xSpeed = DEFAULT_SPEED;
int ySpeed = DEFAULT_SPEED;

Application::Application()
{
    // Window setup
    m_window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "DVD Pong");
    m_window->setFramerateLimit(60);

    // Game setup
    m_player = new Player(10);
    m_player2 = new Player(WIDTH-10-PLAYER_WIDTH);
    m_player2->m_useArrows = true;
    m_dvd = new DVD;
    m_dvd->g_player = m_player;
    m_dvd->g_player2 = m_player2;
    m_dvd->m_parent = this;

    // Graphics setup
    for(int i = 0; i < 50; i++) {
        sf::RectangleShape* m_rect = new sf::RectangleShape;
        m_rect->setSize(sf::Vector2f(12.5f, 50));
        m_rect->setFillColor(sf::Color(128, 128, 128));
        m_rect->setPosition(sf::Vector2f(WIDTH/2-3.125f, i*130+12.5f));
        m_dottedLine.push_back(m_rect);
    }
    m_comicSans = new sf::Font;
    m_comicSans->loadFromFile("res/ComicSans.ttf");
    m_scoreText1 = new sf::Text;
    m_scoreText1->setFont(*m_comicSans);
    m_scoreText1->setString("0");
    m_scoreText1->setCharacterSize(96);
    m_scoreText1->setFillColor(sf::Color::White);
    m_scoreText1->setPosition(WIDTH/2-96, 32);
    m_scoreText2 = new sf::Text;
    m_scoreText2->setFont(*m_comicSans);
    m_scoreText2->setString("0");
    m_scoreText2->setCharacterSize(96);
    m_scoreText2->setFillColor(sf::Color::White);
    m_scoreText2->setPosition(WIDTH/2-96, 32);
    updateScore();
}

int Application::run()
{
    while(m_window->isOpen()) {
        handleEvents();
        update();
        render();
    }
    return 0;
}

void Application::update()
{
    // Update game objects
    m_dvd->update();
    m_player->update();
    m_player2->update();
}

void Application::render()
{
    m_window->clear(sf::Color::Black);
    m_window->draw(*m_scoreText1);
    m_window->draw(*m_scoreText2);
    m_player->render(m_window);
    m_player2->render(m_window);
    for(int i = 0; i < m_dottedLine.size(); i++)
        m_window->draw(*m_dottedLine[i]);
    m_dvd->render(m_window);
    m_window->display();
}

void Application::gameOver()
{
    // This code isn't great but it works
    updateScore();
    for(int i = 0; i < 3; i++) {
        m_scoreText1->setFillColor(sf::Color::White);
        m_scoreText2->setFillColor(sf::Color::White);
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        m_scoreText1->setFillColor(sf::Color::Black);
        m_scoreText2->setFillColor(sf::Color::Black);
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    m_scoreText1->setFillColor(sf::Color::White);
    m_scoreText2->setFillColor(sf::Color::White);
    render();
}

void Application::handleEvents()
{
    sf::Event event;
    while(m_window->pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            m_window->close();
        if(event.type == sf::Event::KeyPressed)
            if(event.key.code == sf::Keyboard::Escape)
                m_window->close();
    }
}

void Application::updateScore()
{
    m_scoreText1->setString(std::to_string(m_player->score));
    m_scoreText2->setString(std::to_string(m_player2->score));
    sf::FloatRect textSize = m_scoreText1->getLocalBounds();
    m_scoreText1->setOrigin(textSize.left + textSize.width/2.0f, textSize.top + textSize.height/2.0f);
    m_scoreText1->setPosition(WIDTH/2-64, 64);
    textSize = m_scoreText2->getLocalBounds();
    m_scoreText2->setOrigin(textSize.left + textSize.width/2.0f, textSize.top + textSize.height/2.0f);
    m_scoreText2->setPosition(WIDTH/2+64, 64);
}