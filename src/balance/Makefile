CXXFLAGS=$(OBELISK_INCLUDE) $(shell pkg-config --cflags libbitcoin)
LIBS=$(OBELISK_LIB) -lobelisk_client -lzmq $(shell pkg-config --libs libbitcoin)

default: balance

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

balance: main.o
	g++ -o balance main.o $(LIBS)

