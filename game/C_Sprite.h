#ifndef _C_SPRITE_H_
#define _C_SPRITE_H_

#include "Component.h"
#include "ResourceAllocator.h"

class C_Sprite : public Component
{
public:
    C_Sprite(Object* owner);

    void SetTextureAllocator(ResourceAllocator<sf::Texture>* allocator);

    void SetTextureRect(int x, int y, int width, int height);
    void SetTextureRect(const sf::IntRect& rect);

    // We add a new overloaded Load method that accepts a texture id.
    void Load(int id);

    // Loads a sprite from file.
    void Load(const std::string& filePath);

    // We override the draw method so we can draw our sprite.
    void Draw(Window& window) override;

    // We’ll use this to update our sprite based on our position.
    void LateUpdate(float deltaTime) override;

private:
    ResourceAllocator<sf::Texture>* allocator;
    sf::Sprite sprite;
    int currentTextureID;
};

#endif /* _C_SPRITE_H_ */
