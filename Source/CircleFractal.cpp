#include "../Header/CircleFractal.h"


void drawCircleFractal(const sf::Vector2f &topLeft, const sf::Vector2f &bottomRight, int numberOfIterations, sf::RenderWindow &window)
{
  circleFractal(topLeft, bottomRight, 0, numberOfIterations, window);

}


void circleFractal(const sf::Vector2f &topLeft, const sf::Vector2f &bottomRight, int currentIteration,
  int numberOfIterations, sf::RenderWindow &window)
{
  if(currentIteration == numberOfIterations)
    return;

  float radius = std::abs(bottomRight.x - topLeft.x)/4.0;
  sf::CircleShape circle(radius);
  circle.setFillColor(sf::Color::Transparent);
  circle.setOutlineColor(sf::Color::Red);
  circle.setOutlineThickness(1);
  sf::Vector2f midTop = sf::Vector2f((topLeft.x + bottomRight.x)/2, topLeft.y);
  sf::Vector2f midLeft = sf::Vector2f(topLeft.x, (topLeft.y + bottomRight.y)/2);
  sf::Vector2f midRight = sf::Vector2f(bottomRight.x, (topLeft.y + bottomRight.y)/2);
  sf::Vector2f midBottom = sf::Vector2f((topLeft.x + bottomRight.x)/2, bottomRight.y);
  sf::Vector2f center = sf::Vector2f((topLeft.x + bottomRight.x)/2, (topLeft.y + bottomRight.y)/2);
  if(currentIteration == numberOfIterations-1)
  {
    circle.setPosition(topLeft);
    window.draw(circle);
    circle.setPosition(midTop);
    window.draw(circle);
    circle.setPosition(midLeft);
    window.draw(circle);
    circle.setPosition(center);
    window.draw(circle);
    circle.setPosition(topLeft.x - radius, topLeft.y - radius);
    window.draw(circle);
    circle.setPosition(topLeft.x + radius, topLeft.y + radius);
    window.draw(circle);
    circle.setPosition(topLeft.x + radius, topLeft.y - radius);
    window.draw(circle);
    circle.setPosition(topLeft.x - radius, topLeft.y + radius);
    window.draw(circle);

    circle.setPosition(bottomRight.x - radius, bottomRight.y - radius);
    window.draw(circle);
    circle.setPosition(bottomRight.x - 3*radius, bottomRight.y - radius);
    window.draw(circle);
    circle.setPosition(bottomRight.x - 5*radius, bottomRight.y - radius);
    window.draw(circle);
    circle.setPosition(bottomRight.x - radius, bottomRight.y - 3*radius);
    window.draw(circle);
    circle.setPosition(bottomRight.x - radius, bottomRight.y - 5*radius);
    window.draw(circle);
  }
  else
  {
    circleFractal(topLeft, center, currentIteration+1, numberOfIterations, window);
    circleFractal(midTop, midRight, currentIteration+1, numberOfIterations, window);
    circleFractal(midLeft, midBottom, currentIteration+1, numberOfIterations, window);
    circleFractal(center, bottomRight, currentIteration+1, numberOfIterations, window);
  }
}
