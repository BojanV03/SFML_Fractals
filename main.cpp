#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include "Header/Renderer.h"
#include "Header/Sierpinski.h"
#include "Header/CircleFractal.h"
#define WIDTH 800
#define HEIGHT 800

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    int i = 0;
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
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
              {
                i--;
              }
            }
        }
        window.clear();
        /*// Animated iterations for Sierpinski Triangle
       drawSierpinski(sf::Vector2f(0, 0), sf::Vector2f(WIDTH, HEIGHT), i= (i+1 == 10? 0 : i+1), window);
       std::this_thread::sleep_for(std::chrono::milliseconds(500));
*/
       // Animated iterations for Sierpinski Triangle
       drawCircleFractal(sf::Vector2f(0, 0), sf::Vector2f(WIDTH, HEIGHT), i, window);
  //     std::this_thread::sleep_for(std::chrono::milliseconds(500));

        window.display();
    }

    return 0;
}





/*
  Program in C
  Program in C
  Pointers assembly
  manage your memory
  with malloc and free()
*/
