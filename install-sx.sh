#!/bin/bash
set -e
echo "Welcome to the S(pesmilo)X(change)"
echo

if [ $# -eq 1 ]; then
    INSTALL_PREFIX=$(pwd)/$1
    CONF_DIR=$INSTALL_PREFIX/etc/
    RUN_LDCONFIG=
    ROOT_INSTALL=0
elif [ "$(id -u)" -eq "0" ]; then
    INSTALL_PREFIX=/usr/local/
    CONF_DIR=/etc/
    RUN_LDCONFIG=ldconfig
    ROOT_INSTALL=1
else
    echo "Error: This script must be run as root." 1>&2
    echo
    echo "  $ sudo bash ./install-sx.sh" 1>&2
    echo
    exit 1
fi
echo " ***********************************************************************"
echo " * sx command line utilities - Empower The Sysadmin With Bitcoin Tools *"
echo " ***********************************************************************"
echo
echo "Installation commencing NOW ($INSTALL_PREFIX)."

DEPENDENCIES="git build-essential autoconf libtool libboost-all-dev pkg-config libcurl4-openssl-dev libleveldb-dev libzmq-dev libconfig++-dev"

function pkg_is_installed
{
    dpkg -s $1 > /dev/null
    if [ $? -eq 0 ]; then
        echo 1
    else
        echo 0
    fi
}

for pkg in $DEPENDENCIES; do
    if [ $(pkg_is_installed $pkg) -eq 0 ]; then
        echo
        echo "Error: $pkg is not installed!"
        echo
        echo "Run the following command:"
        echo
        echo "  $ sudo apt-get install $DEPENDENCIES"
        echo
        exit 1
    fi
done

if [ $ROOT_INSTALL -eq 1 ]; then
    echo "Installing dependencies..."
    apt-get install $DEPENDENCIES
fi

SRC_DIR=$INSTALL_PREFIX/src/
PKG_CONFIG_PATH=$INSTALL_PREFIX/lib/pkgconfig/

mkdir -p $SRC_DIR

cd $SRC_DIR
if [ -d "libbitcoin-git" ]; then
    echo "Updating libbitcoin..."
    cd libbitcoin-git
    git pull --rebase
else
    echo "Downloading libbitcoin..."
    git clone https://github.com/spesmilo/libbitcoin.git libbitcoin-git
    cd libbitcoin-git
fi
echo "Beginning build process now..."
autoreconf -i
./configure --enable-leveldb --prefix $INSTALL_PREFIX
make
make install
$RUN_LDCONFIG
echo "libbitcoin now installed."

cd $SRC_DIR
if [ -d "obelisk-git" ]; then
    echo "Updating obelisk.."
    cd obelisk-git
    git remote set-url origin https://github.com/spesmilo/obelisk.git
    git pull --rebase
else
    echo "Downloading obelisk..."
    git clone https://github.com/spesmilo/obelisk.git obelisk-git
    cd obelisk-git
fi
echo "Beginning build process now..."
autoreconf -i
./configure --sysconfdir $CONF_DIR --prefix $INSTALL_PREFIX
make
make install
$RUN_LDCONFIG
echo "obelisk now installed."

# Old sx put binaries in bin/sx-*
BIN_DIR=$INSTALL_PREFIX/bin/
rm -f $BIN_DIR/sx-*

cd $SRC_DIR
if [ -d "sx-git" ]; then
    echo "Updating sx..."
    cd sx-git
    git remote set-url origin https://github.com/spesmilo/sx.git
    git pull --rebase
else
    echo "Downloading sx..."
    git clone https://github.com/spesmilo/sx.git sx-git
    cd sx-git
fi
echo "Beginning build process now..."
autoreconf -i
./configure --sysconfdir $CONF_DIR --prefix $INSTALL_PREFIX
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
echo "  libbitcoin doc: /usr/local/share/doc/libbitcoin/"
echo "  obelisk doc:    /usr/local/share/doc/obelisk/"
echo "  sx doc:         /usr/local/share/doc/sx/"
echo
if [ $ROOT_INSTALL -eq 0 ]; then
    echo "Add these lines to your ~/.bashrc"
    echo
    echo "  export LD_LIBRARY_PATH=$INSTALL_PREFIX/lib/"
    echo "  export PKG_CONFIG_PATH=$INSTALL_PREFIX/lib/pkgconfig/"
    echo "  export PATH=$PATH:$INSTALL_PREFIX/bin/"
    echo
fi

