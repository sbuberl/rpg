#ifndef _C_ANINMATION_H_
#define _C_ANINMATION_H_

#include "Component.h"
#include "Animation.h"
#include "C_Sprite.h"

#include <map>

enum class AnimationState
{
    None,
    Idle,
    Walk
};


using AnimationList = std::map<FacingDirection, std::shared_ptr<Animation>>;

class C_Animation : public Component
{
public:
    C_Animation(Object* owner);

    void Awake() override;

    void Update(float deltaTime) override;

    // Add animation to object. We need its state as well 
    // so that we can switch to it.
    void AddAnimation(AnimationState state, AnimationList& animationList);

    // Set current animation states.
    void SetAnimationState(AnimationState state);

    // Returns current animation state.
    const AnimationState& GetAnimationState() const;

    void SetAnimationDirection(FacingDirection dir);

private:
    std::shared_ptr<C_Sprite> sprite;
    std::map<AnimationState, AnimationList> animations;
    std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;
    FacingDirection currentDirection;
};
#endif /* _C_ANINMATION_H_ */
