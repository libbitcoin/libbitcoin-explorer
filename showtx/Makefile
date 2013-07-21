CXXFLAGS=$(shell pkg-config --cflags libbitcoin)
LIBS=$(shell pkg-config --libs libbitcoin)

default: showtx

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

showtx: main.o
	g++ -o showtx main.o $(LIBS)

