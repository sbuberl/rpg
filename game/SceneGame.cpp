#include "SceneGame.h"
#include "AnimationLoader.h"

SceneGame::SceneGame(ResourceAllocator<sf::Texture>& textureAllocator)
    : textureAllocator(textureAllocator) { }

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