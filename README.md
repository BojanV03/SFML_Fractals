# SFML_Fractals
I was bored and decided that I'd like to play with Fractals. I was mainly interested in the algorithmic part of it so there is no fancy UI here.

## :computer: Setup

This version is mainly tested on Ubuntu.

### Prerequisites

1. **Install g++**

$ sudo apt-get update
$ sudo apt-get install g++

2. **Install SFML library**

There are three ways to install SFML library:

* Using package manager

$ sudo apt-get install libsfml-dev

* Download the SDK

Download the SDK from the [download page](https://www.sfml-dev.org/download.php), unpack it and copy the files to your preferred location: either a separate path in your personal folder (like /home/me/sfml), or a standard path (like /usr/local).

* Building SFML yourself

If you want to go this way, there's a [dedicated tutorial](https://www.sfml-dev.org/tutorials/2.0/compile-with-cmake.php) on building SFML yourself.

## :wrench: Setup and run the game

1. Download (clone) this repository
2. In main.cpp, define the desired fractal preset you want to see
3. Type 'make' in your terminal (without quotes)
4. Type './exec.out' in your terminal (again, without quotes)
5. Enjoy the fractals

# Here's some screenshots:
## Mandelbrot fractal:
Check out the renderer in action:

  https://www.youtube.com/edit?o=U&video_id=95CqTifr_NE


![Mandelbrot Fractal Render](http://tobechangedverysoon "Mandelbrot Fractal Render")


## Sierpinski Triangle:
![Sierpinski Triangle Animation](http://i.imgur.com/bBITqav.gif "Sierpinski Triangle Animation")

##Sierpinski Carpet:
![Sierpinski Carpet Animation](http://tobechangedverysoon "Sierpinski Carpet Animation")
![Sierpinski Carpet 5x5](http://tobechangedverysoon "Sierpinski Carpet 5x5")
![Sierpinski Carpet Snowflake](http://tobechangedverysoon "Sierpinski Carpet 5x5")

##Tree Fractal:
![Tree Fractal Animation](http://tobechangedverysoon "Tree Fractal Animation")

##Koch Snowflake:
![Koch Snowflake Animation](http://tobechangedverysoon "Koch Snowflake Animation")
