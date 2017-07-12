#include "../Header/Renderer.h"

void drawTriangle(const sf::Vector2f &top, const sf::Vector2f &left, const sf::Vector2f &right, sf::Color &color, sf::RenderWindow &window)
{
  sf::ConvexShape shape;
  shape.setPointCount(3);
  shape.setPoint(0, top);
  shape.setPoint(1, left);
  shape.setPoint(2, right);
  shape.setFillColor(color);
  window.draw(shape);
  return;
}
