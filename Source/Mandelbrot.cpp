#include "../Header/Mandelbrot.h"

void Mandelbrot::setRenderRange(double topLeftReal, double topLeftIm, double bottomRightReal, double bottomRightIm)
{
  m_topLeftReal = topLeftReal;
  m_topLeftImaginary = topLeftIm;
  m_bottomRightReal = bottomRightReal;
  m_bottomRightImaginary = bottomRightIm;
}
void Mandelbrot::setBoundingBox(const sf::RectangleShape& newBoundingBox)
{
  m_boundingBox = sf::RectangleShape(newBoundingBox);
  setImageBounds();
}
void Mandelbrot::setBoundingBox(const sf::Vector2f& topLeft, const sf::Vector2f& bottomRight)
{
  m_boundingBox = sf::RectangleShape();
  m_boundingBox.setPosition(topLeft);
  m_boundingBox.setSize(sf::Vector2f(bottomRight.x-topLeft.x, bottomRight.y-topLeft.y));
  setImageBounds();
}
void Mandelbrot::setBoundingBox(float x1, float y1, float x2, float y2)
{
  m_boundingBox = sf::RectangleShape();
  m_boundingBox.setPosition(sf::Vector2f(x1, y1));
  m_boundingBox.setSize(sf::Vector2f(x2 - x1, y2 - y1));
  setImageBounds();
}

sf::RectangleShape Mandelbrot::getBoundingBox() const
{
  return m_boundingBox;
}

void Mandelbrot::setImageBounds()
{
  m_image.create(m_boundingBox.getSize().x, m_boundingBox.getSize().y, sf::Color::Black);
  m_sprite.setPosition(m_boundingBox.getPosition().x, m_boundingBox.getPosition().y);
}

void Mandelbrot::UpdateImage()
{
  if(m_topLeftReal != m_prevTopLeftReal || m_topLeftImaginary != m_prevTopLeftImaginary
  || m_bottomRightReal != m_prevBottomRightReal || m_bottomRightImaginary != m_prevBottomRightImaginary)
  {
    double differenceX = (m_bottomRightReal - m_topLeftReal)/m_image.getSize().x;
    double differenceY = (m_topLeftImaginary - m_bottomRightImaginary)/m_image.getSize().y;
    double x = m_topLeftReal;

    for(int i = 0; i < m_image.getSize().x; i++)
    {
      double y = m_bottomRightImaginary;
      for(int j = 0; j < m_image.getSize().y; j++)
      {
        double x1, y1, iterator;
        x1 = y1 = iterator = 0;

        while(iterator < 255 && std::sqrt((x1*x1)+(y1*y1) < 2))
        {
          iterator++;
          double tmp = (x1 * x1) - (y1 * y1) + x;
          y1 = 2 * x1 * y1 + y;
          x1 = tmp;
        }

        m_image.setPixel(i, j, sf::Color(255-iterator, 0, 0));
        y += differenceY;
      }
      x += differenceX;
    }
    m_prevTopLeftReal = m_topLeftReal;
    m_prevTopLeftImaginary = m_topLeftImaginary;
    m_prevBottomRightReal = m_bottomRightReal;
    m_prevBottomRightImaginary = m_bottomRightImaginary;
  }
}

double Mandelbrot::getTopLeftReal()
{
  return m_topLeftReal;
}
void Mandelbrot::setTopLeftReal(double newTopLeftReal)
{
  m_topLeftReal = newTopLeftReal;
  UpdateImage();
}

double Mandelbrot::getTopLeftImaginary()
{
  return m_topLeftImaginary;
}
void Mandelbrot::setTopLeftImaginary(double newTopLeftIm)
{
  m_topLeftImaginary = newTopLeftIm;
  UpdateImage();
}

double Mandelbrot::getBottomRightReal()
{
  return m_bottomRightReal;
}
void Mandelbrot::setBottomRightReal(double newBottomRightReal)
{
  m_bottomRightReal = newBottomRightReal;
  UpdateImage();
}

double Mandelbrot::getBottomRightImaginary()
{
  return m_bottomRightImaginary;
}
void Mandelbrot::setBottomRightImaginary(double newBottomRightIm)
{
  m_bottomRightImaginary = newBottomRightIm;
  UpdateImage();
}

void Mandelbrot::Render(sf::RenderWindow& window)
{
  sf::Texture tex;
  tex.loadFromImage(m_image);
  m_sprite.setTexture(tex);



  window.draw(m_sprite);
}
