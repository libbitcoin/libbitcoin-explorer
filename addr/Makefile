CXXFLAGS=$(shell pkg-config --cflags libbitcoin)
LIBS=$(shell pkg-config --libs libbitcoin)

default: addr

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

addr: main.o
	g++ -o addr main.o $(LIBS)

