#ifndef __ANIMATION_LOADER_H_
#define __ANIMATION_LOADER_H_

#include "C_Animation.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include <string>

class AnimationLoader
{
public:
    AnimationLoader()
    {
    }

    void Parse(const std::string& file, int textureId, std::shared_ptr<C_Animation> component)
    {
        char* fileLoc = new char[file.size() + 1];

        //TODO: make multi format version of string copy
#ifdef MACOS
        strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
        strcpy_s(fileLoc, file.size() + 1, file.c_str());
#endif 

        rapidxml::file<> xmlFile(fileLoc);
        rapidxml::xml_document<> doc;
        doc.parse<0>(xmlFile.data());
        rapidxml::xml_node<>* rootNode = doc.first_node("TextureAtlas");

        std::map<FacingDirection, std::shared_ptr<Animation>> idleAnimations;
        std::map<FacingDirection, std::shared_ptr<Animation>> walkAnimations;

        for (rapidxml::xml_node<> *  node = rootNode->first_node("sprite");
            node; node = node->next_sibling())
        {
            std::string name = node->first_attribute("n")->value();
            int x = std::atoi(node->first_attribute("x")->value());
            int y = std::atoi(node->first_attribute("y")->value());
            int width = std::atoi(node->first_attribute("w")->value());
            int height = std::atoi(node->first_attribute("h")->value());

            std::string walk("Walk");
            std::string idle("Idle");
            std::string restOfName;
            AnimationState state = AnimationState::None;
            if (!name.compare(0, idle.size(), idle))
            {
                state = AnimationState::Idle;
                restOfName = name.substr(idle.size());
            }
            else if (!name.compare(0, walk.size(), walk))
            {
                state = AnimationState::Walk;
                restOfName = name.substr(walk.size());
            }
            else
                continue;

            std::string down("Down");
            std::string up("Up");
            std::string left("Left");
            std::string right("Right");
            FacingDirection direction;
            if (!restOfName.compare(0, down.size(), down))
                direction = FacingDirection::Down;
            else if (!restOfName.compare(0, up.size(), up))
                direction = FacingDirection::Up;
            else if (!restOfName.compare(0, left.size(), left))
                direction = FacingDirection::Left;
            else if (!restOfName.compare(0, right.size(), right))
                direction = FacingDirection::Right;
            else
                continue;

            if (state == AnimationState::Idle)
            {
                std::shared_ptr<Animation> animation;
                auto itr = idleAnimations.find(direction);
                if (itr == idleAnimations.end()) {
                    animation = std::make_shared<Animation>();
                    idleAnimations.insert(std::make_pair(direction, animation));
                }
                else {
                    animation = itr->second;

                }
                animation->AddFrame(textureId, x, y, width, height, 0.2);
            }
            else if (state == AnimationState::Walk)
            {
                std::shared_ptr<Animation> animation;
                auto itr = walkAnimations.find(direction);
                if (itr == walkAnimations.end()) {
                    animation = std::make_shared<Animation>();
                    walkAnimations.insert(std::make_pair(direction, animation));
                }
                else {
                    animation = itr->second;
                }
                animation->AddFrame(textureId, x, y, width, height, 0.15);
            }

        }

        component->AddAnimation(AnimationState::Idle, idleAnimations);
        component->AddAnimation(AnimationState::Walk, walkAnimations);
    }
};

#endif /* __ANIMAITON_LOADER_H_ */
