#!/bin/bash
#
# Script to install libbitcoin, libwallet, obelisk and sx tools.
#
# Install dependencies and compiles the source code from git for Debian 7 / Ubuntu 13.10 or Fedora GNU/Linux distributions.
#
# Requires sudo. 
#
# To execute this script, run:
# <sudo bash install-sx.sh>
#
# To read help instructions run:
# <sudo bash install-sx.sh --help>
#
#
set -e
echo
echo " [+] Welcome to S(pesmilo)X(changer)."
echo
sleep 0.3
if [ "$#" = "1" ]; then
    if [[ "$1" = /* ]]; then
        #Absolute path
        INSTALL_PREFIX=$1
    elif [ "$1" = "--help" ]; then
        echo
        echo " [+] Install script help:"
        echo " Requires sudo."
        echo " --> To execute this script type:"
        echo " <sudo bash install-sx.sh>"
        echo " --> To execute this script and install at a specific path type:"
        echo " <sudo bash install-sx.sh PATH/...>"
        echo " This script will install libbitcoin, libwallet, obelisk and sx tools."
        echo " The standard path to the source instalation is /usr/local/src."
        echo " The stardard path for the conf files is /etc."
        echo
        exit
    else
        #Relative path
        RELATIVE=`pwd`
        INSTALL_PREFIX=$RELATIVE/$1
    fi
    CONF_DIR=$INSTALL_PREFIX/etc
    RUN_LDCONFIG=
    ROOT_INSTALL=0
elif [ `id -u` = "0" ]; then
    INSTALL_PREFIX=/usr/local
    CONF_DIR=/etc
    RUN_LDCONFIG=ldconfig
    ROOT_INSTALL=1
else
    echo
    echo "[+] ERROR: This script must be run as root." 1>&2
    echo
    echo "<sudo bash install-sx.sh>"
    echo
    exit
fi
SRC_DIR=$INSTALL_PREFIX/src
PKG_CONFIG_PATH=$INSTALL_PREFIX/lib/pkgconfig
mkdir -p $SRC_DIR
mkdir -p $PKG_CONFIG_PATH
#
install_dependencies(){
    flavour_id=`cat /etc/*-release | egrep -i "^ID=" | cut -f 2 -d "="`
    echo " Flavour: $flavour_id."
    echo
    if [ "$flavour_id" = "debian" ]; then
        if [ "$ROOT_INSTALL" = 1 ]; then
# Debian dependencies
            D_DEPENDENCIES="git build-essential autoconf apt-utils libtool libboost-all-dev pkg-config libcurl4-openssl-dev libleveldb-dev libzmq-dev libconfig++-dev libncurses5-dev"
            sleep 0.5
            apt-get -y install $D_DEPENDENCIES
        fi
    elif [ "$flavour_id" = "ubuntu" ]; then
        if [ "$ROOT_INSTALL" = 1 ]; then
# Ubuntu dependencies
            #some people have 1.53 installed, determine which and install -dev-all
            for BOOST in libboost1.49 libboost1.53 ; do
                dpkg -s "$BOOST-dev" >/dev/null 2>&1 && {
                  echo "installing $BOOST-dev-all"
                  apt-get install $BOOST-all-dev -y && break
              }
            done

            U_DEPENDENCIES="git build-essential autoconf apt-utils libtool pkg-config libcurl4-openssl-dev libleveldb-dev libzmq-dev libconfig++8-dev libncurses5-dev"
            sleep 0.5
            apt-get -y install $U_DEPENDENCIES
        fi
    elif [ "$flavour_id" = "fedora" ]; then
        if [ "$ROOT_INSTALL" = 1 ]; then
# Fedora dependencies
            F_DEPENDENCIES="gcc-c++ git autoconf libtool boost-devel pkgconfig libcurl-devel openssl-devel leveldb-devel zeromq zeromq3 zeromq-devel libconfig libconfig-devel ncurses-devel"
            sleep 0.5
            yum -y install $F_DEPENDENCIES
        fi
    else
        echo
        echo " [+] ERROR: No GNU/Linux flavour properly detected: $flavour_id" 1>&2
        echo 
        echo " Please, review the script."
        echo
        exit
    fi
}

install_libbitcoin(){
    cd $SRC_DIR
    if [ -d "libbitcoin-git" ]; then
        echo
        echo " --> Updating Libbitcoin..."
        echo
        cd libbitcoin-git
        git remote set-url origin https://github.com/spesmilo/libbitcoin.git
        git pull --rebase
    else
        echo
        echo " --> Downloading Libbitcoin from git..."
        echo
        git clone https://github.com/spesmilo/libbitcoin.git libbitcoin-git
    fi
    cd $SRC_DIR/libbitcoin-git
    echo
    echo " --> Beggining build process now...."
    echo
    autoreconf -i
    ./configure --enable-leveldb --prefix $INSTALL_PREFIX
    make
    make install
    $RUN_LDCONFIG
    echo
    echo " o/ Libbitcoin now installed."
    echo
    }

install_libwallet(){
    cd $SRC_DIR
    if [ -d "libwallet-git" ]; then
        echo
        echo " --> Updating Libwallet..."
        echo
        cd libwallet-git
        git remote set-url origin https://github.com/spesmilo/libwallet.git
        git pull --rebase
    else
        echo
        echo " --> Downloading Libwallet from git..."
        echo
        git clone https://github.com/spesmilo/libwallet.git libwallet-git
    fi
    cd $SRC_DIR/libwallet-git
    echo
    echo " --> Beggining build process now...."
    echo
    autoreconf -i
    ./configure --prefix $INSTALL_PREFIX
    make
    make install
    $RUN_LDCONFIG
    echo
    echo " o/ Libwallet now installed."
    echo
    }

install_obelisk(){
    cd $SRC_DIR
    if [ -d "obelisk-git" ]; then
        echo
        echo " --> Updating Obelisk..."
        echo
        cd obelisk-git
        git remote set-url origin https://github.com/spesmilo/obelisk.git
        git pull --rebase
    else
        echo
        echo " --> Downloading obelisk..."
        echo
        git clone https://github.com/spesmilo/obelisk.git obelisk-git
    fi
    cd $SRC_DIR/obelisk-git
    echo
    echo " --> Beggining build process now..."
    echo
    autoreconf -i
    ./configure --sysconfdir $CONF_DIR --prefix $INSTALL_PREFIX
    make
    make install 
    $RUN_LDCONFIG
    echo
    echo " o/ Obelisk now installed."
    echo
    }

install_sx(){
    BIN_DIR=$INSTALL_PREFIX/bin
    rm -rf $BIN_DIR/sx-*
    cd $SRC_DIR
    if [ -d "sx-git" ]; then
        echo
        echo " --> Updating SX..."
        echo
        cd sx-git
        git remote set-url origin https://github.com/spesmilo/sx.git
        git pull --rebase
    else
        echo
        echo " --> Downloading SX from git..."
        echo
        git clone https://github.com/spesmilo/sx.git sx-git
    fi
    cd $SRC_DIR/sx-git
    echo
    echo " --> Beggining build process now...."
    echo
    autoreconf -i
    ./configure --sysconfdir $CONF_DIR --prefix $INSTALL_PREFIX
    make
    make install
    $RUN_LDCONFIG
    echo
    echo " o/ SX tools now installed."
    echo
    }

show_finish_install_info(){
    echo " --> Installation finished!"
    if [ "$ROOT_INSTALL" = "1" ]; then
        echo
        echo " Config Files are in: $CONF_DIR"
        echo "   obelisk configuration files: $CONF_DIR/obelisk/*.cfg"
        echo "   sx configuration file: ~/.sx.cfg (see $INSTALL_PREFIX/share/sx/sx.cfg for an example config file)"
        echo 
        echo " Documentation available /usr/local/doc:"
        echo "   libbitcoin doc: $INSTALL_PREFIX/share/doc/libbitcoin/"
        echo "   obelisk doc:    $INSTALL_PREFIX/share/doc/obelisk/"
        echo "   sx doc:         $INSTALL_PREFIX/share/doc/sx/"
        echo
    elif [ "$ROOT_INSTALL" = "0" ]; then
        echo
        echo " Add these lines to your ~/.bashrc"
        echo "   export LD_LIBRARY_PATH=$INSTALL_PREFIX/lib"
        echo "   export PKG_CONFIG_PATH=$INSTALL_PREFIX/lib/pkgconfig"
        echo "   export PATH=\$PATH:$INSTALL_PREFIX/bin"
    fi
    echo 
    echo " To setup a obelisk node, you will need obworker and obbalancer daemons running."
    echo " Run <sudo bash $SRC_DIR/obelisk-git/scripts/setup.sh> to create, configure and start the daemons."
    echo
}

install_dependencies
install_libbitcoin
install_libwallet
install_obelisk
install_sx
show_finish_install_info
