INCLUDE = -I F:\Coding\C++_Projects\Project3\SFML\include
LIBS = -L F:\Coding\C++_Projects\Project3\SFML\lib 
server3.exe: server3.o 
	g++ $(LIBS) -o server3 server3.o -lsfml-window  -lsfml-graphics -lsfml-system -lsfml-network 
server3.o: server3.cpp 
	g++  -c $(INCLUDE) server3.cpp 


