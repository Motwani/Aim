all: 
	g++ -o Aim game.cpp glad.c -lGL -lglfw -L/usr/local/lib -ldl
