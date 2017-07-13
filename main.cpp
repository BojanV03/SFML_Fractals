#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include "Header/Renderer.h"
#include "Header/Sierpinski.h"
#include "Header/CirclePattern.h"
#define WIDTH 1050
#define HEIGHT 1050

std::chrono::milliseconds prevFrame;
std::chrono::milliseconds currFrame;
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

        // Animated iterations for Sierpinski Triangle
        std::vector<int> skipping;
        skipping.push_back(6);
        skipping.push_back(7);
        skipping.push_back(8);
        skipping.push_back(11);
        skipping.push_back(13);
        skipping.push_back(16);
        skipping.push_back(17);
        skipping.push_back(18);
        drawSierpinskiCarpet(sf::Vector2f(0, 0), sf::Vector2f(WIDTH, HEIGHT), skipping, 5, i, window);

//        drawSierpinskiTriangle(sf::Vector2f(0, 0), sf::Vector2f(WIDTH, HEIGHT), i, window);
  //      std::this_thread::sleep_for(std::chrono::milliseconds(1000));

       // Animated iterations for Sierpinski Triangle
  //     drawCircleFractal(sf::Vector2f(0, 0), sf::Vector2f(WIDTH, HEIGHT), i, window);
  //     std::this_thread::sleep_for(std::chrono::milliseconds(500));

        window.display();
        std::cout << currFrame.count() - prevFrame.count() << std::endl;
        prevFrame = currFrame;
        currFrame = std::chrono::duration_cast <std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
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
