interface.o: interface.cpp interface.h
	g++ -c -lncurses interface.cpp

player.o: player.cpp player.h interface.h
	g++ -c -lncurses player.cpp

main.o: main.cpp player.h interface.h
	g++ -c -lncurses player.cpp main.cpp 

main: main.o player.o interface.o
	g++ main.o player.o interface.o -lncurses -o main

clean:
	rm -f interface.o player.o main.o main

.PHONY: clean

