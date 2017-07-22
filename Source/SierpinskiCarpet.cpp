#include "../Header/SierpinskiCarpet.h"

SierpinskiCarpet::SierpinskiCarpet()
{
  m_squaresToSkip = std::vector<int>();
}

SierpinskiCarpet::~SierpinskiCarpet()
{

}

void SierpinskiCarpet::addSquareToSkip(int n)
{
  m_squaresToSkip.push_back(n);
}

void SierpinskiCarpet::clearSquaresToSkip()
{
  m_squaresToSkip.clear();
}

void SierpinskiCarpet::removeSquareToSkip(int n)
{
  for(auto i = m_squaresToSkip.begin(); i != m_squaresToSkip.end(); i++)
  {
    if(*i == n)
    {
      m_squaresToSkip.erase(i);
    }
  }
}

void SierpinskiCarpet::setNumberOfIterations(int newNumberOfIterations)
{
  m_numberOfIterations = newNumberOfIterations;
}

int SierpinskiCarpet::getNumberOfIterations() const
{
  return m_numberOfIterations;
}

void SierpinskiCarpet::setBoundingBox(const sf::RectangleShape& newBoundingBox)
{
  m_boundingBox = sf::RectangleShape(newBoundingBox);
}
void SierpinskiCarpet::setBoundingBox(const sf::Vector2f& topLeft, const sf::Vector2f& bottomRight)
{
  m_boundingBox = sf::RectangleShape();
  m_boundingBox.setPosition(topLeft);
  m_boundingBox.setSize(sf::Vector2f(bottomRight.x-topLeft.x, bottomRight.y-topLeft.y));
}
void SierpinskiCarpet::setBoundingBox(float x1, float y1, float x2, float y2)
{
  m_boundingBox = sf::RectangleShape();
  m_boundingBox.setPosition(sf::Vector2f(x1, y1));
  m_boundingBox.setSize(sf::Vector2f(x2 - x1, y2 - y1));
}

sf::RectangleShape SierpinskiCarpet::getBoundingBox() const
{
  return m_boundingBox;
}

void SierpinskiCarpet::setColor(const sf::Color& newColor)
{
  m_color = sf::Color(newColor);
}

sf::Color SierpinskiCarpet::getColor() const
{
  return m_color;
}


void SierpinskiCarpet::Render(sf::RenderWindow& window)
{
  sf::Vector2f bottomRightPoint = sf::Vector2f(m_boundingBox.getPosition().x + m_boundingBox.getSize().x, m_boundingBox.getPosition().y + m_boundingBox.getSize().y);
  sf::Vector2f topLeftPoint = sf::Vector2f(m_boundingBox.getPosition());
  drawSierpinskiCarpet(topLeftPoint, bottomRightPoint, 0, window);

}

void SierpinskiCarpet::setGridSize(int newGridSize)
{
  m_gridSize = newGridSize;
}
int SierpinskiCarpet::getGridSize() const
{
  return m_gridSize;
}

void SierpinskiCarpet::drawSierpinskiCarpet(const sf::Vector2f &topLeftPoint, const sf::Vector2f &bottomRightPoint,
  int currentIteration, sf::RenderWindow &window)
{
    if(currentIteration == m_numberOfIterations)
    {
      float width  = std::abs(bottomRightPoint.x - topLeftPoint.x);
      float height = std::abs(bottomRightPoint.y - topLeftPoint.y);
      sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(width, height));
      int R = 255 - (1.0*bottomRightPoint.x)/m_boundingBox.getSize().x*255;
      int G = 255 - (1.0*bottomRightPoint.y)/m_boundingBox.getSize().x*255;
      int B = (R + G)/2;
      sf::Color color = sf::Color(R, G, B);
      rect.setFillColor(color);
      rect.setPosition(topLeftPoint);
      window.draw(rect);
      return;
    }
//    std::cout << currentIteration << std::endl;
    for(int i = 0; i < m_gridSize*m_gridSize; i++)
    {
      if(std::find(m_squaresToSkip.cbegin(), m_squaresToSkip.cend(), i) != m_squaresToSkip.cend())
        continue;

      float width = std::abs(bottomRightPoint.x - topLeftPoint.x)/m_gridSize;
      float height= std::abs(bottomRightPoint.y - topLeftPoint.y)/m_gridSize;
      int ii = i % m_gridSize;
      int ij = i / m_gridSize;

  //        std::cout << "    " << i << std::endl;
      sf::Vector2f newTopLeft = sf::Vector2f(topLeftPoint.x + (ii*width), topLeftPoint.y + ij*height);
      sf::Vector2f newBottomRight = sf::Vector2f(topLeftPoint.x + (ii+1)*width, topLeftPoint.y + (ij+1)*height);

      drawSierpinskiCarpet(newTopLeft, newBottomRight, currentIteration+1, window);
    }
}
