#include "../Header/KochSnowflake.h"
#include <iostream>

void KochSnowflake::setNumberOfIterations(int newNumberOfIterations)
{
  m_numberOfIterations = newNumberOfIterations;
}

int KochSnowflake::getNumberOfIterations() const
{
  return m_numberOfIterations;
}

void KochSnowflake::setBoundingBox(const sf::RectangleShape& newBoundingBox)
{
  m_boundingBox = sf::RectangleShape(newBoundingBox);
}
void KochSnowflake::setBoundingBox(const sf::Vector2f& topLeft, const sf::Vector2f& bottomRight)
{
  m_boundingBox = sf::RectangleShape();
  m_boundingBox.setPosition(topLeft);
  m_boundingBox.setSize(sf::Vector2f(bottomRight.x-topLeft.x, bottomRight.y-topLeft.y));
}
void KochSnowflake::setBoundingBox(float x1, float y1, float x2, float y2)
{
  m_boundingBox = sf::RectangleShape();
  m_boundingBox.setPosition(sf::Vector2f(x1, y1));
  m_boundingBox.setSize(sf::Vector2f(x2 - x1, y2 - y1));
}

sf::RectangleShape KochSnowflake::getBoundingBox() const
{
  return m_boundingBox;
}

void KochSnowflake::setColor(const sf::Color& newColor)
{
  m_color = sf::Color(newColor);
}

sf::Color KochSnowflake::getColor() const
{
  return m_color;
}


void KochSnowflake::setInverted(bool newInverted)
{
  m_inverted = newInverted;
}
bool KochSnowflake::getInverted() const
{
  return m_inverted;
}

void KochSnowflake::Render(sf::RenderWindow& window)
{
  sf::Vector2f topLeft = m_boundingBox.getPosition();
  sf::Vector2f bottomRight = sf::Vector2f(m_boundingBox.getPosition().x + m_boundingBox.getSize().x, m_boundingBox.getPosition().y + m_boundingBox.getSize().y);

  float oneThirdWidth = (bottomRight.x - topLeft.x)/6;
  float oneThirdHeight = (bottomRight.y - topLeft.y)/6;

  sf::Vector2f left = sf::Vector2f(topLeft.x+oneThirdWidth, bottomRight.y-2*oneThirdHeight);
  sf::Vector2f right = sf::Vector2f(bottomRight.x-oneThirdWidth, bottomRight.y-2*oneThirdHeight);
  sf::Vector2f top = TopPoint(left, right);

  if(m_numberOfIterations == 0)
  {
    drawTriangle(top, left, right, m_color, window);
  }
  else
  {
    if(m_inverted)
    {
      drawKochSnowflake(right, left, 1, m_inverted, window);
      drawKochSnowflake(left, top, 1, m_inverted, window);
      drawKochSnowflake(top, right, 1, m_inverted, window);
    }
    else
    {
      drawTriangle(top, left, right, m_color, window);
      drawKochSnowflake(left, right, 1, m_inverted, window);
      drawKochSnowflake(top, left, 1, m_inverted, window);
      drawKochSnowflake(right, top, 1, m_inverted, window);
    }
  }
}

void KochSnowflake::drawKochSnowflake(sf::Vector2f pointA, sf::Vector2f pointB,
   int currentIteration, bool inverted, sf::RenderWindow& window)
{
  if(currentIteration == m_numberOfIterations)
  {    sf::Vector2f a = sf::Vector2f(ONE_THIRD * (pointA.x - pointB.x) + pointB.x, ONE_THIRD * (pointA.y - pointB.y) + pointB.y);
    sf::Vector2f b = sf::Vector2f(TWO_THIRDS * (pointA.x - pointB.x) + pointB.x, TWO_THIRDS * (pointA.y - pointB.y) + pointB.y);
    sf::Vector2f c = TopPoint(a, b);
    drawTriangle(a, b, c, m_color, window);
    return;
  }
  else
  {
    sf::Vector2f a = sf::Vector2f(ONE_THIRD * (pointB.x - pointA.x) + pointA.x, ONE_THIRD * (pointB.y - pointA.y) + pointA.y);
    sf::Vector2f b = sf::Vector2f(TWO_THIRDS * (pointB.x - pointA.x) + pointA.x, TWO_THIRDS * (pointB.y - pointA.y) + pointA.y);
    sf::Vector2f c = TopPoint(b, a);

    if(!inverted)
      drawTriangle(a, b, c, m_color, window);
    drawKochSnowflake(pointA, a, currentIteration+1, inverted, window);
    drawKochSnowflake(b, pointB, currentIteration+1, inverted, window);
    drawKochSnowflake(a, c, currentIteration+1, inverted, window);
    drawKochSnowflake(c, b, currentIteration+1, inverted, window);
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
