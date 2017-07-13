#include "../Header/CirclePattern.h"


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

  if(currentIteration == numberOfIterations-1)
  {
    for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
      {
        /* Draw 4 circles that are entirely contained within the square */
        if(i < 2 && j < 2)
        {
          circle.setPosition(topLeft.x + 2*i*radius, topLeft.y + 2*j*radius);
          window.draw(circle);
        }
        /* Other 9 semi/quarter circles */
        circle.setPosition((topLeft.x - radius) + 2*i*radius, (topLeft.y - radius) + 2*j*radius);
        window.draw(circle);
      }
    }
  }
  else
  {
    sf::Vector2f midTop = sf::Vector2f((topLeft.x + bottomRight.x)/2, topLeft.y);
    sf::Vector2f midLeft = sf::Vector2f(topLeft.x, (topLeft.y + bottomRight.y)/2);
    sf::Vector2f midRight = sf::Vector2f(bottomRight.x, (topLeft.y + bottomRight.y)/2);
    sf::Vector2f midBottom = sf::Vector2f((topLeft.x + bottomRight.x)/2, bottomRight.y);
    sf::Vector2f center = sf::Vector2f((topLeft.x + bottomRight.x)/2, (topLeft.y + bottomRight.y)/2);

    circleFractal(topLeft, center, currentIteration+1, numberOfIterations, window);
    circleFractal(midTop, midRight, currentIteration+1, numberOfIterations, window);
    circleFractal(midLeft, midBottom, currentIteration+1, numberOfIterations, window);
    circleFractal(center, bottomRight, currentIteration+1, numberOfIterations, window);
  }
}
