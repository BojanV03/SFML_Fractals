#include "../Header/Sierpinski.h"
#include <stdlib.h>
int WIDTH = 1200;
int HEIGHT = 1000;

void SierpinskiTriangle(const sf::Vector2f &top, const sf::Vector2f &left, const sf::Vector2f &right,
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
      SierpinskiTriangle(top, midLeft, midRight, iteration+1, numberOfIterations, window);
      SierpinskiTriangle(midLeft, left, midBottom, iteration+1, numberOfIterations, window);
      SierpinskiTriangle(midRight, midBottom, right, iteration+1, numberOfIterations, window);
    }
  }
}

void drawSierpinskiTriangle(const sf::Vector2f &topLeftPoint, const sf::Vector2f &bottomRightPoint,
                    int numberOfIterations, sf::RenderWindow &window)
{
  sf::Vector2f top = sf::Vector2f((bottomRightPoint.x + topLeftPoint.x)/2, topLeftPoint.y);
  sf::Vector2f left = sf::Vector2f(topLeftPoint.x, bottomRightPoint.y);
  sf::Vector2f right = sf::Vector2f(bottomRightPoint.x, bottomRightPoint.y);
  WIDTH  = std::abs(bottomRightPoint.x - topLeftPoint.x);
  HEIGHT = std::abs(bottomRightPoint.y - topLeftPoint.y);
  SierpinskiTriangle(top, left, right, -1, numberOfIterations, window);
}


void drawSierpinskiCarpet(const sf::Vector2f &topLeftPoint, const sf::Vector2f &bottomRightPoint,
  const std::vector<int> &squaresToSkip, int gridSize, int numberOfIterations, sf::RenderWindow &window)
{
    WIDTH  = std::abs(bottomRightPoint.x - topLeftPoint.x);
    HEIGHT = std::abs(bottomRightPoint.y - topLeftPoint.y);
    SierpinskiCarpet(topLeftPoint, bottomRightPoint, squaresToSkip, gridSize, 0, numberOfIterations, window);
}

void SierpinskiCarpet(const sf::Vector2f &topLeftPoint, const sf::Vector2f &bottomRightPoint,
  const std::vector<int> &squaresToSkip, int gridSize, int currentIteration, int numberOfIterations, sf::RenderWindow &window)
{
    if(currentIteration == numberOfIterations)
    {
      float width  = std::abs(bottomRightPoint.x - topLeftPoint.x);
      float height = std::abs(bottomRightPoint.y - topLeftPoint.y);
      sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(width, height));
      int R = 255 - (1.0*bottomRightPoint.x)/WIDTH*255;
      int G = 255 - (1.0*bottomRightPoint.y)/WIDTH*255;
      int B = (R + G)/2;
      sf::Color color = sf::Color(R, G, B);
      rect.setFillColor(color);
      rect.setPosition(topLeftPoint);
      window.draw(rect);
      return;
    }
//    std::cout << currentIteration << std::endl;
    for(int i = 0; i < gridSize*gridSize; i++)
    {
      if(std::find(squaresToSkip.cbegin(), squaresToSkip.cend(), i) != squaresToSkip.cend())
        continue;

      float width = std::abs(bottomRightPoint.x - topLeftPoint.x)/gridSize;
      float height= std::abs(bottomRightPoint.y - topLeftPoint.y)/gridSize;
      int ii = i % gridSize;
      int ij = i / gridSize;

  //        std::cout << "    " << i << std::endl;
      sf::Vector2f newTopLeft = sf::Vector2f(topLeftPoint.x + (ii*width), topLeftPoint.y + ij*height);
      sf::Vector2f newBottomRight = sf::Vector2f(topLeftPoint.x + (ii+1)*width, topLeftPoint.y + (ij+1)*height);

      SierpinskiCarpet(newTopLeft, newBottomRight, squaresToSkip, gridSize, currentIteration+1, numberOfIterations, window);
    }
}
