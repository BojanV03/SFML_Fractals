#include "../Header/Renderer.h"

void drawTriangle(const sf::Vector2f &top, const sf::Vector2f &left, const sf::Vector2f &right, const sf::Color &fillColor, sf::RenderWindow &window)
{
  sf::ConvexShape shape;
  shape.setPointCount(3);
  shape.setPoint(0, top);
  shape.setPoint(1, left);
  shape.setPoint(2, right);
  shape.setFillColor(fillColor);
  shape.setOutlineColor(fillColor);
  shape.setOutlineThickness(2);
  window.draw(shape);
  return;
}
