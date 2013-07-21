CXXFLAGS=$(shell pkg-config --cflags libbitcoin)
LIBS=$(shell pkg-config --libs libbitcoin)

default: showpriv

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

showpriv: main.o
	g++ -o showpriv main.o $(LIBS)

