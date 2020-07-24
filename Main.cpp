#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Pipeset.h"
#include <list>
#include "NumberSystem.h"

void updateGround(sf::Sprite& ground, float ts, int& x, sf::Clock& c, std::list<Pipeset>& ps)
{
    if (ts >= 0.01f)
    {
        int amt = 1;
        x += amt;
        for (auto it = ps.begin(); it != ps.end(); it++)
        {
            it->OnUpdate(-amt);
        }
        x = x >= 555 ? 0 : x;
        c.restart();
        ground.setTextureRect(sf::IntRect(x, 0, 440, 112));
    }
}
bool collision(Player& pl, const Pipeset& ps, NumberSystem& nums)
{
    auto [topPos, bottomPos] = ps.getPipePositions();
    if (pl.getPosition().x >= topPos.x - 55)
        if (pl.getPosition().y <= topPos.y || pl.getPosition().y >= bottomPos.y)
        {
            pl.die();           
            return true;
        }
        else
            nums++;        
}
std::list<Pipeset>::iterator findNext(std::list<Pipeset>& ps, const sf::Vector2f& playerPos)
{
    if (!ps.empty())    
       for (auto it = ps.begin(); it != ps.end(); it++)
       {
           auto [top, bottom] = it->getPipePositions();
           if (playerPos.x <= top.x)                          
              return it;                            
       }    
    return std::list<Pipeset>::iterator();
}
void waitForStart(bool& s)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        s = true;
}
int main()
{
    sf::Vector2f screenSize(432.0f, 768.0f);
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y-70.0f), "Flappy Bird!");
    sf::RectangleShape mainbackground;
    sf::RectangleShape;
    sf::Texture backGroundTexture;
    sf::Texture groundTexture;
    sf::Texture pipeTexture;
    sf::Texture starttexture;
    sf::Texture overTexture;
    sf::Clock gameClock;
    sf::Clock pipeClock;
    sf::Clock birdClockFlight;
    sf::Clock birdClockGravity;
    sf::Clock birdJumpClock;
    sf::Clock deathClock;     
    backGroundTexture.loadFromFile("res/textures/background-day.png");
    groundTexture.loadFromFile("res/textures/BestBase.png");   
    mainbackground.setSize({ screenSize.x, screenSize.y });
    mainbackground.setPosition({ 0.0f, 0.0f });
    mainbackground.setTexture(&backGroundTexture);
    sf::Sprite ground;
    sf::Sprite startMessage;
    startMessage.setPosition({ 120.0f, 200.0f });
    starttexture.loadFromFile("res/textures/message.png");
    startMessage.setTexture(starttexture);
    Pipeset::init();
    ground.setPosition({ 0.0f, 590.0f });
    ground.setTexture(groundTexture);
    sf::Sprite gameOverMessage;
    overTexture.loadFromFile("res/textures/gameover.png");
    gameOverMessage.setTexture(overTexture);
    gameOverMessage.setPosition({ 120.0f, 200.0f });
    int sampleX = 0;
    ground.setTextureRect(sf::IntRect(sampleX, 0, 440, 112));
    std::list<Pipeset> pipes;
    const float groundLimit = 600.0f;
    const float gravity = 0.115f;
    const float jumpSpeed = 5.2f;
    float jumpTime = 0.0f;
    float movementOffsetDown = 0.0f;
    float movementOffsetUp   = 0.0f;
    float birdRotation = 340;
    Player::Get().setRotation(birdRotation);   
    NumberSystem numSystem;
    bool gameStart = false;
    bool gameOver = false;
    while (window.isOpen())
    {
        if (Player::Get().isDead())
            gameOver = true;
        if (!gameStart)
        {
            Player::Get().setRotation(birdRotation);
            gameStart = false;
            waitForStart(gameStart);           
        }
        float pipesTimeStep = pipeClock.getElapsedTime().asSeconds();
        if (pipesTimeStep >= 2.0f && !Player::Get().isDead() && gameStart)
        {
            Pipeset temp;
            pipes.push_back(temp);   
            if (pipes.size() >= 4)
                pipes.pop_front();
            pipeClock.restart();
        }          
        float birdTimeFlight  = birdClockFlight.getElapsedTime().asSeconds();
        float birdTimeGravity = birdClockGravity.getElapsedTime().asSeconds();        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && birdTimeFlight >= 0.01f && !Player::Get().isDead())
        {
            movementOffsetUp += jumpSpeed;
            Player::Get().moveUp(movementOffsetUp);
            movementOffsetUp = 0.0f;
            birdClockFlight.restart();
            birdJumpClock.restart();
            movementOffsetDown = 0.0f;             
            if (birdRotation >= 340)
                birdRotation -= 5;          
            Player::Get().setRotation(birdRotation);
        }        
        if (Player::Get().getPosition().y < groundLimit && birdTimeGravity >= 0.01f && gameStart)
        {
            movementOffsetDown += gravity;
            Player::Get().moveDown(movementOffsetDown);
            birdClockGravity.restart();
            jumpTime = birdJumpClock.getElapsedTime().asSeconds();
            if (birdRotation <= 450 && jumpTime >= 0.2f)
                birdRotation += 1.5f;               
            Player::Get().setRotation(birdRotation);            
        }
        if (Player::Get().getPosition().y >= groundLimit)
            movementOffsetDown = 0.0f;
        float deltaTime = gameClock.getElapsedTime().asSeconds();
        if(!Player::Get().isDead())
            updateGround(ground, deltaTime, sampleX, gameClock, pipes);
        sf::Event event;
        Player::Get().handleTextures();
        if (Player::Get().getPosition().y >= groundLimit)
            Player::Get().die();
        if (!pipes.empty())
        {
            auto next = findNext(pipes, Player::Get().getPosition());
            collision(Player::Get(), *next, numSystem);                
        }        
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;                
            }            
        }            
        window.clear();
        window.draw(mainbackground);
        for (auto it = pipes.begin(); it != pipes.end(); it++)
            it->draw(window);
        if (!gameStart)
            window.draw(startMessage);
        if (gameOver)
            window.draw(gameOverMessage);
        window.draw(ground);
        window.draw(Player::Get().Quad());   
        numSystem.display(window);
        window.display();
    }
}