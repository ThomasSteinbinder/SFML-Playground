#include "mapTileTypes.hpp"
#include <SFML/Graphics.hpp>

class MapTile
{
public:
  MapTile();
  MapTile(MapTileType tileType);

  MapTileType GetTileType();
  void SetTileType(MapTileType newTileType);
  sf::Texture GetTexture();

private:
  MapTileType _tileType;
  sf::Sprite _sprite;
};