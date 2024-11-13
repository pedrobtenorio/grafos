ifeq ($(OS),Windows_NT)
output: kruskal.o
	g++ kruskal.o -o kruskal.exe

kruskal.o: kruskal.cpp
	g++ -c kruskal.cpp

clean:
	del *.o
else
output: kruskal.o
	g++ kruskal.o -o kruskal.exe

kruskal.o: kruskal.cpp
	g++ -c kruskal.cpp

clean:
	rm *.o
endif