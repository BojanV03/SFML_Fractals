#include "../Header/Mandelbrot.h"

/*
 * Moves the render area by the ammount directly proportional to users mouse movement
 */
void Mandelbrot::move(const sf::Vector2i& vector)
{
  double x = vector.x * (m_bottomRightReal - m_topLeftReal)/m_image.getSize().x;
  double y = vector.y * (m_topLeftImaginary - m_bottomRightImaginary)/m_image.getSize().y;

  m_topLeftReal -= x;
  m_bottomRightReal -= x;
  m_topLeftImaginary -= y;
  m_bottomRightImaginary -= y;
  std::cout << "Panned by (" << -x << ", " << -y << "). TopLeft = " << m_topLeftReal << " + " << m_topLeftImaginary << "i; bottomRight = " << m_bottomRightReal << " + " << m_bottomRightImaginary << std::endl;

}

/*
 * Zooms into the selected range
 */
void Mandelbrot::zoom(const sf::Vector2i& vector, int zoomAmount)
{
  double diffX = (m_bottomRightReal - m_topLeftReal)/m_image.getSize().x;
  double diffY = (m_topLeftImaginary - m_bottomRightImaginary)/m_image.getSize().y;

  double scaleFactor;

  if(zoomAmount < 0)
    scaleFactor = 1.0/((double)std::pow(0.85, std::abs(zoomAmount))*20);
  else
    scaleFactor = (double)std::pow(0.85, std::abs(zoomAmount))*10;

  double newDiffX = diffX*scaleFactor;
  double newDiffY = diffY*scaleFactor;

  if(newDiffX < std::pow(0.1, 15) || newDiffY < std::pow(0.1, 15))
    return;

  m_topLeftReal += (newDiffX-diffX);
  m_topLeftImaginary -= (newDiffY-diffY);
  m_bottomRightReal -= (newDiffX-diffX);
  m_bottomRightImaginary += (newDiffY-diffY);

  std::cout << "Zoomed in by 1. TopLeft = " << m_topLeftReal << " + " << m_topLeftImaginary << "i; bottomRight = " << m_bottomRightReal << " + " << m_bottomRightImaginary << std::endl;
}


void Mandelbrot::UpdateImageOptimized(int numberOfIterations) //-O3 flag friendly, use it!
{
  // No need to reRender if nothing has changed
  if(m_topLeftReal != m_prevTopLeftReal || m_topLeftImaginary != m_prevTopLeftImaginary
  || m_bottomRightReal != m_prevBottomRightReal || m_bottomRightImaginary != m_prevBottomRightImaginary)
  {
    // Converts the Width in pixels to the width in real numbers proportional to the render area range
    double differenceX = (m_bottomRightReal - m_topLeftReal)/m_image.getSize().x;
    // Same with height
    double differenceY = (m_topLeftImaginary - m_bottomRightImaginary)/m_image.getSize().y;
    double x = m_bottomRightReal;
    double x1, y1, tmp, y, x2, y2;
    int iterator;

    for(int i = m_image.getSize().x-1; i != 0 ; i--)
    {
      double y = m_topLeftImaginary;

      for(int j = m_image.getSize().y-1; j != 0 ; j--)
      {
        x1 = y1 = iterator = 0;

        // Apply the mandelbrot function to it numberOfIteration times or until the |z| goes above 2
        while(iterator <= numberOfIterations && (x1*x1)+(y1*y1) < 4)
        {
          tmp = x1*x1 - y1*y1 + x;
          iterator++;
          y1 = 2 * x1 * y1 + y;
          x1 = tmp;
        }
        // Adjust the pixel color based on the number of iterations
        m_image.setPixel(i, j, sf::Color((iterator%256), (iterator/256)%256, (iterator/65536)%256));
        y -= differenceY;
      }
      x -= differenceX;
    } // Update the prev Variables in order to possibly skip unneeded renders in the future
    m_prevTopLeftReal = m_topLeftReal;
    m_prevTopLeftImaginary = m_topLeftImaginary;
    m_prevBottomRightReal = m_bottomRightReal;
    m_prevBottomRightImaginary = m_bottomRightImaginary;
  }
  else
  {

  }
}

/*
 * Renders the currently selected range with the desired width/height and saves it as a .png picture
 * Logic is equivalent to the UpdateImageOptimized function with a few prints added
 */
