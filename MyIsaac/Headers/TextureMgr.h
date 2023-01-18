#pragma once
#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>

struct my_struct
{
    std::string Name;
    int x;
    int y;
    int SizeX;
    int SizeY;
    int OffSetY;
    int OffSetX;
    int SpriteNum;
    int SptitesOnLine;
    bool Reverted;
    bool RevertedX;
    bool RevertedY;
};

struct TextureInfo
{
    sf::Texture texture;
    std::map<std::string,my_struct>   myStruct;
};

class TextureMgr
{
    public:
        TextureMgr();
        ~TextureMgr();
        std::map<std::string,my_struct> parseAnimations(std::string path);
        std::map<std::string,my_struct> parse_basements(std::string path);

        sf::Texture& get_texture(std::string path);
        
        std::map<std::string,my_struct> map;

        static TextureMgr *pInstance;

        static TextureMgr* Instance();
    private:
    std::map<std::string,TextureInfo> textures;


};
