#ifndef SPRITE_XML_HPP_
# define SPRITE_XML_HPP_

#include <iostream>
#include <unordered_map>

#include "Nexus/modules/environment/Environment.hpp"
#include "Nexus/modules/xml/rapidxml-1.13/rapidxml.hpp"

#include "Nexus/modules/xml/Gui/GuiElement.hpp"

using namespace rapidxml;

namespace nx{
namespace xml{
    
    class Sprite{
    public:
        static void init(std::unordered_map<std::string, std::function<std::string(env::Environment&, const GameInfosParser& gameInfosParser, env::GUISpriteInfos&, const std::string& tag, const std::string& value)>>& autorizedAtt){
            autorizedAtt = std::unordered_map<std::string, std::function<std::string(env::Environment&, const GameInfosParser& gameInfosParser, env::GUISpriteInfos&, const std::string& tag, const std::string& value)>>({
                {"spritesheetPath", &fillSpritesheetPath},
                {"sheetGrid", &fillSheetGrid},
                {"spriteSize", &fillSpriteSize}
            });
        }

        static std::string fillSprite(env::Environment& env, const GameInfosParser& gameInfosParser, env::Layer& layer, xml_node<>* rootNode){
            std::string error = "";
            std::unordered_map<std::string, std::string> attributes;

            if ((error += Util::getAttributes(rootNode->name(), rootNode, attributes)).empty()){
                env::gui::Sprite sprite;
                std::string name = attributes.at("name");

                error += GuiElement::fillGuiElementInfos(env, gameInfosParser, sprite.getGuiElementInfos(), attributes, false);
                error += fillSpriteInfo(env, gameInfosParser, sprite.getGuiSpriteInfos(), attributes, name);
                layer.addSprite(sprite);
            }
            return error;
        }

        static std::string fillSpriteInfo(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUISpriteInfos& guiSpriteInfos, std::unordered_map<std::string, std::string>& attributes, const std::string& name){
            std::string error = "";
            std::unordered_map<std::string, std::function<std::string(env::Environment&, const GameInfosParser& gameInfosParser, env::GUISpriteInfos&, const std::string& tag, const std::string& value)>> autorizedAtt;

            init(autorizedAtt);
            for (auto attribute : attributes){
                if (autorizedAtt.find(attribute.first) != autorizedAtt.end())
                    autorizedAtt.at(attribute.first)(env, gameInfosParser, guiSpriteInfos, attribute.first, attribute.second);
                else
                    error += "Error: This attribute \"" + attribute.first + "\" doesn't exist in the sprite named \"" + name + "\"\n";
            }
            return error;
        }
        
        static std::string fillSpritesheetPath(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUISpriteInfos& guiSpriteInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiSpriteInfos.setSpritesheetPath(Integrity::path(env, gameInfosParser.getFields()._resources.at("images"), value, error));
            return error; 
        }

        static std::string fillSheetGrid(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUISpriteInfos& guiSpriteInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiSpriteInfos.setSheetGrid(Integrity::xyValues(value, error));
            return error; 
        }

        static std::string fillSpriteSize(env::Environment& env, const GameInfosParser& gameInfosParser, env::GUISpriteInfos& guiSpriteInfos, const std::string& tag, const std::string& value){
            std::string error = "";

            guiSpriteInfos.setSpriteSize(Integrity::xyValues(value, error));
            return error; 
        }
    };

}
}

#endif