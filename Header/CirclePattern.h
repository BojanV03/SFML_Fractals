#ifndef CIRCLEPATTERN_H
#define CIRCLEPATTERN_H
#include <SFML/Graphics.hpp>
#include <cmath>

void drawCircleFractal(const sf::Vector2f &topLeft, const sf::Vector2f &bottomRight,
  int numberOfIterations, sf::RenderWindow &window);

void circleFractal(const sf::Vector2f &topLeft, const sf::Vector2f &bottomRight,
  int currentIteration, int numberOfIterations, sf::RenderWindow &window);

#endif
