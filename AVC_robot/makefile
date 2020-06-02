INCLUDE = -I F:\Coding\C++_Projects\Project3\SFML\include
LIBS = -L F:\Coding\C++_Projects\Project3\SFML\lib 
robot.exe: robot.o 
	g++ $(LIBS) -o robot robot.o -lsfml-window  -lsfml-graphics -lsfml-system -lsfml-network 
robot.o: robot.cpp 
	g++  -c $(INCLUDE) robot.cpp 


