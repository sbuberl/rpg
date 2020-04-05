#ifndef _SCENE_SPLASH_SCREEN_H_
#define _SCENE_SPLASH_SCREEN_H_

#include <SFML/Graphics.hpp>

#include "SceneStateMachine.h"
#include "ResourceAllocator.h"

class SceneSplashScreen : public Scene
{
public:
    SceneSplashScreen(SceneStateMachine& sceneStateMachine, Window& window, ResourceAllocator<sf::Texture>& textureAllocator);

    void OnCreate() override;
    void OnDestroy() override;

    void OnActivate() override;

    void SetSwitchToScene(unsigned int id);

    void Update(float deltaTime) override;
    void Draw(Window& window) override;

private:
    sf::Texture splashTexture;
    sf::Sprite splashSprite;

    SceneStateMachine& sceneStateMachine;
    Window& window;

    ResourceAllocator<sf::Texture>& textureAllocator;

    // We want to show this scene for a set amount of time
    float showForSeconds;

    // How long the scene has currently been visible.
    float currentSeconds;

    // The state we want to transition to when this scenes time expires.
    unsigned int switchToState;
};

#endif /* _SCENE_SPLASH_SCREEN_H_ */
