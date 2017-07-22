#ifndef CIRCLEPATTERN_H
#define CIRCLEPATTERN_H
#include <SFML/Graphics.hpp>
#include <cmath>


class CirclePattern
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

  void drawCircleFractal(const sf::Vector2f &topLeft, const sf::Vector2f &bottomRight,
  int currentIteration, int numberOfIterations, sf::RenderWindow &window);
  void Render(sf::RenderWindow& window);

private:
  int m_numberOfIterations;
  sf::RectangleShape m_boundingBox;
  sf::Color m_color;
};

#endif
