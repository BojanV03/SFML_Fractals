#include "../Header/KochSnowflake.h"
#include <iostream>
void drawKochSnowflake(sf::Vector2f topLeft, sf::Vector2f bottomRight,
    int numberOfIterations, bool inverted, sf::RenderWindow& window)
{
  float oneThirdWidth = (bottomRight.x - topLeft.x)/6;
  float oneThirdHeight = (bottomRight.y - topLeft.y)/6;

  sf::Vector2f left = sf::Vector2f(topLeft.x+oneThirdWidth, bottomRight.y-2*oneThirdHeight);
  sf::Vector2f right = sf::Vector2f(bottomRight.x-oneThirdWidth, bottomRight.y-2*oneThirdHeight);
  sf::Vector2f top = TopPoint(left, right);

// 061 160 2000

  if(numberOfIterations == 0)
  {
    drawTriangle(top, left, right, sf::Color::Blue, window);
  }
  else
  {
    if(inverted)
    {
      KochSnowflake(right, left, 1, numberOfIterations, inverted, window);
      KochSnowflake(left, top, 1, numberOfIterations, inverted, window);
      KochSnowflake(top, right, 1, numberOfIterations, inverted, window);
    }
    else
    {
      drawTriangle(top, left, right, sf::Color::Blue, window);
      KochSnowflake(left, right, 1, numberOfIterations, inverted, window);
      KochSnowflake(top, left, 1, numberOfIterations, inverted, window);
      KochSnowflake(right, top, 1, numberOfIterations, inverted, window);
    }
  }
}

void KochSnowflake(sf::Vector2f pointA, sf::Vector2f pointB,
   int currentIteration, int numberOfIterations, bool inverted, sf::RenderWindow& window)
{
  if(currentIteration == numberOfIterations)
  {    sf::Vector2f a = sf::Vector2f(ONE_THIRD * (pointA.x - pointB.x) + pointB.x, ONE_THIRD * (pointA.y - pointB.y) + pointB.y);
    sf::Vector2f b = sf::Vector2f(TWO_THIRDS * (pointA.x - pointB.x) + pointB.x, TWO_THIRDS * (pointA.y - pointB.y) + pointB.y);
    sf::Vector2f c = TopPoint(a, b);
    drawTriangle(a, b, c, sf::Color::Blue, window);
    return;
  }
  else
  {
    sf::Vector2f a = sf::Vector2f(ONE_THIRD * (pointB.x - pointA.x) + pointA.x, ONE_THIRD * (pointB.y - pointA.y) + pointA.y);
    sf::Vector2f b = sf::Vector2f(TWO_THIRDS * (pointB.x - pointA.x) + pointA.x, TWO_THIRDS * (pointB.y - pointA.y) + pointA.y);
    sf::Vector2f c = TopPoint(b, a);

    if(!inverted)
      drawTriangle(a, b, c, sf::Color::Blue, window);
    KochSnowflake(pointA, a, currentIteration+1, numberOfIterations, inverted, window);
    KochSnowflake(b, pointB, currentIteration+1, numberOfIterations, inverted, window);
    KochSnowflake(a, c, currentIteration+1, numberOfIterations, inverted, window);
    KochSnowflake(c, b, currentIteration+1, numberOfIterations, inverted, window);
  }
}

sf::Vector2f UnitVector(sf::Vector2f& vector)
{
  float length = std::sqrt(std::pow(vector.x, 2.0f)*1.0f + std::pow(vector.y, 2.0f)*1.0f);
  return sf::Vector2f(vector.x/length, vector.y/length);
}

float TriangleHeight(sf::Vector2f& pointA, sf::Vector2f& pointB)
{
  float sideLen = std::sqrt(std::pow(pointA.x-pointB.x, 2)*1.0f + std::pow(pointA.y - pointB.y, 2) * 1.0f);
  return (sideLen*M_SQRT3)/2.0f;
}
sf::Vector2f CenterPoint(sf::Vector2f& pointA, sf::Vector2f& pointB)
{
  return sf::Vector2f((pointA.x + pointB.x)/2.0f, (pointA.y + pointB.y)/2.0f);
}

sf::Vector2f TopPoint(sf::Vector2f& pointA, sf::Vector2f& pointB)
{
  float h = TriangleHeight(pointA, pointB);
  sf::Vector2f center = CenterPoint(pointA, pointB);
  sf::Vector2f ABVector = sf::Vector2f((pointA.x-pointB.x), (pointA.y - pointB.y));
  // Jedinicni vektor
  ABVector = UnitVector(ABVector);
  // Normalan vector
  ABVector = sf::Vector2f(-ABVector.y, ABVector.x);
  return sf::Vector2f(center.x + ABVector.x*h, center.y + ABVector.y*h);
}
