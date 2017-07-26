exec.out: main.o TreeFractal.o Mandelbrot.o SierpinskiTriangle.o SierpinskiCarpet.o Renderer.o CirclePattern.o KochSnowflake.o
	g++ *.o -o exec.out -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp

Mandelbrot.o: Source/Mandelbrot.cpp Header/Mandelbrot.h
	g++ -c Source/Mandelbrot.cpp

TreeFractal.o: Source/TreeFractal.cpp Header/TreeFractal.h
	g++ -c Source/TreeFractal.cpp

KochSnowflake.o: Source/KochSnowflake.cpp Header/KochSnowflake.h
	g++ -c Source/KochSnowflake.cpp

SierpinskiCarpet.o: Source/SierpinskiCarpet.cpp Header/SierpinskiCarpet.h
	g++ -c Source/SierpinskiCarpet.cpp

SierpinskiTriangle.o: Source/SierpinskiTriangle.cpp Header/SierpinskiTriangle.h
	g++ -c Source/SierpinskiTriangle.cpp

Renderer.o: Source/Renderer.cpp Header/Renderer.h
	g++ -c Source/Renderer.cpp

CirclePattern.o: Source/CirclePattern.cpp Header/CirclePattern.h
	g++ -c Source/CirclePattern.cpp
