#ifndef KOCHSNOWFLAKE_H
#define KOCHSNOWFLAKE_H
#define M_SQRT3 1.73205080757
#define ONE_THIRD 0.33333333333
#define TWO_THIRDS 0.66666666666
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Renderer.h"
void drawKochSnowflake(sf::Vector2f topLeft, sf::Vector2f bottomRight,
    int numberOfIterations, bool inverted, sf::RenderWindow& window);

void KochSnowflake(sf::Vector2f pointA, sf::Vector2f pointB,
    int currentIteration, int numberOfIterations, bool inverted, sf::RenderWindow& window);

float TriangleHeight(sf::Vector2f& pointA, sf::Vector2f& pointB);
sf::Vector2f CenterPoint(sf::Vector2f& pointA, sf::Vector2f& pointB);
sf::Vector2f TopPoint(sf::Vector2f& pointA, sf::Vector2f& pointB);
sf::Vector2f UnitVector(sf::Vector2f&);

#endif
