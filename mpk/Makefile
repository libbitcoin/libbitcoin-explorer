CXXFLAGS=$(shell pkg-config --cflags libbitcoin)
LIBS=$(shell pkg-config --libs libbitcoin)

default: mpk

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

mpk: main.o
	g++ -o mpk main.o $(LIBS)

