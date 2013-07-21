CXXFLAGS=$(shell pkg-config --cflags libbitcoin)
LIBS=$(shell pkg-config --libs libbitcoin)

default: broadcast-tx

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

broadcast-tx: main.o
	g++ -o broadcast-tx main.o $(LIBS)

