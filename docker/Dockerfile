from ubuntu:13.10
run apt-get update; 
run apt-get install -y git build-essential autoconf apt-utils libtool  pkg-config libcurl4-openssl-dev libleveldb-dev libconfig++8-dev libncurses5-dev libboost1.49-all-dev wget
run cd /tmp/;  git clone https://github.com/jedisct1/libsodium libsodium-git; cd libsodium-git; ./autogen.sh;./configure ; make; make install;ldco
run cd /tmp; wget http://download.zeromq.org/zeromq-4.0.4.tar.gz;  tar zxf zeromq-4.0.4.tar.gz  ; cd zeromq-4.0.4; ./autogen.sh; ./configure; make; make install;
run cd /tmp;  git clone https://github.com/zeromq/czmq czmq-git; cd czmq-git; ./autogen.sh ; ./configure; make; make install;
run cd /tmp;  git clone https://github.com/zeromq/czmqpp czmqpp-git; cd czmqpp-git; autoreconf -i; ./configure; make; make install;
run cd /tmp; git clone https://github.com/libbitcoin/libbitcoin.git libbitcoin-git; cd libbitcoin-git;  autoreconf -i; ./configure --enable-leveldb ; make; make install;
run cd /tmp; git clone https://github.com/libbitcoin/libwallet.git libwallet-git ; cd libwallet-git; autoreconf -i; ./configure ; make; make install; 
run cd /tmp;  git clone https://github.com/libbitcoin/obelisk.git obelisk-git; cd obelisk-git; autoreconf -i; ./configure; make; make install;
run cd /tmp;  git clone https://github.com/spesmilo/sx.git sx-git; cd sx-git; autoreconf -i; ./configure ; make; make install;
run ldconfig
