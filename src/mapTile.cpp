#include "mapTile.hpp"

MapTile::MapTile()
{
  _tileType = MapTileType::Grass;
  // _sprite = 
}

MapTile::MapTile(MapTileType tileType)
{
  _tileType = tileType;
}

MapTileType MapTile::GetTileType()
{
  return _tileType;
}

void MapTile::SetTileType(MapTileType newTileType)
{
  _tileType = newTileType;
}

sf::Texture MapTile::GetTexture()
{
  // return _sprite;
}