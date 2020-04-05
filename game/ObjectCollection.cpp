#include "ObjectCollection.h"

void ObjectCollection::Update(float deltaTime)
{
    for (auto& o : objects)
    {
        o->Update(deltaTime);
    }
}

void ObjectCollection::LateUpdate(float deltaTime)
{
    for (auto& o : objects)
    {
        o->LateUpdate(deltaTime);
    }
}

void ObjectCollection::Draw(Window& window)
{
    for (auto& o : objects)
    {
        o->Draw(window);
    }
}

void ObjectCollection::Add(std::shared_ptr<Object> object)
{
    newObjects.push_back(object);
}

void ObjectCollection::ProcessNewObjects()
{
    if (newObjects.size() > 0)
    {
        for (const auto& o : newObjects)
        {
            o->Awake();
        }

        for (const auto& o : newObjects)
        {
            o->Start();
        }

        objects.assign(newObjects.begin(), newObjects.end());

        newObjects.clear();
    }
}

void ObjectCollection::ProcessRemovals()
{
    auto objIterator = objects.begin();
    while (objIterator != objects.end())
    {
        auto obj = **objIterator;

        if (obj.IsQueuedForRemoval())
        {
            objIterator = objects.erase(objIterator);
        }
        else
        {
            ++objIterator;
        }
    }
}
