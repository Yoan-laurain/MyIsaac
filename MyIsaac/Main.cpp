#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Headers/BasementAssets.h"
#include "Headers/GameAssets.h"
#include "Headers/GameDatas.h"
#include "Headers/InputManager.h"
#include "Headers/IsaacAssets.h"

float speed = 0.3f;
float ball_speed = 0.5f;
int height_window = 780;
int width_window = 1300;
sf::Sprite my_sprite;

enum direction
{
    up_direction ,
    up_left_direction ,
    up_right_direction ,
    down_direction ,
    down_left_direction ,
    down_right_direction ,
    left_direction ,
    right_direction
};

struct ball
{
    float x;
    float y;
    direction direction;
};

std::vector<ball> balls;
std::vector<sf::CircleShape> shapes;


int update()
{
    if(InputManager::Instance()->KeyDown(GameDatas::Up))
    {
        GameDatas::Instance()->yPlayer = ( GameDatas::Instance()->yPlayer < 120  ? 120  : GameDatas::Instance()->yPlayer  -= speed );
        GameDatas::Instance()->currentAction = GameDatas::Up;
    }
    
    if(InputManager::Instance()->KeyDown(GameDatas::Down))
    {
        GameDatas::Instance()->yPlayer  = ( GameDatas::Instance()->yPlayer   > height_window - 120 ? height_window - 120 : GameDatas::Instance()->yPlayer  += speed );
        GameDatas::Instance()->currentAction = GameDatas::Down;
    }

    if(InputManager::Instance()->KeyDown(GameDatas::Left))
    {
        GameDatas::Instance()->xPlayer  = ( GameDatas::Instance()->xPlayer  < 120 ? 120 : GameDatas::Instance()->xPlayer  -= speed );
        GameDatas::Instance()->currentAction = GameDatas::Left;
    }
    
    if(InputManager::Instance()->KeyDown(GameDatas::Right))
    {
        GameDatas::Instance()->xPlayer  = ( GameDatas::Instance()->xPlayer   > width_window - 120 ? width_window - 120 : GameDatas::Instance()->xPlayer  += speed );
        GameDatas::Instance()->currentAction = GameDatas::Right;
    }

    if (InputManager::Instance()->KeyDown(GameDatas::Exit))
    {
        InputManager::Instance()->Update();
        return true;
    }
    
    return false;
}

void bind_keys_actions()
{
    InputManager::Instance()->BindKey(GameDatas::Up, sf::Keyboard::Z);
    InputManager::Instance()->BindKey(GameDatas::Down, sf::Keyboard::S);
    InputManager::Instance()->BindKey(GameDatas::Left, sf::Keyboard::Q);
    InputManager::Instance()->BindKey(GameDatas::Right, sf::Keyboard::D);
    InputManager::Instance()->BindKey(GameDatas::Exit, sf::Keyboard::Escape);
    InputManager::Instance()->BindKey(GameDatas::Shoot, sf::Keyboard::Space);
}

void setup_window()
{
    sf::RectangleShape background(sf::Vector2f(width_window, height_window));

    GameDatas::Instance()->xPlayer  = width_window / 2;
    GameDatas::Instance()->yPlayer  = height_window / 2;
}

void move_ball(ball* ball)
{
    switch (ball->direction)
    {
        case up_direction:
            ball->y -= ball_speed;
            break;
        case down_direction:
            ball->y += ball_speed;
            break;

        case up_left_direction:
            ball->y -= ball_speed;
            ball->x -= ball_speed;
            break;
        
        case up_right_direction:
            ball->y -= ball_speed;
            ball->x += ball_speed;
            break;
        
        case down_left_direction:
            ball->y += ball_speed;
            ball->x -= ball_speed;
            break;
        
        case down_right_direction:
            ball->y += ball_speed;
            ball->x += ball_speed;
            break;
        
        case left_direction:
            ball->x -= ball_speed;
            break;
        
        case right_direction:
            ball->x += ball_speed;
            break;
    }
}

direction determine_which_direction()
{
    // if the player is pressing up and left
    if (InputManager::Instance()->KeyDown(GameDatas::Up) && InputManager::Instance()->KeyDown(GameDatas::Left))
        return up_left_direction;

    // if the player is pressing up and right
    if (InputManager::Instance()->KeyDown(GameDatas::Up) && InputManager::Instance()->KeyDown(GameDatas::Right))
        return up_right_direction;

    // if the player is pressing down and left
    if (InputManager::Instance()->KeyDown(GameDatas::Down) && InputManager::Instance()->KeyDown(GameDatas::Left))
        return down_left_direction;

    // if the player is pressing down and right
    if (InputManager::Instance()->KeyDown(GameDatas::Down) && InputManager::Instance()->KeyDown(GameDatas::Right))
        return down_right_direction;

    // if the player is pressing up
    if (InputManager::Instance()->KeyDown(GameDatas::Up))
        return up_direction;

    // if the player is pressing down
    if (InputManager::Instance()->KeyDown(GameDatas::Down))
        return down_direction;

    // if the player is pressing left
    if (InputManager::Instance()->KeyDown(GameDatas::Left))
        return left_direction;
    
    return right_direction;
}

int main()
{
    bind_keys_actions();
    BasementAssets *basementAssets = new BasementAssets(width_window,height_window);
    basementAssets->LoadAssets();
    basementAssets->load_corner();
    
    IsaacAssets *isaacAssets = new IsaacAssets(width_window,height_window);
    isaacAssets->load_assets();
    
    sf::RenderWindow window;
    window.create(sf::VideoMode(width_window, height_window), "Issac");
    
    setup_window();
    
    while (window.isOpen())
    {
        sf::Event event{};
        
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        
        while(true)
        {
            sf::Event e{};
            
            if(window.pollEvent(e))
                InputManager::Instance()->KRUpdate(e);
    
            window.clear();
            
            basementAssets->draw(window);
            isaacAssets->update(window);
            
            //Shoot
            if(InputManager::Instance()->KeyPress(GameDatas::Shoot))
            {
                ball new_ball = {GameDatas::Instance()->xPlayer  + 50, GameDatas::Instance()->yPlayer  +50, determine_which_direction()};
                
                balls.push_back(new_ball);
                shapes.emplace_back(15.f);
            }
    
            // if there is a ball
            if (!balls.empty())
            {
                // Display ball
                for (auto& ball : balls)
                {
                    // Move ball depending on direction
                    move_ball(&ball);
    
                    sf::CircleShape& shape = shapes[&ball - balls.data()];
                    shape = sf::CircleShape(15.f);
                    shape.setFillColor(sf::Color::Green);
                    
                    shape.setPosition(ball.x, ball.y);
                    window.draw(shape);
                }
                
                // if ball is out of screen remove it
                if (balls[0].x > 1300)
                    balls.erase(balls.begin());
            }
            
            // Move
            if ( update() )
                break;
            
            window.display();
            InputManager::Instance()->Update();
        }
    }
    
    return 0;   
}