#!/bin/bash
set -e
echo "Welcome to the S(pesmilo)X(change)"
echo
if [ "$(id -u)" != "0" ]; then
    echo "Error: This script must be run as root." 1>&2
    echo
    echo "  $ sudo ./install-sx.sh" 1>&2
    echo
    exit 1
fi
echo " ***********************************************************************"
echo " * sx command line utilities - Empower The Sysadmin With Bitcoin Tools *"
echo " ***********************************************************************"
echo
echo Installation commencing NOW.

INSTALL_DATE=$(date +%s)

echo "(Installing git if neccessary."
apt-get install git

mkdir -p /usr/local/src/

cd /usr/local/src/
if [ -d "libbitcoin-git" ]; then
    echo "Updating libbitcoin..."
    cd libbitcoin-git
    git pull --rebase
else
    echo "Downloading libbitcoin..."
    git clone https://github.com/spesmilo/libbitcoin.git libbitcoin-git
    cd libbitcoin-git
fi
echo "Installing libbitcoin dependencies..."
apt-get install build-essential autoconf libtool libboost-all-dev pkg-config libcurl4-openssl-dev libleveldb-dev
echo "Beginning build process now..."
autoreconf -i
./configure --enable-leveldb
make
make install
ldconfig
echo "libbitcoin now installed."

cd /usr/local/src/
if [ -d "obelisk-git" ]; then
    echo "Updating obelisk.."
    cd obelisk-git
    git pull --rebase
else
    echo "Downloading obelisk..."
    git clone https://github.com/genjix/obelisk.git obelisk-git
    cd obelisk-git
fi
echo "Installing obelisk dependencies..."
apt-get install libzmq-dev libconfig++-dev
echo "Beginning build process now..."
autoreconf -i
./configure --sysconfdir=/etc/
make
make install
ldconfig
echo "obelisk now installed."

# Old sx put binaries in bin/sx-*
rm -f /usr/local/bin/sx-*

cd /usr/local/src/
if [ -d "sx-git" ]; then
    echo "Updating sx..."
    cd sx-git
    git pull --rebase
else
    echo "Downloading sx..."
    git clone https://github.com/genjix/sx sx-git
    cd sx-git
fi
echo "Beginning build process now..."
autoreconf -i
./configure --sysconfdir=/etc/
make
make install
echo "sx now installed."
echo
echo "Config files are in /etc/"
echo "  obelisk cfg:    /etc/obelisk/*.cfg"
echo "  sx cfg:         ~/.sx.cfg (see /usr/local/share/sx/sx.cfg for an"
echo "                  example config file."
echo
echo "Documentation is available /usr/local/doc/"
echo "  libbitcoin doc: /usr/local/doc/libbitcoin/"
echo "  obelisk doc:    /usr/local/doc/libbitcoin/"
echo "  sx doc:         /usr/local/doc/libbitcoin/"
echo

