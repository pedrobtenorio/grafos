ifeq ($(shell uname), Linux)

kruskal: kruskal.o
	g++ kruskal.o -o kruskal
	g++ kruskal.o -o kruskal.bin

kruskal.o: kruskal.cpp
	g++ -c kruskal.cpp

clean:
	rm *.o kruskal kruskal.bin

endif
