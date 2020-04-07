#include "SceneGame.h"
#include "AnimationLoader.h"

SceneGame::SceneGame(ResourceAllocator<sf::Texture>& textureAllocator)
    : textureAllocator(textureAllocator), mapParser(textureAllocator) { }

void SceneGame::OnCreate()
{
    std::shared_ptr<Object> player = std::make_shared<Object>();

    auto sprite = player->AddComponent<C_Sprite>();
    sprite->SetTextureAllocator(&textureAllocator);

    auto movement = player->AddComponent<C_KeyboardMovement>();
    movement->SetInput(&input);
     
    auto animation = player->AddComponent<C_Animation>();

    int playerTextureID = textureAllocator.Add("Resources/knight.png");
    AnimationLoader animations;
    animations.Parse("Resources/knight.xml", playerTextureID, animation);



    // You will need to play around with this offset until it fits 
    // the level in at your chosen resolution. This worls for 1920 * 1080.
    // In future we will remove this hardcoded offset when we 
    // look at allowing the player to change resolutions.
    sf::Vector2i mapOffset(-100, 128);
    //sf::Vector2i mapOffset(128, 128);
    std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse("Resources/Test Map 1.tmx", mapOffset);
    objects.Add(levelTiles);

    objects.Add(player);
}

void SceneGame::OnDestroy()
{

}

void SceneGame::ProcessInput()
{
    input.Update();
}

void SceneGame::Update(float deltaTime)
{
    objects.ProcessRemovals();
    objects.ProcessNewObjects();

    objects.Update(deltaTime);
}

void SceneGame::LateUpdate(float deltaTime)
{
    objects.LateUpdate(deltaTime);
}

void SceneGame::Draw(Window& window)
{
    objects.Draw(window);
}