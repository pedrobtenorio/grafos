ifeq ($(shell uname), Linux)

floyd: floyd.o
	g++ floyd.o -o floyd
	g++ floyd.o -o floyd.bin

floyd.o: floyd.cpp
	g++ -c floyd.cpp

clean:
	rm *.o floyd floyd.bin

endif
