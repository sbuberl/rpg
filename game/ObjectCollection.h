#ifndef _OBJECT_COLLECTION_H_
#define _OBJECT_COLLECTION_H_

#include <memory>
#include <vector>

#include "Object.h"
#include "S_Drawable.h"

class ObjectCollection
{
public:
    void Add(std::shared_ptr<Object> object);
    void Add(std::vector<std::shared_ptr<Object>>& objects);

    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window& window);

    void ProcessNewObjects();
    void ProcessRemovals();

private:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Object>> newObjects;
    S_Drawable drawables;
};

#endif /* _OBJECT_COLLECTION_H_ */
