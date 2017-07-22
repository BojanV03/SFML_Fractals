#ifndef KOCHSNOWFLAKE_H
#define KOCHSNOWFLAKE_H

#define M_SQRT3 1.73205080757
#define ONE_THIRD 0.33333333333
#define TWO_THIRDS 0.66666666666

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Renderer.h"


float TriangleHeight(sf::Vector2f& pointA, sf::Vector2f& pointB);
sf::Vector2f CenterPoint(sf::Vector2f& pointA, sf::Vector2f& pointB);
sf::Vector2f TopPoint(sf::Vector2f& pointA, sf::Vector2f& pointB);
sf::Vector2f UnitVector(sf::Vector2f&);

class KochSnowflake
{
public:
  void setNumberOfIterations(int newNumberOfIterations);
  int getNumberOfIterations() const;

  void setBoundingBox(const sf::RectangleShape& newBoundingBox);
  void setBoundingBox(const sf::Vector2f& topLeft, const sf::Vector2f& bottomRight);
  void setBoundingBox(float x1, float y1, float x2, float y2);
  sf::RectangleShape getBoundingBox() const;

  void setColor(const sf::Color& newColor);
  sf::Color getColor() const;

  void setInverted(bool newInverted);
  bool getInverted() const;

  void drawKochSnowflake(sf::Vector2f pointA, sf::Vector2f pointB,
      int currentIteration, int numberOfIterations, bool inverted, sf::RenderWindow& window);
  void Render(sf::RenderWindow& window);
private:
  sf::RectangleShape m_boundingBox;
  int m_numberOfIterations;
  sf::Color m_color;
  bool m_inverted;
};

#endif
