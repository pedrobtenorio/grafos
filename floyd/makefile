ifeq ($(OS),Windows_NT)
output: floyd.o
	g++ floyd.o -o floyd.exe

floyd.o: floyd.cpp
	g++ -c floyd.cpp

clean:
	del *.o
else
output: floyd.o
	g++ floyd.o -o floyd.exe

floyd.o: floyd.cpp
	g++ -c floyd.cpp

clean:
	rm *.o
endif