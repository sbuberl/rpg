#include "Quadtree.h"

Quadtree::Quadtree() : Quadtree(5, 5, 0, { 0.f, 0.f, 1920, 1080 },
    nullptr) {}

Quadtree::Quadtree(int maxObjects, int maxLevels, int level,
    sf::FloatRect bounds, Quadtree* parent)
    : maxObjects(maxObjects), maxLevels(maxLevels),
    level(level), bounds(bounds), parent(parent) {}

void Quadtree::Insert(std::shared_ptr<C_BoxCollider> object)
{
    if (children[0] != nullptr)
    {
        int indexToPlaceObject =
            GetChildIndexForObject(object->GetCollidable());

        if (indexToPlaceObject != thisTree)
        {
            children[indexToPlaceObject]->Insert(object);
            return;
        }
    }

    objects.emplace_back(object);

    if (objects.size() > maxObjects &&
        level < maxLevels && children[0] == nullptr)
    {
        Split();

        auto objIterator = objects.begin();
        while (objIterator != objects.end())
        {
            auto obj = *objIterator;
            int indexToPlaceObject =
                GetChildIndexForObject(obj->GetCollidable());

            if (indexToPlaceObject != thisTree)
            {
                children[indexToPlaceObject]->Insert(obj);
                objIterator = objects.erase(objIterator);

            }
            else
            {
                ++objIterator;
            }
        }
    }
}

void Quadtree::Remove(std::shared_ptr<C_BoxCollider> object)
{
    int index = GetChildIndexForObject(object->GetCollidable());

    if (index == thisTree || children[index] == nullptr)
    {
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects.at(i)->owner->instanceID->Get()
                == object->owner->instanceID->Get())
            {
                objects.erase(objects.begin() + i);
                break;
            }
        }
    }
    else
    {
        return children[index]->Remove(object);
    }
}

void Quadtree::Clear()
{
    objects.clear();

    for (int i = 0; i < 4; i++)
    {
        if (children[i] != nullptr)
        {
            children[i]->Clear();
            children[i] = nullptr;
        }
    }
}

std::vector<std::shared_ptr<C_BoxCollider>> Quadtree::Search(const sf::FloatRect& area)
{
    std::vector<std::shared_ptr<C_BoxCollider>> possibleOverlaps;
    Search(area, possibleOverlaps);
    
    std::vector<std::shared_ptr<C_BoxCollider>> returnList;
    
    for (auto collider : possibleOverlaps)
    {
        if (area.intersects(collider->GetCollidable()))
        {
            returnList.emplace_back(collider);
        }
    }

    return returnList;
}

void Quadtree::Search(const sf::FloatRect& area,
    std::vector<std::shared_ptr<C_BoxCollider>>& overlappingObjects)
{
    overlappingObjects.insert(overlappingObjects.end(), objects.begin(), objects.end());

    if (children[0] != nullptr)
    {
        int index = GetChildIndexForObject(area);

        if (index == thisTree)
        {
            for (int i = 0; i < 4; i++)
            {
                if (children[i]->GetBounds().intersects(area))
                {
                    children[i]->Search(area, overlappingObjects);
                }
            }
        }
        else
        {
            children[index]->Search(area, overlappingObjects);
        }
    }
}

const sf::FloatRect& Quadtree::GetBounds() const
{
    return bounds;
}

int Quadtree::GetChildIndexForObject(const sf::FloatRect& objectBounds)
{
    int index = -1;

    double verticalDividingLine = bounds.left + bounds.width * 0.5f;
    double horizontalDividingLine = bounds.top + bounds.height * 0.5f;

    bool north = objectBounds.top < horizontalDividingLine
        && (objectBounds.height + objectBounds.top < horizontalDividingLine);
    bool south = objectBounds.top > horizontalDividingLine;
    bool west = objectBounds.left < verticalDividingLine
        && (objectBounds.left + objectBounds.width < verticalDividingLine);
    bool east = objectBounds.left > verticalDividingLine;

    if (east)
    {
        if (north)
        {
            index = childNE;
        }
        else if (south)
        {
            index = childSE;
        }
    }
    else if (west)
    {
        if (north)
        {
            index = childNW;
        }
        else if (south)
        {
            index = childSW;
        }
    }

    return index;
}

void Quadtree::Split()
{
    const int childWidth = bounds.width / 2;
    const int childHeight = bounds.height / 2;

    children[childNE] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1,
        sf::FloatRect(bounds.left + childWidth, bounds.top, childWidth, childHeight),
        this);
    children[childNW] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1,
        sf::FloatRect(bounds.left, bounds.top, childWidth, childHeight),
        this);
    children[childSW] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1,
        sf::FloatRect(bounds.left, bounds.top + childHeight, childWidth, childHeight),
        this);
    children[childSE] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1,
        sf::FloatRect(bounds.left + childWidth, bounds.top + childHeight, childWidth, childHeight),
        this);
}