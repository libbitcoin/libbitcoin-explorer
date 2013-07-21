CXXFLAGS=$(shell pkg-config --cflags libbitcoin)
LIBS=$(shell pkg-config --libs libbitcoin)

default: sign-input

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

sign-input: main.o
	g++ -o sign-input main.o $(LIBS)