void Mandelbrot::saveImage(const std::string& fileName, int numberOfIterations, int width, int height)
{
  // We'll want to return to the previous size once we're done
  int prevWidth = m_boundingBox.getSize().x;
  int prevHeight = m_boundingBox.getSize().y;
  setBoundingBox(0, 0, width, height);


  double differenceX = (m_bottomRightReal - m_topLeftReal)/m_image.getSize().x;
  double differenceY = (m_topLeftImaginary - m_bottomRightImaginary)/m_image.getSize().y;
  double x = m_bottomRightReal;
  double x1, y1, tmp, y, x2, y2;
  int iterator;

  // Used for calculating the remaining time
  std::chrono::milliseconds currIter = std::chrono::duration_cast <std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
  std::chrono::milliseconds prevIter = currIter;

  double elapsedTime = 0;

  for(int i = m_image.getSize().x-1; i != 0 ; i--)
  {
    double y = m_topLeftImaginary;

    for(int j = m_image.getSize().y-1; j != 0 ; j--)
    {
      x1 = y1 = iterator = 0;

      while(iterator <= numberOfIterations && (x1*x1)+(y1*y1) < 4)
      {
        tmp = x1*x1 - y1*y1 + x;
        iterator++;
        y1 = 2 * x1 * y1 + y;
        x1 = tmp;
      }
      m_image.setPixel(i, j, sf::Color((iterator%256), (iterator/256)%256, ((iterator/65536)%256)));
      y -= differenceY;
    }
    // Get current time
    std::chrono::milliseconds currIter = std::chrono::duration_cast <std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    double deltaTime = (currIter.count() - prevIter.count());
    elapsedTime += deltaTime;
    int ETA = ((elapsedTime / (m_image.getSize().x-i))/1000.0) * (double) m_image.getSize().x - elapsedTime/1000.0;

    // Refresh the terminal and print updated status on it
    system("clear");
    std::cout <<  m_image.getSize().x-i << " / " << m_image.getSize().x << " = " << 100*(double)(m_image.getSize().x-i)/(double)m_image.getSize().x << "% done." << std::endl;
    std::cout << "Delta time: " << deltaTime/1000.0 << "s" << std::endl;
    std::cout << "Elapsed time: " << elapsedTime/1000 << "s" << std::endl;

    prevIter = currIter;
    prettyPrintTime("ETA Based on all iterations so far: ", ETA);
    ETA = (deltaTime * i)/1000.0;
    std::cout << std::endl;
    prettyPrintTime("ETA Based on last iteration: ", ETA);

    std::cout << std::endl << "************************************" << std::endl;

    x -= differenceX;
  }
  if(m_image.saveToFile(fileName) == true)
  {
    std::cout << fileName << " saved successfully" << std::endl;
  }

  setBoundingBox(0, 0, prevWidth, prevHeight);
}

void Mandelbrot::prettyPrintTime(const std::string &prefix, int seconds)
{
    if(seconds)
    {
      std::cout << prefix;
    }
    if(seconds / NUM_OF_SECS_YEAR)
    {
      std::cout << seconds / NUM_OF_SECS_YEAR << " years ";
    }
    if((seconds%NUM_OF_SECS_YEAR) / NUM_OF_SECS_DAY)
    {
      std::cout << (seconds%NUM_OF_SECS_YEAR) / NUM_OF_SECS_DAY << " days ";
    }
    if((seconds%NUM_OF_SECS_DAY) / NUM_OF_SECS_HOUR)
    {
      std::cout << (seconds%NUM_OF_SECS_DAY) / NUM_OF_SECS_HOUR << " hours ";
    }
    if((seconds%NUM_OF_SECS_HOUR) / NUM_OF_SECS_MINUTE)
    {
      std::cout << (seconds%NUM_OF_SECS_HOUR) / NUM_OF_SECS_MINUTE << " minutes ";
    }
    if(seconds%NUM_OF_SECS_MINUTE)
    {
      std::cout << seconds%NUM_OF_SECS_MINUTE << " seconds";
    }
}

// No need to use this, use the optimized function
void Mandelbrot::UpdateImage()
{
  if(m_topLeftReal != m_prevTopLeftReal || m_topLeftImaginary != m_prevTopLeftImaginary
  || m_bottomRightReal == m_prevBottomRightReal || m_bottomRightImaginary != m_prevBottomRightImaginary)
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

        while(iterator < 256 && std::sqrt((x1*x1)+(y1*y1) < 2))
        {
          iterator++;
          double tmp = (x1 * x1) - (y1 * y1) + x;
          y1 = 2 * x1 * y1 + y;
          x1 = tmp;
        }

        m_image.setPixel(i, j, sf::Color(iterator, 0, 0));
        y += differenceY;
      }
      x += differenceX;
    }
    m_prevTopLeftReal = m_topLeftReal;
    m_prevTopLeftImaginary = m_topLeftImaginary;
    m_prevBottomRightReal = m_bottomRightReal;
    m_prevBottomRightImaginary = m_bottomRightImaginary;
  }
  else
  {
  }

}

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

double Mandelbrot::getTopLeftReal()
{
  return m_topLeftReal;
}
void Mandelbrot::setTopLeftReal(double newTopLeftReal)
{
  m_topLeftReal = newTopLeftReal;
}

double Mandelbrot::getTopLeftImaginary()
{
  return m_topLeftImaginary;
}
void Mandelbrot::setTopLeftImaginary(double newTopLeftIm)
{
  m_topLeftImaginary = newTopLeftIm;
}

double Mandelbrot::getBottomRightReal()
{
  return m_bottomRightReal;
}
void Mandelbrot::setBottomRightReal(double newBottomRightReal)
{
  m_bottomRightReal = newBottomRightReal;
}

double Mandelbrot::getBottomRightImaginary()
{
  return m_bottomRightImaginary;
}
void Mandelbrot::setBottomRightImaginary(double newBottomRightIm)
{
  m_bottomRightImaginary = newBottomRightIm;
}

void Mandelbrot::Render(sf::RenderWindow& window)
{
  UpdateImageOptimized(256);
  sf::Texture tex;
  tex.loadFromImage(m_image);
  m_sprite.setTexture(tex);
  window.draw(m_sprite);
}
