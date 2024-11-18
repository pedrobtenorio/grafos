ifeq ($(shell uname), Linux)

prim: prim.o
	g++ prim.o -o prim
	g++ prim.o -o prim.bin

prim.o: prim.cpp
	g++ -c prim.cpp

clean:
	rm *.o prim prim.bin

endif
