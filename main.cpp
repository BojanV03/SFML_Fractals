#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include "Header/Renderer.h"
#include "Header/SierpinskiTriangle.h"
#include "Header/SierpinskiCarpet.h"
#include "Header/CirclePattern.h"
#include "Header/KochSnowflake.h"
#include "Header/TreeFractal.h"
#include "Header/Mandelbrot.h"

// define what preset you want to draw, _MANDELBROT, _TRIANGLE, _CARPET, _KOCH, _TREE
#define _MANDELBROT

// Mandelbrot has a preview mode because the Rendering is much more demanging. Use "S" to render the image in desired resolution
#ifdef _MANDELBROT
  #define WIDTH 400
  #define HEIGHT 400
#else
  #define WIDTH 1024
  #define HEIGHT 1024
#endif

// used for calculating delta time
std::chrono::milliseconds prevFrame;
std::chrono::milliseconds currFrame;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot!");

    // for calculating the distance between the mouse button click location and release location, for mandelbrot movement
    sf::Vector2f previousMousePosition;
    window.setFramerateLimit(30);
    int i = 0;  // Number of iterations of the selected fractal

    #ifdef _MANDELBROT
      Mandelbrot ml = Mandelbrot();
      ml.setBoundingBox(0, 0, WIDTH, HEIGHT);
      ml.setTopLeftReal(-2.1);
      ml.setTopLeftImaginary(1.8);
      ml.setBottomRightReal(1);
      ml.setBottomRightImaginary(-1.3);
      ml.Render(window);
    #endif

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
              {
                window.close();
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
              {
                i++;
                std::cout << i << std::endl;
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
              {
                i--;
                std::cout << i << std::endl;
              }
              #ifdef _MANDELBROT
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))  // Render mandelbrot and save to file
                {
                  int w, h;
                  std::cout << std::endl << std::endl << "*****************************************" << std::endl;
                  std::cout <<"input the desired resolution of the rendered image (width height): ";
                  std::cin >> w;
                  std::cin >> h;
                  ml.saveImage("MandelbrotTest.png", 65536, w, h);
                }
              #endif
          }
          #ifdef _MANDELBROT
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                previousMousePosition.x = sf::Mouse::getPosition(window).x;
                previousMousePosition.y = sf::Mouse::getPosition(window).y;
            }
            else if(event.type == sf::Event::MouseButtonReleased) // Pan mandelbrot
            {
              sf::Vector2i movedBy(sf::Mouse::getPosition(window).x - previousMousePosition.x, sf::Mouse::getPosition(window).y - previousMousePosition.y);
              ml.move(movedBy);
              previousMousePosition.x = sf::Mouse::getPosition(window).x;
              previousMousePosition.y = sf::Mouse::getPosition(window).y;
              window.clear();
            }
          if (event.type == sf::Event::MouseWheelMoved) // Zoom mandelbrot
          {
              int zoomDelta = event.mouseWheel.delta;
              ml.zoom(sf::Mouse::getPosition(window), zoomDelta);
          }
          #endif

        }
        window.clear();
        #ifdef _MANDELBROT
          ml.Render(window);
          sf::CircleShape cs(4);
          cs.setFillColor(sf::Color::White);
          cs.setPosition(WIDTH/2-2, HEIGHT/2-2);
          window.draw(cs);
        #endif

        #ifdef _TRIANGLE
          SierpinskiTriangle st = SierpinskiTriangle();
          st.setBoundingBox(0, 0, WIDTH, HEIGHT);
          st.setNumberOfIterations(i);
          st.setColor(sf::Color::Red);
          st.Render(window);
        #endif

        #ifdef _KOCH
          KochSnowflake ks = KochSnowflake();
          ks.setBoundingBox(0, 0, WIDTH, HEIGHT);
          ks.setNumberOfIterations(i);
          ks.setColor(sf::Color::Red);
          ks.setInverted(false);
          ks.Render(window);
        #endif

        #ifdef _CARPET
          SierpinskiCarpet sc = SierpinskiCarpet();
          sc.setBoundingBox(0, 0, WIDTH, HEIGHT);
          sc.setNumberOfIterations(i);
          sc.setColor(sf::Color::Red);
          sc.setGridSize(3);
          sc.addSquareToSkip(4);
          sc.Render(window);
        #endif

        #ifdef _TREE
          TreeFractal tf = TreeFractal();
          tf.setStartLocation(WIDTH/2, HEIGHT-100);
          tf.setLeftAngle(30);
          tf.setRightAngle(17);
          tf.setNumberOfIterations(i);
          tf.setInitWidth(12);
          tf.setInitHeight(96);
          sf::Color brown = sf::Color(70,190,63);
          tf.setColor(brown);
          tf.setScalingFactor(0.88);
          tf.Render(window);
        #endif

        window.display();
//        std::cout << currFrame.count() - prevFrame.count() << std::endl;

  //      std::cout << currFrame.count() - prevFrame.count() << std::endl;
        prevFrame = currFrame;
        currFrame = std::chrono::duration_cast <std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    }

    return 0;
}
