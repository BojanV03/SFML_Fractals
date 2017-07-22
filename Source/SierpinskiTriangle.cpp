#include "../Header/SierpinskiTriangle.h"

SierpinskiTriangle::SierpinskiTriangle()
{

}
SierpinskiTriangle::~SierpinskiTriangle()
{

}

void SierpinskiTriangle::setNumberOfIterations(int newNumberOfIterations)
{
  m_numberOfIterations = newNumberOfIterations;
}

int SierpinskiTriangle::getNumberOfIterations() const
{
  return m_numberOfIterations;
}

void SierpinskiTriangle::setBoundingBox(const sf::RectangleShape& newBoundingBox)
{
  m_boundingBox = sf::RectangleShape(newBoundingBox);
}
void SierpinskiTriangle::setBoundingBox(const sf::Vector2f& topLeft, const sf::Vector2f& bottomRight)
{
  m_boundingBox = sf::RectangleShape();
  m_boundingBox.setPosition(topLeft);
  m_boundingBox.setSize(sf::Vector2f(bottomRight.x-topLeft.x, bottomRight.y-topLeft.y));
}
void SierpinskiTriangle::setBoundingBox(float x1, float y1, float x2, float y2)
{
  m_boundingBox = sf::RectangleShape();
  m_boundingBox.setPosition(sf::Vector2f(x1, y1));
  m_boundingBox.setSize(sf::Vector2f(x2 - x1, y2 - y1));
}

sf::RectangleShape SierpinskiTriangle::getBoundingBox() const
{
  return m_boundingBox;
}

void SierpinskiTriangle::setColor(const sf::Color& newColor)
{
  m_color = sf::Color(newColor);
}

sf::Color SierpinskiTriangle::getColor() const
{
  return m_color;
}


void SierpinskiTriangle::drawSierpinskiTriangle(const sf::Vector2f &top, const sf::Vector2f &left, const sf::Vector2f &right,
                    int iteration, int numberOfIterations, sf::RenderWindow &window)
{
  if(numberOfIterations == 0)
  {
    sf::Color color = sf::Color(top.y/m_boundingBox.getSize().y*255, 0, right.x/m_boundingBox.getSize().x*255);
    drawTriangle(top, left, right, color, window);
    return;
  }
  else if(iteration == numberOfIterations-1)
      return;
  else
  {
    sf::Vector2f midLeft = sf::Vector2f((left.x + top.x)/2.0, (left.y+top.y)/2.0);
    sf::Vector2f midRight = sf::Vector2f((right.x + top.x)/2.0, (right.y + top.y)/2.0);
    sf::Vector2f midBottom = sf::Vector2f((left.x+right.x)/2.0, (left.y+right.y)/2.0);

    if(iteration == numberOfIterations-2)
    {
      sf::Color color = sf::Color(top.y/m_boundingBox.getSize().y*255, 0, midRight.x/m_boundingBox.getSize().x*255);
      drawTriangle(top, midLeft, midRight, color, window);
      color = sf::Color(midLeft.y/m_boundingBox.getSize().y*255, 0, midRight.x/m_boundingBox.getSize().x*255);
      drawTriangle(midLeft, left, midBottom, color, window);
      color = sf::Color(midRight.y/m_boundingBox.getSize().y*255, 0, midRight.x/m_boundingBox.getSize().x*255);
      drawTriangle(midRight, midBottom, right, color, window);
    }
    else
    {
      drawSierpinskiTriangle(top, midLeft, midRight, iteration+1, numberOfIterations, window);
      drawSierpinskiTriangle(midLeft, left, midBottom, iteration+1, numberOfIterations, window);
      drawSierpinskiTriangle(midRight, midBottom, right, iteration+1, numberOfIterations, window);
    }
  }
}

void SierpinskiTriangle::Render(sf::RenderWindow& window)
{
  sf::Vector2f bottomRightPoint = sf::Vector2f(m_boundingBox.getPosition().x + m_boundingBox.getSize().x, m_boundingBox.getPosition().y + m_boundingBox.getSize().y);
  sf::Vector2f topLeftPoint = sf::Vector2f(m_boundingBox.getPosition());
  sf::Vector2f top = sf::Vector2f((bottomRightPoint.x + topLeftPoint.x)/2.0, topLeftPoint.y);
  sf::Vector2f left = sf::Vector2f(topLeftPoint.x, bottomRightPoint.y);
  sf::Vector2f right = sf::Vector2f(bottomRightPoint.x, bottomRightPoint.y);
  drawSierpinskiTriangle(top, left, right, -1, m_numberOfIterations, window);
}
