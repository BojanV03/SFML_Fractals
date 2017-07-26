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
#define WIDTH 1024
#define HEIGHT 1024

std::chrono::milliseconds prevFrame;
std::chrono::milliseconds currFrame;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    window.setFramerateLimit(30);
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
                std::cout << i << std::endl;
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
              {
                i--;
                std::cout << i << std::endl;
              }
            }
        }
        window.clear();

        Mandelbrot ml = Mandelbrot();
        ml.setBoundingBox(0, HEIGHT/2, WIDTH/2, HEIGHT);
        ml.setTopLeftReal(-2.1);
        ml.setTopLeftImaginary(1.3);
        ml.setBottomRightReal(1);
        ml.setBottomRightImaginary(-1.3);
  //      getchar();
    //    getchar();
    //    getchar();
    //    getchar();
    //    getchar();
  //      getchar();
        SierpinskiTriangle st = SierpinskiTriangle();
        st.setBoundingBox(0, 0, WIDTH/2, HEIGHT/2);
        st.setNumberOfIterations(i);
        st.setColor(sf::Color::Red);
        st.Render(window);


        KochSnowflake ks = KochSnowflake();
        ks.setBoundingBox(WIDTH/2, HEIGHT/2, WIDTH, HEIGHT);
        ks.setNumberOfIterations(i);
        ks.setColor(sf::Color::Red);
        ks.setInverted(false);
        ks.Render(window);

        SierpinskiCarpet sc = SierpinskiCarpet();
        sc.setBoundingBox(0, HEIGHT/2, WIDTH/2, HEIGHT);
        sc.setNumberOfIterations(i);
        sc.setColor(sf::Color::Blue);
        sc.setGridSize(3);
        sc.addSquareToSkip(4);
        sc.Render(window);
        ml.Render(window);
/*
        sc.setBoundingBox(WIDTH/2, 0, WIDTH, HEIGHT/2);
        sc.setGridSize(5);
        sc.clearSquaresToSkip();
        sc.addSquareToSkip(6);
        sc.addSquareToSkip(7);
        sc.addSquareToSkip(8);
        sc.addSquareToSkip(11);
        sc.addSquareToSkip(13);
        sc.addSquareToSkip(16);
        sc.addSquareToSkip(17);
        sc.addSquareToSkip(18);
        sc.Render(window);
*/
/*
        TreeFractal tf = TreeFractal();
        tf.setStartLocation(WIDTH/2, HEIGHT-100);
        tf.setLeftAngle(30);
        tf.setRightAngle(13);
        tf.setNumberOfIterations(i);
        tf.setInitWidth(16);
        tf.setInitHeight(128);
        sf::Color brown = sf::Color(70,190,63);
        tf.setColor(brown);
        tf.setScalingFactor(0.88);
        tf.Render(window);
*/
//        drawKochSnowflake(sf::Vector2f(0, 0), sf::Vector2f(WIDTH, HEIGHT), i, true, window);
//        drawKochSnowflake(sf::Vector2f(0, 0), sf::Vector2f(WIDTH, HEIGHT), i, falce, window);

/*
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
*/
//        drawSierpinskiTriangle(sf::Vector2f(0, 0), sf::Vector2f(WIDTH, HEIGHT), i, window);
  //      std::this_thread::sleep_for(std::chrono::milliseconds(1000));

       // Animated iterations for Sierpinski Triangle
  //     drawCircleFractal(sf::Vector2f(0, 0), sf::Vector2f(WIDTH, HEIGHT), i, window);
  //     std::this_thread::sleep_for(std::chrono::milliseconds(500));

        window.display();
//        std::cout << currFrame.count() - prevFrame.count() << std::endl;
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
