ifeq ($(OS),Windows_NT)
output: dijkstra.o
	g++ dijkstra.o -o dijkstra.exe

dijkstra.o: dijkstra.cpp
	g++ -c dijkstra.cpp

clean:
	del *.o
else
output: dijkstra.o
	g++ dijkstra.o -o dijkstra.exe

dijkstra.o: dijkstra.cpp
	g++ -c dijkstra.cpp

clean:
	rm *.o
endif
