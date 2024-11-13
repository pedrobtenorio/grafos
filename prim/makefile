ifeq ($(OS),Windows_NT)
output: prim.o
	g++ prim.o -o prim.exe

prim.o: prim.cpp
	g++ -c prim.cpp

clean:
	del *.o *.exe
else
output: prim.o
	g++ prim.o -o prim

prim.o: prim.cpp
	g++ -c prim.cpp

clean:
	rm *.o prim
endif
