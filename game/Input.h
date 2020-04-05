#ifndef _INPUT_H_
#define _INPUT_H_

#include "Bitmask.h"
#include <SFML/Graphics.hpp>

class Input
{
public:
    enum class Key
    {
        None = 0,
        Left = 1,
        Right = 2,
        Up = 3,
        Down = 4,
        Esc = 5
    };

    bool IsKeyPressed(Key keycode); // Returns true if the key is pressed.
    bool IsKeyDown(Key keycode); // Returns true if the key was just pressed.
    bool IsKeyUp(Key keycode); // Returns true if the key was just released.
    void Update();
private:
    Bitmask thisFrameKeys;
    Bitmask lastFrameKeys;
};

#endif /* _INPUT_H_ */
