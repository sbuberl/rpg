#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

int main()
{
    Game game;

    while (game.IsRunning())
    {
        game.ProcessInput();
        game.Update();
        game.LateUpdate();
        game.Draw();
        game.CalculateDeltaTime();
    }
}

