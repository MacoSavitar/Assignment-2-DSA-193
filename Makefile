all: assignment

DEFS = -DUSE_SOME_DEF

assignment: main.o ttowers.o
	g++ main.o ttowers.o -std=c++11 -o assignment $(DEFS)

main.o: main.cpp defs.h
	g++ -c main.cpp -std=c++11 $(DEFS)
ttowers.o: ttowers.cpp defs.h
	g++ -c ttowers.cpp -std=c++11 $(DEFS)

clean:
	rm *.o assignment
