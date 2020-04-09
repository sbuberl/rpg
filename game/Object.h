#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Window.h"
#include "Component.h"
#include "C_Transform.h"
#include "C_Drawable.h"
#include "C_InstanceID.h"

#include <vector>


class Object
{
public:
    Object();

    // Awake is called when object created. Use to ensure 
    // required components are present.
    void Awake();

    // Start is called after Awake method. Use to initialise variables.
    void Start();

    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window& window);

    bool IsQueuedForRemoval();
    void QueueForRemoval();

    template <typename T> std::shared_ptr<T> AddComponent()
    {
        static_assert(
            std::is_base_of<Component, T>::value, "T must derive from Component"
            );

        //TODO: allow us to add more than one component, implement getcomponents
        // Check that we don't already have a component of this type.
        for (auto& exisitingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }

        std::shared_ptr<T> newComponent = std::make_shared<T>(this);

        components.push_back(newComponent);

        // We now check if the component is a drawable.
        if (std::dynamic_pointer_cast<C_Drawable>(newComponent))
        {
            drawable = std::dynamic_pointer_cast<C_Drawable>(newComponent);
        }

        return newComponent;
    };

    std::shared_ptr<C_Drawable> GetDrawable();

    template <typename T> std::shared_ptr<T> GetComponent()
    {
        static_assert(std::is_base_of<Component, T>::value,
            "T must derive from Component");

            // Check that we don't already have a component of this type.
            for (auto& exisitingComponent : components)
            {
                if (std::dynamic_pointer_cast<T>(exisitingComponent))
                {
                    return std::dynamic_pointer_cast<T>(exisitingComponent);
                }
            }

        return nullptr;
    };

    std::shared_ptr<C_Transform> transform;
    std::shared_ptr<C_InstanceID> instanceID;
private:
    std::vector<std::shared_ptr<Component>> components;
    bool queuedForRemoval;
    std::shared_ptr<C_Drawable> drawable;
};

#endif /* _OBJECT_H_ */
