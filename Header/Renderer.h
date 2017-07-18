#ifndef RENDERER_H
#define RENDERER_H
#include <SFML/Graphics.hpp>
/*
 *  Draws a triangle from the given points
 */
void drawTriangle(const sf::Vector2f &top, const sf::Vector2f &left, const sf::Vector2f &right, const sf::Color &color,  sf::RenderWindow &window);
#endif
