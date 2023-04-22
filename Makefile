player.o: player.cpp player.h
	g++ -c player.cpp

main.o: main.cpp player.h interface.h
	g++ -c -lncurses player.cpp main.cpp 

main: main.o player.o
	g++ main.o player.o -lncurses -o main

clean:
	rm -f player.o main.o main

.PHONY: clean

