#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_

#include "Scene.h"
#include "Input.h"
#include "Object.h"
#include "C_Sprite.h"
#include "C_KeyboardMovement.h"
#include "ResourceAllocator.h"
#include "ObjectCollection.h"
#include "C_Animation.h"
#include "TileMapParser.h"

class SceneGame : public Scene
{
public:
    SceneGame(ResourceAllocator<sf::Texture>& textureAllocator);

    void OnCreate() override;
    void OnDestroy() override;

    void ProcessInput() override;
    void Update(float deltaTime) override;
    void Draw(Window& window) override;
    void LateUpdate(float deltaTime) override;

private:
    std::shared_ptr<Object> player;

    // We’ll store a reference to the texture allocator.
    ResourceAllocator<sf::Texture>& textureAllocator;

    Input input;

    ObjectCollection objects;
    TileMapParser mapParser;
};

#endif /* _SCENE_GAME_H_ */
