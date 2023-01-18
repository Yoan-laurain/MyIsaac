#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Headers/InputManager.h"
#include "Headers/TextureMgr.h"

float y;
float x;
float speed = 0.3f;
float ball_speed = 0.5f;
int height_window = 780;
int width_window = 1300;
sf::Sprite my_sprite;

std::vector<sf::Sprite> leftWalls;
std::vector<sf::Sprite> rightWalls;
std::vector<sf::Sprite> upWalls;
std::vector<sf::Sprite> downWalls;
std::vector<sf::Sprite> grounds;

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

enum actions
{
    Up,
    Down,
    Left,
    Right,
    Shoot,
    Exit,
};

actions currentAction;

int update()
{
    if(InputManager::Instance()->KeyDown(Up))
    {
        y = ( y < 156 + 26 ? 156 + 26 : y -= speed );
        currentAction = Up;
    }
    
    if(InputManager::Instance()->KeyDown(Down))
    {
        y = ( y  > height_window - 26 ? height_window - 26 : y += speed );
        currentAction = Down;
    }

    if(InputManager::Instance()->KeyDown(Left))
    {
        x = ( x < 156 + 26 ? 156 + 26 : x -= speed );
        currentAction = Left;
    }
    
    if(InputManager::Instance()->KeyDown(Right))
    {
        x = ( x  > width_window - 26 ? width_window - 26 : x += speed );
        currentAction = Right;
    }

    if (InputManager::Instance()->KeyDown(Exit))
    {
        InputManager::Instance()->Update();
        return true;
    }
    
    return false;
}

void bind_keys_actions()
{
    InputManager::Instance()->BindKey(Up, sf::Keyboard::Z);
    InputManager::Instance()->BindKey(Down, sf::Keyboard::S);
    InputManager::Instance()->BindKey(Left, sf::Keyboard::Q);
    InputManager::Instance()->BindKey(Right, sf::Keyboard::D);
    InputManager::Instance()->BindKey(Exit, sf::Keyboard::Escape);
    InputManager::Instance()->BindKey(Shoot, sf::Keyboard::Space);
}

void setup_window()
{
    sf::RectangleShape background(sf::Vector2f(width_window, height_window));

    x = width_window / 2;
    y = height_window / 2;
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
    if (InputManager::Instance()->KeyDown(Up) && InputManager::Instance()->KeyDown(Left))
        return up_left_direction;

    // if the player is pressing up and right
    if (InputManager::Instance()->KeyDown(Up) && InputManager::Instance()->KeyDown(Right))
        return up_right_direction;

    // if the player is pressing down and left
    if (InputManager::Instance()->KeyDown(Down) && InputManager::Instance()->KeyDown(Left))
        return down_left_direction;

    // if the player is pressing down and right
    if (InputManager::Instance()->KeyDown(Down) && InputManager::Instance()->KeyDown(Right))
        return down_right_direction;

    // if the player is pressing up
    if (InputManager::Instance()->KeyDown(Up))
        return up_direction;

    // if the player is pressing down
    if (InputManager::Instance()->KeyDown(Down))
        return down_direction;

    // if the player is pressing left
    if (InputManager::Instance()->KeyDown(Left))
        return left_direction;
    
    return right_direction;
}

std::vector<sf::Sprite*> loadAnimations()
{
    std::vector<sf::Sprite*> animationsSprite;

    TextureMgr texture_mgr = TextureMgr();
    texture_mgr.parseAnimations("../MyIsaac/Ressources/IsaacSprite");

    sf::Texture& FullIssac = texture_mgr.get_texture("../MyIsaac/Ressources/IsaacSprite.png");
    sf::Sprite* sprite = new sf::Sprite(FullIssac);

    std::vector<std::string> animations = {"Head_Up","Head_Right","Head_Down","Head_Left","Body_Vertical","Body_Right","Body_Left"};

    for ( int i = 0 ; i < 7 ; i++ )
    {
        my_struct texture = texture_mgr.map[animations[i]];
    
        sprite->setTextureRect(sf::IntRect(texture.x, texture.y, texture.SizeX, texture.SizeY));
        animationsSprite.emplace_back(sprite);
    }

    return animationsSprite;
}

