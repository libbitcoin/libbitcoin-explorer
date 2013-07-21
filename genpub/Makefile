CXXFLAGS=$(shell pkg-config --cflags libbitcoin)
LIBS=$(shell pkg-config --libs libbitcoin)

default: genpub

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

genpub: main.o
	g++ -o genpub main.o $(LIBS)

