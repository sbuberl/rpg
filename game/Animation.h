#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>


struct FrameData
{
    int id; // Texture id (retrieved from our texture allocator).
    int x; // x position of sprite in the texture.
    int y; // y position of sprite in the texture.
    int width; // Width of sprite.
    int height; // Height of sprite.
    float displayTimeSeconds; // How long to display the frame.
};

enum class FacingDirection
{
    None,
    Up,
    Down,
    Left,
    Right
};

class Animation
{
public:
    Animation();

    void AddFrame(int textureID, int x, int y,
        int width, int height, float frameTime);

    const FrameData* GetCurrentFrame() const;

    bool UpdateFrame(float deltaTime);

    void Reset();

    void SetDirection(FacingDirection dir);
    FacingDirection GetDirection() const;

private:
    void IncrementFrame();

    // Stores all frames for our animation.
    std::vector<FrameData> frames;

    // Current frame.
    int currentFrameIndex;

    // We use this to decide when to transition to the next frame.
    float currentFrameTime;
};

#endif // _ANIMATION_H_
