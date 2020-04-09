#ifndef _C_BOX_COLLIDER_H_
#define _C_BOX_COLLIDER_H_

#include "Component.h"
#include "C_Collider.h"

class C_BoxCollider : public C_Collider
{
public:
    C_BoxCollider(Object* owner);

    Manifold Intersects(std::shared_ptr<C_Collider> other) override;
    void ResolveOverlap(const Manifold& m) override;

    void SetCollidable(const sf::FloatRect& rect);
    const sf::FloatRect& GetCollidable();

private:
    void SetPosition();

    sf::FloatRect AABB;
    sf::Vector2f offset;
};

#endif /* _C_BOX_COLLIDER_H_ */
