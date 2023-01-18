#include <SFML/Graphics.hpp>
#include <iostream>
#include "Headers/Assets/BasementAssets.h"
#include "Headers/GameDatas.h"
#include "Headers/Managers/InputManager.h"
#include "Headers/Assets/IsaacAssets.h"
#include "Headers/Assets/TearAssets.h"

int main()
{
    // Facto
    BasementAssets *basementAssets = new BasementAssets(GameDatas::Instance()->width,GameDatas::Instance()->height);
    basementAssets->LoadAssets();
    basementAssets->load_corner();
    
    IsaacAssets *isaacAssets = new IsaacAssets(GameDatas::Instance()->width,GameDatas::Instance()->height);
    isaacAssets->load_assets();

    new TearAssets(GameDatas::Instance()->width,GameDatas::Instance()->height);
    
    sf::RenderWindow window;
    window.create(sf::VideoMode(GameDatas::Instance()->width, GameDatas::Instance()->height), "Issac");

    // Utile ?  
    sf::RectangleShape background(sf::Vector2f(GameDatas::Instance()->width, GameDatas::Instance()->height));
    
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

            // Facto
            basementAssets->draw(window);
            isaacAssets->update(window);
            
            if ( GameDatas::Instance()->update(window) )
                break;
            
            window.display();
            InputManager::Instance()->Update();
        }
    }
    return 0;   
}