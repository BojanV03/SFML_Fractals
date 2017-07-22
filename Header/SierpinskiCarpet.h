#ifndef SIERPINSKICARPET_H
#define SIERPINSKICARPET_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Renderer.h"


class SierpinskiCarpet
{
public:
  SierpinskiCarpet();
  ~SierpinskiCarpet();
  void setNumberOfIterations(int newNumberOfIterations);
  int getNumberOfIterations() const;

  void setBoundingBox(const sf::RectangleShape& newBoundingBox);
  void setBoundingBox(const sf::Vector2f& topLeft, const sf::Vector2f& bottomRight);
  void setBoundingBox(float x1, float y1, float x2, float y2);
  sf::RectangleShape getBoundingBox() const;

  void setColor(const sf::Color& newColor);
  sf::Color getColor() const;


  /*
   *  Recursively calls itself for the top, left and right subtriangle and draws the final iteration
   */
  void drawSierpinskiCarpet(const sf::Vector2f &topLeftPoint, const sf::Vector2f &bottomRightPoint,
                      int iteration, sf::RenderWindow &window);

  void Render(sf::RenderWindow& window);
  /*
   * Wrapper function for easier calling, Generates the arguments for and calls the Sierpinski function
   */

  void setGridSize(int newGridSize);
  int getGridSize() const;

  void addSquareToSkip(int n);
  void clearSquaresToSkip();
  void removeSquareToSkip(int n);

private:
  sf::RectangleShape m_boundingBox;
  std::vector<int> m_squaresToSkip;
  int m_numberOfIterations;
  int m_gridSize;
  sf::Color m_color;
};

#endif