int WhichAnimations(bool head = true)
{
    if ( head)
    {
        switch (currentAction)
        {
            case Up:
                return 0;
            case Right:
                return 1;
            case Down:
                return 2;
            case Left:
                return 3;
        }
    }
    else
    {
        switch (currentAction)
        {
            case Up:
                return 4;
            case Right:
                return 5;
            case Down:
                return 4;
            case Left:
                return 6;
        }
    }
}

int main()
{
    bind_keys_actions();
    
    sf::RenderWindow window;
    window.create(sf::VideoMode(width_window, height_window), "Issac");
    
    setup_window();

    // Texture manager with xml
    TextureMgr texture_mgr = TextureMgr();
    texture_mgr.parseAnimations("../MyIsaac/Ressources/IsaacSprite");
    texture_mgr.parse_basements("../MyIsaac/Ressources/Basement");

    // Load my image png
    sf::Texture FullIssac = texture_mgr.get_texture("../MyIsaac/Ressources/IsaacSprite.png");
    sf::Sprite spriteHead(FullIssac);
    sf::Sprite spriteBody(FullIssac);

    my_struct head = texture_mgr.map["Head_Down"];
    my_struct body = texture_mgr.map["Body_Vertical"];
    
    spriteHead.setTextureRect(sf::IntRect(head.x, head.y, head.SizeX, head.SizeY));
    spriteBody.setTextureRect(sf::IntRect(body.x, body.y, body.SizeX, body.SizeY));
    
    spriteHead.setScale(2.f, 2.f);
    spriteBody.setScale(2.f, 2.f);

    sf::Texture FullBasement = texture_mgr.get_texture("../MyIsaac/Ressources/Basement.png");
    
    sf::Sprite spriteCornerTopLeft(FullBasement);
    my_struct cornerTopLeft = texture_mgr.map["Corner_Top_Left"];
    spriteCornerTopLeft.setTextureRect(sf::IntRect(cornerTopLeft.x, cornerTopLeft.y, cornerTopLeft.SizeX, cornerTopLeft.SizeY));

    spriteCornerTopLeft.setScale(2.f, 2.f);
    spriteCornerTopLeft.setPosition(-cornerTopLeft.SizeX /2 , -cornerTopLeft.SizeY /2);

    //

    sf::Sprite spriteCornerTopRight(FullBasement);
    my_struct cornerTopRight = texture_mgr.map["Corner_Top_Right"];
    spriteCornerTopRight.setTextureRect(sf::IntRect(cornerTopRight.x, cornerTopRight.y, cornerTopRight.SizeX, cornerTopRight.SizeY));
    
    spriteCornerTopRight.setScale(-2.f, 2.f);

    spriteCornerTopRight.setPosition(width_window + cornerTopRight.SizeX / 2 , -cornerTopRight.SizeY / 2);

    //

    sf::Sprite spriteCornerBottomLeft(FullBasement);
    my_struct cornerBottomLeft = texture_mgr.map["Corner_Bottom_Left"];
    spriteCornerBottomLeft.setTextureRect(sf::IntRect(cornerBottomLeft.x, cornerBottomLeft.y, cornerBottomLeft.SizeX, cornerBottomLeft.SizeY));

    spriteCornerBottomLeft.setScale(2.f, -2.f);
    spriteCornerBottomLeft.setPosition(-cornerBottomLeft.SizeX / 2,height_window + cornerBottomLeft.SizeY / 2);

    // 

    sf::Sprite spriteCornerBottomRight(FullBasement);
    my_struct cornerBottomRight = texture_mgr.map["Corner_Bottom_Right"];
    spriteCornerBottomRight.setTextureRect(sf::IntRect(cornerBottomRight.x, cornerBottomRight.y, cornerBottomRight.SizeX, cornerBottomRight.SizeY));

    spriteCornerBottomRight.setScale(-2.f, -2.f);
    spriteCornerBottomRight.setPosition(width_window + cornerBottomRight.SizeX / 2,height_window + cornerBottomRight.SizeY / 2);
    
    sf::Sprite spriteBasement(FullBasement);

    std::vector<sf::Sprite*> animationsSprite = loadAnimations();
    
    for ( int i = 0; i < 13; i++)
    {
        if ( i % 2 == 0 )
        {
            my_struct wallLeft = texture_mgr.map["Wall_Classic_Left"];
            
            spriteBasement.setTextureRect(sf::IntRect(wallLeft.x, wallLeft.y, wallLeft.SizeX, wallLeft.SizeY));
            spriteBasement.setScale(2.f, 2.f);
            spriteBasement.setPosition(- 26, 104 * leftWalls.size()+1 - 26);
            
            leftWalls.push_back(spriteBasement);
        }
        else
        {
            my_struct wallRight = texture_mgr.map["Wall_Classic_Right"];
            
            spriteBasement.setTextureRect(sf::IntRect(wallRight.x, wallRight.y, wallRight.SizeX, wallRight.SizeY));
            spriteBasement.setScale(-2.f, 2.f);
            spriteBasement.setPosition(width_window + 26 , 104 * rightWalls.size()+1 + 78 );
            
            rightWalls.push_back(spriteBasement);
        }
    }

    for ( int i = 0; i < 23; i++)
    {
        if ( i % 2 == 0 )
        {
            my_struct wallUp = texture_mgr.map["Wall_Classic_Up"];
            
            spriteBasement.setTextureRect(sf::IntRect(wallUp.x, wallUp.y, wallUp.SizeX, wallUp.SizeY));
            spriteBasement.setScale(2.f, 2.f);
            spriteBasement.setPosition(104 * upWalls.size()+1 - 26, -26);
            
            upWalls.push_back(spriteBasement);
        }
        else
        {
            my_struct wall_down = texture_mgr.map["Wall_Classic_Down"];
            
            spriteBasement.setTextureRect(sf::IntRect(wall_down.x, wall_down.y, wall_down.SizeX, wall_down.SizeY));
            spriteBasement.setScale(2.f, -2.f);
            spriteBasement.setPosition(104 * downWalls.size()+1 + 78, height_window + 26);
            
            downWalls.push_back(spriteBasement);
        }
    }

    for ( int i = 1; i < 7; i++)
    {
        my_struct ground = texture_mgr.map["Ground_Line_Up"];
        
        spriteBasement.setTextureRect(sf::IntRect(ground.x, ground.y, ground.SizeX, ground.SizeY));
        spriteBasement.setScale(1144.f / 676, 2);
        spriteBasement.setPosition(78, i * 104 - 24);
        
        grounds.push_back(spriteBasement);
    }
    
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

            window.draw(spriteCornerTopLeft);
            window.draw(spriteCornerTopRight);
            window.draw(spriteCornerBottomLeft);
            window.draw(spriteCornerBottomRight);
            
            for (int i = 0; i < leftWalls.size(); i++)
            {
                window.draw(leftWalls[i]);
                if (i < rightWalls.size())
                    window.draw(rightWalls[i]);
            }
            
            for (int i = 0; i < upWalls.size(); i++)
            {
                window.draw(upWalls[i]);
                if ( i < downWalls.size() )
                    window.draw(downWalls[i]);
            }
            
            for (int i = 0; i < grounds.size(); i++)
                window.draw(grounds[i]);
            
            // window.draw(*animationsSprite[WhichAnimations(true)]);
            // window.draw(*animationsSprite[WhichAnimations(false)]);

            window.draw(spriteHead);
            window.draw(spriteBody);
            
            // Display player 
            spriteHead.setPosition(x, y);
            spriteBody.setPosition(x, y + head.SizeY * 1.2);

            // set the image at the center of the sprite
            spriteHead.setOrigin(head.SizeX / 2, head.SizeY / 2);
            spriteBody.setOrigin(body.SizeX / 2, body.SizeY / 2);
            
            window.draw(spriteHead);
            
            //Shoot
            if(InputManager::Instance()->KeyPress(Shoot))
            {
                ball new_ball = {x + 50, y +50, determine_which_direction()};
                
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