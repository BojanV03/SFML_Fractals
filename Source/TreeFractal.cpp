#include "../Header/TreeFractal.h"
#include "math.h"

TreeFractal::TreeFractal()
{

}

TreeFractal::~TreeFractal()
{

}

sf::Vector2f& TreeFractal::getStartLocation()
{
  return m_startLocation;
}


void TreeFractal::setStartLocation(sf::Vector2f& newStartLocation)
{
  m_startLocation = sf::Vector2f(newStartLocation);
}

float TreeFractal::getInitHeight()
{
  return m_initHeight;
}
void TreeFractal::setInitHeight(float newInitHeight)
{
  m_initHeight = newInitHeight;
}

float TreeFractal::getInitWidth()
{
  return m_initWidth;
}
void TreeFractal::setInitWidth(float newInitWidth)
{
  m_initWidth = newInitWidth;
}

void TreeFractal::setStartLocation(float x1, float y1)
{
  m_startLocation = sf::Vector2f(x1, y1);
}

int TreeFractal::getNumberOfIterations()
{
  return m_numberOfIterations;
}
void TreeFractal::setNumberOfIterations(int newNumberOfIterations)
{
  m_numberOfIterations = newNumberOfIterations;
}

float TreeFractal::getRightAngle()
{
  return m_rightAngle;
}
void TreeFractal::setRightAngle(float newRightAngle)
{
  m_rightAngle = newRightAngle;
}

float TreeFractal::getLeftAngle()
{
  return m_leftAngle;
}
void TreeFractal::setLeftAngle(float newLeftAngle)
{
  m_leftAngle = newLeftAngle;
}

void TreeFractal::setColor(const sf::Color& c)
{
  m_rootColor = sf::Color(c);
}

sf::Color& TreeFractal::getColor()
{
  return m_rootColor;
}
float TreeFractal::getScalingFactor()
{
  return m_scalingFactor;
}
void TreeFractal::setScalingFactor(float newScalingFactor)
{
  m_scalingFactor = newScalingFactor;
}

void TreeFractal::drawTreeFractal(int iteration, const sf::Vector2f& rootPosition, float rootRotation, sf::RenderWindow& window)
{
  if(m_numberOfIterations <= 1)
    return;

  if(iteration == m_numberOfIterations)
  {
    float scalingFactor = pow(m_scalingFactor, iteration);
    sf::CircleShape circle = sf::CircleShape(m_initWidth*scalingFactor*1.1);
    circle.setFillColor(sf::Color::White);

    circle.setPosition(sf::Vector2f(rootPosition.x-circle.getRadius(), rootPosition.y-circle.getRadius()));
    window.draw(circle);
    return;
  }

  float scalingFactor = pow(m_scalingFactor, iteration);
  sf::RectangleShape rect = sf::RectangleShape();

  float width=m_initWidth*scalingFactor;
  float height=m_initHeight*scalingFactor;

  rect.setSize(sf::Vector2f(width, height));
  sf::Color scaledColor = sf::Color(m_rootColor.r * scalingFactor, m_rootColor.g * scalingFactor, m_rootColor.b * scalingFactor);
  rect.setFillColor(scaledColor);
  rect.setRotation(rootRotation);
  rect.setPosition(rootPosition);
  window.draw(rect);

  float x = rootPosition.x - std::sin((rootRotation*M_PI)/180)*height;
  float y = rootPosition.y + std::cos((rootRotation*M_PI)/180)*height;

//  std::cout << rootPosition.x << " vs " << rootPosition.x + std::sin((rootRotation*M_PI)/180)*width << std::endl;
  drawTreeFractal(iteration+1, sf::Vector2f(x, y), rootRotation+m_leftAngle, window);
  drawTreeFractal(iteration+1, sf::Vector2f(x, y), rootRotation-m_rightAngle, window);
}

void TreeFractal::Render(sf::RenderWindow& window)
{
  sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(m_initWidth, m_initHeight));
  rect.setFillColor(m_rootColor);
  rect.setPosition(m_startLocation);
  rect.setRotation(180);

  float x = m_startLocation.x - std::sin((180*M_PI)/180) * m_initHeight;
  float y = m_startLocation.y + std::cos((180*M_PI)/180) * m_initHeight;

  window.draw(rect);
  drawTreeFractal(1, sf::Vector2f(x, y), 180 - m_leftAngle, window);
  drawTreeFractal(1, sf::Vector2f(x, y), 180 + m_rightAngle,window);
}
