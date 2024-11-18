ifeq ($(shell uname), Linux)

kosaraju: kosaraju.o
	g++ kosaraju.o -o kosaraju
	g++ kosaraju.o -o kosaraju.bin

kosaraju.o: kosaraju.cpp
	g++ -c kosaraju.cpp

clean:
	rm *.o kosaraju kosaraju.bin

endif
