CXXFLAGS=$(OBELISK_INCLUDE) $(shell pkg-config --cflags libbitcoin)
LIBS=$(OBELISK_LIB_PATH) -lobelisk -lzmq -lconfig++ $(shell pkg-config --libs libbitcoin)

default: sx-balance sx-history

config.o: config.cpp
	g++ -c config.cpp -o config.o $(CXXFLAGS)

balance.o: balance.cpp
	g++ -c balance.cpp -o balance.o $(CXXFLAGS)
sx-balance: balance.o config.o
	g++ -o sx-balance balance.o config.o $(LIBS)

history.o: history.cpp
	g++ -c history.cpp -o history.o $(CXXFLAGS)
sx-history: history.o config.o
	g++ -o sx-history history.o config.o $(LIBS)

install:
	cp sx-balance sx-history /usr/local/bin
	cp sx.cfg /etc/

