#include <iostream>
#include <chrono>
#include <string>

#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Playground!");
  window.setFramerateLimit(60.0);

  sf::Texture texture;
  texture.loadFromFile("assets/grassTile.png");

  sf::Texture texture2;
  texture2.loadFromFile("assets/selectTile.png");

  sf::RectangleShape selectionRect;
  selectionRect.setOutlineColor(sf::Color::Yellow);
  selectionRect.setOutlineThickness(1);
  selectionRect.setFillColor(sf::Color::Transparent);

  sf::Sprite spriteSelect;
  spriteSelect.setTexture(texture2);

  std::vector<sf::Sprite> sprites;
  for (int x = 0; x < 18; x++)
  {
    for (int y = 0; y < 18; y++)
    {
      sf::Sprite sprite;
      sprite.setTexture(texture);
      // int xPos = 50 + (x * texture.getSize().x / 2) - (y * texture)
      int xPos = (x - y) * (texture.getSize().x / 2);
      int yPos = (x + y) * texture.getSize().y / 2;
      std::cout << "x: " << xPos << "    y: " << yPos << std::endl;
      sprite.setPosition(texture.getSize().x * 10 + xPos, texture.getSize().y + yPos);
      sprites.push_back(sprite);
    }
  }
  auto startTime = std::chrono::high_resolution_clock::now();

  sf::Vector2f startPos;
  sf::Vector2f endPos;
  bool dragging = false;

  while (window.isOpen())
  {
    startTime = std::chrono::high_resolution_clock::now();
    sf::Event event;
    bool drawSelction = false;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        return 0;
      }

      auto pos = sf::Mouse::getPosition(window);
      int xPos = pos.x / texture2.getSize().x * texture2.getSize().x;
      int yPos = pos.y / texture2.getSize().y * texture2.getSize().y;
      spriteSelect.setPosition(xPos, yPos);

      if (event.type == sf::Event::MouseButtonPressed)
      {
        if (event.mouseButton.button == sf::Mouse::Button::Left)
        {
          startPos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
          selectionRect.setPosition(startPos);
          std::cout << "x " << startPos.x << "  y: " << startPos.y << std::endl;
          dragging = true;
        }
      }
      else if (event.type == sf::Event::MouseMoved)
      {
        if (dragging)
        {
          endPos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
          selectionRect.setSize(endPos - startPos);
        }
      }
      else if (event.type == sf::Event::MouseButtonReleased)
      {
        if (event.mouseButton.button == sf::Mouse::Button::Left)
        {
          dragging = false;
          selectionRect.setSize(sf::Vector2f(0, 0));
        }
      }
    }

    window.clear();
    for (auto &sprite : sprites)
    {
      window.draw(sprite);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
      window.draw(spriteSelect);

    if (dragging)
      window.draw(selectionRect);

    window.display();

    auto endTime = std::chrono::high_resolution_clock::now();
    auto time = endTime - startTime;
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
  }

  return 0;
}