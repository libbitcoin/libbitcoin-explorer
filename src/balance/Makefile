CXXFLAGS=-I$(shell echo ~)/obelisk/include $(shell pkg-config --cflags libbitcoin)
LIBS=$(shell echo ~)/obelisk/client/libobelisk_client.a -lzmq $(shell pkg-config --libs libbitcoin)

default: balance

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

balance: main.o
	g++ -o balance main.o $(LIBS)

