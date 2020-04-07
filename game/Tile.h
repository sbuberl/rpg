#ifndef _TILE_H_
#define _TILE_H_

#include "ResourceAllocator.h"

#include <SFML/Graphics.hpp>

// Stores common tile data.
struct TileInfo
{
    TileInfo() : tileID(-1)
    {
    }

    TileInfo(int textureID, unsigned int tileID, sf::IntRect textureRect)
        : textureID(textureID), tileID(tileID), textureRect(textureRect) { }

    int tileID;
    int textureID;
    sf::IntRect textureRect;
};

struct Tile
{
    std::shared_ptr<TileInfo> properties;
    int x;
    int y;
};

#endif /* _TILE_H_ */
