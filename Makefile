interface.o: interface.cpp interface.h
	g++ -c -lncurses interface.cpp

item.o: item.cpp item.h
	g++ -c item.cpp

player.o: player.cpp player.h interface.h item.h
	g++ -c -lncurses player.cpp

event.o: event.cpp event.h player.h
	g++ -c -lncurses event.cpp

main.o: main.cpp player.h interface.h
	g++ -c -lncurses player.cpp main.cpp 

main: main.o item.o player.o interface.o
	g++ main.o item.o player.o interface.o -lncurses -o main

clean:
	rm -f interface.o item.o player.o main.o event.o main

.PHONY: clean

