#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <chrono>

#define NUM_OF_SECS_YEAR (31556926)
#define NUM_OF_SECS_DAY (86400)
#define NUM_OF_SECS_HOUR (3600)
#define NUM_OF_SECS_MINUTE (60)
class Mandelbrot
{
public:

  void setBoundingBox(const sf::RectangleShape& newBoundingBox);
  void setBoundingBox(const sf::Vector2f& topLeft, const sf::Vector2f& bottomRight);
  void setBoundingBox(float x1, float y1, float x2, float y2);
  sf::RectangleShape getBoundingBox() const;

  void move(const sf::Vector2i& vector);
  void zoom(const sf::Vector2i& vector, int zoomAmount);

  double getTopLeftReal();
  void setTopLeftReal(double newTopLeftReal);

  double getTopLeftImaginary();
  void setTopLeftImaginary(double newTopLeftIm);

  double getBottomRightReal();
  void setBottomRightReal(double newBottomRightReal);

  double getBottomRightImaginary();
  void setBottomRightImaginary(double newBottomRightIm);

  void setRenderRange(double topLeftReal, double topLeftIm, double bottomRightReal, double bottomRightIm);

  void Render(sf::RenderWindow& window);
  void UpdateImage();
  void UpdateImageOptimized(int numberOfIterations);

  void finePrintTime(const std::string& prefix, int ETA);
  void saveImage(const std::string& fileName, int numberOfIterations, int width, int height);

private:
  void setImageBounds();
  double m_topLeftReal, m_topLeftImaginary, m_bottomRightReal, m_bottomRightImaginary;
  double m_prevTopLeftReal, m_prevTopLeftImaginary, m_prevBottomRightReal, m_prevBottomRightImaginary;
  sf::RectangleShape m_boundingBox;
  sf::Image m_image;
  sf::Sprite m_sprite;
};

#endif
