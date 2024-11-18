ifeq ($(shell uname), Linux)
output: dijkstra.o
	g++ dijkstra.o -o dijkstra
	g++ dijkstra.o -o dijkstra.bin

dijkstra.o: dijkstra.cpp
	g++ -c dijkstra.cpp

clean:
	rm *.o dijkstra dijkstra.bin
endif
