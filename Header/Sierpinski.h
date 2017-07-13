#ifndef SIERPINSKI_H
#define SIERPINSKI_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Renderer.h"

/*
 * Wrapper function for easier calling, Generates the arguments for and calls the Sierpinski function
 */
void drawSierpinskiTriangle(const sf::Vector2f &topLeftPoint, const sf::Vector2f &bottomRightPoint, int numberOfIterations, sf::RenderWindow &window);
/*
 *  Recursively calls itself for the top, left and right subtriangle and draws the final iteration
 */
void SierpinskiTriangle(const sf::Vector2f &top, const sf::Vector2f &left, const sf::Vector2f &right,
                    int iteration, int numberOfIterations, sf::RenderWindow &window);

/*
 * Wrapper function for easier calling, Generates the arguments for and calls the Sierpinski function
 */
void drawSierpinskiCarpet(const sf::Vector2f &topLeftPoint, const sf::Vector2f &bottomRightPoint,
  const std::vector<int> &squaresToSkip, int gridSize, int numberOfIterations, sf::RenderWindow &window);
/*
 *  Recursively calls itself for the top, left and right subtriangle and draws the final iteration
 */
void SierpinskiCarpet(const sf::Vector2f &topLeftPoint, const sf::Vector2f &bottomRightPoint,
                    const std::vector<int> &squaresToSkip, int gridSize, int iteration, int numberOfIterations, sf::RenderWindow &window);
#endif
