CXXFLAGS=$(shell pkg-config --cflags libbitcoin)
LIBS=$(shell pkg-config --libs libbitcoin)

default: newpriv

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

newpriv: main.o
	g++ -o newpriv main.o $(LIBS)

