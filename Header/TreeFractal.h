#ifndef TREEFRACTAL_H
#define TREEFRACTAL_H
#include <SFML/Graphics.hpp>
#include <iostream>

class TreeFractal
{
public:
  TreeFractal();
  ~TreeFractal();

  void setStartLocation(sf::Vector2f& newLocation);
  void setStartLocation(float x, float y);
  sf::Vector2f& getStartLocation();

  float getInitHeight();
  void setInitHeight(float newInitHeight);

  float getInitWidth();
  void setInitWidth(float newInitWidth);

  int getNumberOfIterations();
  void setNumberOfIterations(int newNumberOfIterations);

  float getRightAngle();
  void setRightAngle(float newRightAngle);

  float getLeftAngle();
  void setLeftAngle(float newLeftAngle);

  void Render(sf::RenderWindow& window);

  void drawTreeFractal(int iteration, const sf::Vector2f& rootPosition, float rootRotation, sf::RenderWindow& window);

  float getScalingFactor();
  void setScalingFactor(float newScalingFactor);

  void setColor(const sf::Color& c);
  sf::Color& getColor();

private:
  sf::Color m_rootColor;
  sf::Vector2f m_startLocation;
  int m_numberOfIterations;
  float m_leftAngle;
  float m_rightAngle;
  float m_initHeight;
  float m_initWidth;
  float m_scalingFactor;
};

#endif
