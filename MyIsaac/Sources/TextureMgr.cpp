#include "../Headers/TextureMgr.h"
#include <filesystem>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Utf.hpp>

#include "rapidxml/rapidxml_utils.hpp"

using namespace rapidxml;

TextureMgr *TextureMgr::pInstance = nullptr;

TextureMgr* TextureMgr::Instance()
{
    if (pInstance == nullptr)
        pInstance = new TextureMgr;

    return pInstance;
}


TextureMgr::TextureMgr(){}

TextureMgr::~TextureMgr(){}

std::map<std::string,my_struct> TextureMgr::parseAnimations(std::string path)
{
    if ( !std::filesystem::exists(path+".xml")  ) return std::map<std::string,my_struct>();
    if ( !std::filesystem::exists(path+".png") ) return std::map<std::string,my_struct>(); 
    
    xml_document<> doc;
    xml_node<> * root_node;

    file<> theFile((path + ".xml").c_str());
    doc.parse<0>(theFile.data());

    root_node = doc.first_node("Animations");

    for (xml_node<> * anim_node = root_node->first_node("Animation"); anim_node; anim_node = anim_node->next_sibling())
    {
        my_struct temp;
        temp.Name = anim_node->first_attribute("Name")->value();
        
        temp.x = atoi(anim_node->first_node("X")->value());
        temp.y =  atoi(anim_node->first_node("Y")->value());
        temp.SizeX =  atoi(anim_node->first_node("SizeX")->value());
        temp.SizeY =  atoi(anim_node->first_node("SizeY")->value());
        temp.OffSetX =  atoi(anim_node->first_node("OffsetX")->value());
        temp.OffSetY =  atoi(anim_node->first_node("OffsetY")->value());
        temp.SpriteNum =  atoi(anim_node->first_node("SpriteNum")->value());
        temp.SptitesOnLine =  atoi(anim_node->first_node("SptitesOnLine")->value());
        temp.Reverted = atoi(anim_node->first_node("Reverted")->value());

        map[temp.Name] = temp;
    }

    sf::Texture texture;
    texture.loadFromFile(path+".png");

    TextureInfo info;
    info.texture = texture;
    info.myStruct = map;

    textures[path+ ".png"] = info;

    return map;
    
}

std::map<std::string, my_struct> TextureMgr::parse_basements(std::string path)
{
    if ( !std::filesystem::exists(path+".xml")  ) return std::map<std::string,my_struct>();
    if ( !std::filesystem::exists(path+".png") ) return std::map<std::string,my_struct>(); 
    
    xml_document<> doc;
    xml_node<> * root_node;

    file<> theFile((path + ".xml").c_str());
    doc.parse<0>(theFile.data());

    root_node = doc.first_node("Backgrounds");

    for (xml_node<> * anim_node = root_node->first_node("Tile"); anim_node; anim_node = anim_node->next_sibling())
    {
        my_struct temp;

        temp.Name = anim_node->first_attribute("Name")->value();
        temp.x = atoi(anim_node->first_node("X")->value());
        temp.y =  atoi(anim_node->first_node("Y")->value());
        temp.SizeX =  atoi(anim_node->first_node("SizeX")->value());
        temp.SizeY =  atoi(anim_node->first_node("SizeY")->value());
        temp.RevertedX = atoi(anim_node->first_node("RevertedX")->value());
        temp.RevertedY = atoi(anim_node->first_node("RevertedY")->value());

        map[temp.Name] = temp;
    }

    sf::Texture texture;
    texture.loadFromFile(path+".png");

    TextureInfo info;
    info.texture = texture;
    info.myStruct = map;

    textures[path+ ".png"] = info;

    return map;
}

sf::Texture& TextureMgr::get_texture(std::string path)
{
    return textures[path].texture;
}
