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
    auto* basement_assets = new BasementAssets(GameDatas::Instance()->width,GameDatas::Instance()->height);
    basement_assets->LoadAssets();
    basement_assets->load_corner();

    auto* isaac_assets = new IsaacAssets(GameDatas::Instance()->width,GameDatas::Instance()->height);
    isaac_assets->load_assets();

    new TearAssets(GameDatas::Instance()->width,GameDatas::Instance()->height);
    
    sf::RenderWindow window;
    window.create(sf::VideoMode(static_cast<unsigned>(GameDatas::Instance()->width), static_cast<int>(GameDatas::Instance()->height)), "Issac");
    
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
            basement_assets->draw(window);
            isaac_assets->update(window);
            
            if ( GameDatas::Instance()->update(window) )
                break;
            
            window.display();
            InputManager::Instance()->Update();
        }
    }
    return 0;   
}