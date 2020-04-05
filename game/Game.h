#ifndef _GAME_H_
#define _GAME_H_

#include "Window.h"
#include "Input.h"
#include "SceneStateMachine.h"
#include "SceneSplashScreen.h"
#include "SceneGame.h"

class Game
{
public:
    Game();

    void ProcessInput();
    void Update();
    void LateUpdate();
    void Draw();
    void CalculateDeltaTime();
    bool IsRunning() const;

private:
    Window window;

    sf::Clock clock;
    float deltaTime;

    SceneStateMachine sceneStateMachine;

    ResourceAllocator<sf::Texture> textureAllocator;
};

#endif /* _GAME_H_ */
