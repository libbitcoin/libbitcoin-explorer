CXXFLAGS=$(shell pkg-config --cflags libbitcoin)
LIBS=$(shell pkg-config --libs libbitcoin)

default: send-tx

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

send-tx: main.o
	g++ -o send-tx main.o $(LIBS)

