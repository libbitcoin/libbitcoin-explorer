CXXFLAGS=$(shell pkg-config --cflags libbitcoin)
LIBS=$(shell pkg-config --libs libbitcoin)

default: newseed

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

newseed: main.o
	g++ -o newseed main.o $(LIBS)

