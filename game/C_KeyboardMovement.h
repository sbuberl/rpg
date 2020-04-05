#ifndef _C_KEYBOARD_MOVEMENT_H_
#define _C_KEYBOARD_MOVEMENT_H_

#include "Component.h"
#include "Input.h"
#include "C_Animation.h"

class C_KeyboardMovement : public Component
{
public:
    C_KeyboardMovement(Object * owner);

    void SetInput(Input* input);
    void SetMovementSpeed(int moveSpeed);

    void Awake() override;
    void Update(float deltaTime) override;

private:
    int moveSpeed;
    Input* input;
    std::shared_ptr<C_Animation> animation;
};

#endif /* _C_KEYBOARD_MOVEMENT_H_ */
