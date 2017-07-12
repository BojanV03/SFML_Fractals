#include "../Header/Sierpinski.h"

int WIDTH = 1200;
int HEIGHT = 1000;

void Sierpinski(const sf::Vector2f &top, const sf::Vector2f &left, const sf::Vector2f &right,
                    int iteration, int numberOfIterations, sf::RenderWindow &window)
{
  if(numberOfIterations == 0)
  {
    sf::Color color = sf::Color(top.y/HEIGHT*255, 0, right.x/WIDTH*255);
    drawTriangle(top, left, right, color, window);
    return;
  }
  else if(iteration == numberOfIterations-1)
      return;
  else
  {
    sf::Vector2f midLeft = sf::Vector2f((left.x + top.x)/2, (left.y+top.y)/2);
    sf::Vector2f midRight = sf::Vector2f((right.x + top.x)/2, (right.y + top.y)/2);
    sf::Vector2f midBottom = sf::Vector2f((left.x+right.x)/2, (left.y+right.y)/2);

    if(iteration == numberOfIterations-2)
    {
      sf::Color color = sf::Color(top.y/HEIGHT*255, 0, midRight.x/WIDTH*255);
      drawTriangle(top, midLeft, midRight, color, window);
      color = sf::Color(midLeft.y/HEIGHT*255, 0, midRight.x/WIDTH*255);
      drawTriangle(midLeft, left, midBottom, color, window);
      color = sf::Color(midRight.y/HEIGHT*255, 0, midRight.x/WIDTH*255);
      drawTriangle(midRight, midBottom, right, color, window);
    }
    else
    {
      Sierpinski(top, midLeft, midRight, iteration+1, numberOfIterations, window);
      Sierpinski(midLeft, left, midBottom, iteration+1, numberOfIterations, window);
      Sierpinski(midRight, midBottom, right, iteration+1, numberOfIterations, window);
    }
  }
}

void drawSierpinski(const sf::Vector2f &topLeftPoint, const sf::Vector2f &bottomRightPoint,
                    int numberOfIterations, sf::RenderWindow &window)
{
  sf::Vector2f top = sf::Vector2f((bottomRightPoint.x + topLeftPoint.x)/2, topLeftPoint.y);
  sf::Vector2f left = sf::Vector2f(topLeftPoint.x, bottomRightPoint.y);
  sf::Vector2f right = sf::Vector2f(bottomRightPoint.x, bottomRightPoint.y);

  Sierpinski(top, left, right, -1, numberOfIterations, window);
}
