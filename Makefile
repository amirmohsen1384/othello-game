CC=x86_64-w64-mingw32-g++
APP=othello.exe

all: main

main: coordinates.o game.o point.o render.o system.o table.o text.o io.o commands.o match.o
	$(CC) -o $(APP) *.o main.cpp

coordinates.o:
	$(CC) -o coordinates.o -c src/coordinates.cpp

game.o:
	$(CC) -o game.o -c src/game.cpp

match.o:
	$(CC) -o match.o -c src/match.cpp
	
render.o:
	$(CC) -o render.o -c src/render.cpp

system.o:
	$(CC) -o system.o -c src/system.cpp

table.o:
	$(CC) -o table.o -c src/table.cpp

text.o:
	$(CC) -o text.o -c src/text.cpp

point.o:
	$(CC) -o point.o -c src/point.cpp

io.o:
	$(CC) -o io.o -c src/io.cpp

commands.o:
	$(CC) -o commands.o -c src/commands.cpp

match.o:
	$(CC) -o match.o -c src/match.cpp

clean:
	@rm *.o
	@rm $(APP)