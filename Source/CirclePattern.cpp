#include "../Header/CirclePattern.h"


void CirclePattern::setNumberOfIterations(int newNumberOfIterations)
{
  m_numberOfIterations = newNumberOfIterations;
}
int CirclePattern::getNumberOfIterations() const
{
  return m_numberOfIterations;
}

void CirclePattern::setBoundingBox(const sf::RectangleShape& newBoundingBox)
{
  m_boundingBox = sf::RectangleShape(newBoundingBox);
}
void CirclePattern::setBoundingBox(const sf::Vector2f& topLeft, const sf::Vector2f& bottomRight)
{
  m_boundingBox = sf::RectangleShape();
  m_boundingBox.setPosition(topLeft);
  m_boundingBox.setSize(sf::Vector2f(bottomRight.x-topLeft.x, bottomRight.y-topLeft.y));
}
void CirclePattern::setBoundingBox(float x1, float y1, float x2, float y2)
{
  m_boundingBox = sf::RectangleShape();
  m_boundingBox.setPosition(sf::Vector2f(x1, y1));
  m_boundingBox.setSize(sf::Vector2f(x2 - x1, y2 - y1));
}
sf::RectangleShape CirclePattern::getBoundingBox() const
{
  return m_boundingBox;
}

void CirclePattern::setColor(const sf::Color& newColor)
{
  m_color = sf::Color(newColor);
}

sf::Color CirclePattern::getColor() const
{
  return m_color;
}

void CirclePattern::Render(sf::RenderWindow& window)
{
  sf::Vector2f bottomRight = sf::Vector2f(m_boundingBox.getPosition().x + m_boundingBox.getSize().x, m_boundingBox.getPosition().y + m_boundingBox.getSize().y);
  drawCircleFractal(m_boundingBox.getPosition(), bottomRight, 0, window);
}



void CirclePattern::drawCircleFractal(const sf::Vector2f &topLeft, const sf::Vector2f &bottomRight, int currentIteration,
  sf::RenderWindow &window)
{
  if(currentIteration == m_numberOfIterations)
    return;

  float radius = std::abs(bottomRight.x - topLeft.x)/4.0;
  sf::CircleShape circle(radius);
  circle.setFillColor(sf::Color::Transparent);
  circle.setOutlineColor(sf::Color::Red);
  circle.setOutlineThickness(1);

  if(currentIteration == m_numberOfIterations-1)
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
    sf::Vector2f midTop = sf::Vector2f((topLeft.x + bottomRight.x)/2.0, topLeft.y);
    sf::Vector2f midLeft = sf::Vector2f(topLeft.x, (topLeft.y + bottomRight.y)/2.0);
    sf::Vector2f midRight = sf::Vector2f(bottomRight.x, (topLeft.y + bottomRight.y)/2.0);
    sf::Vector2f midBottom = sf::Vector2f((topLeft.x + bottomRight.x)/2.0, bottomRight.y);
    sf::Vector2f center = sf::Vector2f((topLeft.x + bottomRight.x)/2.0, (topLeft.y + bottomRight.y)/2.0);

    drawCircleFractal(topLeft, center, currentIteration+1, window);
    drawCircleFractal(midTop, midRight, currentIteration+1, window);
    drawCircleFractal(midLeft, midBottom, currentIteration+1, window);
    drawCircleFractal(center, bottomRight, currentIteration+1, window);
  }
}
