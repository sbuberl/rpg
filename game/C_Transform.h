#ifndef _C_TRANSFORM_H_
#define _C_TRANSFORM_H_

#include "Component.h"

class C_Transform : public Component
{
public:
    C_Transform(Object* owner);

    void SetPosition(float x, float y);
    void SetPosition(const sf::Vector2f &pos);

    void AddPosition(float x, float y);
    void AddPosition(sf::Vector2f pos);

    // Allows us to set x/y values separately.
    void SetX(float x);
    void SetY(float y);

    // Allows us to set x/y values separately.
    void AddX(float x);
    void AddY(float y);

    const sf::Vector2f& GetPosition() const;

    void SetStatic(bool isStatic);
    bool isStatic() const;

private:
    sf::Vector2f position;
    bool isStaticTransform;
};

#endif /* _C_TRANSFORM_H_ */
