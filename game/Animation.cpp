
#include "Animation.h"

Animation::Animation()
    : frames(0), currentFrameIndex(0), currentFrameTime(0.f)
{

}

void Animation::AddFrame(int textureID, int x, int y,
    int width, int height, float frameTime)
{
    FrameData data;
    data.id = textureID;
    data.x = x;
    data.y = y;
    data.width = width;
    data.height = height;
    data.displayTimeSeconds = frameTime;

    frames.push_back(data);
}

const FrameData* Animation::GetCurrentFrame() const
{
    if (frames.size() > 0)
    {
        return &frames[currentFrameIndex];
    }

    return nullptr;
}

bool Animation::UpdateFrame(float deltaTime)
{
    if (frames.size() > 0)
    {
        currentFrameTime += deltaTime;

        if (currentFrameTime >=
            frames[currentFrameIndex].displayTimeSeconds)
        {
            currentFrameTime = 0.f;
            IncrementFrame();
            return true;
        }
    }

    return false;
}

void Animation::IncrementFrame()
{
    // For more information on how this works see here: 
    //https://www.cprogramming.com/tips/tip/increment-and-decrement-counters-with-rollover
    currentFrameIndex = (currentFrameIndex + 1) % frames.size();
}

void Animation::Reset()
{
    currentFrameIndex = 0;
    currentFrameTime = 0.f;
}
