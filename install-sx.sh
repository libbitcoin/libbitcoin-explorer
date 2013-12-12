#!/bin/bash
set -e
echo "Welcome to the S(pesmilo)X(change)"

if [ $# -eq 1 ]; then
    if [[ "$1" = /* ]]; then
        # Absolute path.
        INSTALL_PREFIX=$1
    else
        # Relative path.
        INSTALL_PREFIX=$(pwd)/$1
    fi
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

<<<<<<< HEAD
function is_ubuntu_precise
{
    uname -a | grep precise > /dev/null
    if [ $? -eq 0 ]; then
        echo 1
    else
        echo 0
    fi
}

echo "Ubuntu/Debian users require the following packages:"
echo "git build-essential autoconf libtool libboost-all-dev"
echo "pkg-config libcurl4-openssl-dev libleveldb-dev"
echo "libzmq-dev libconfig++-dev libncurses5-dev"
echo
echo "Fedora/Redhat users require the following packages:"
echo "gcc-c++ git autoconf libtool boost-devel pkgconfig"
echo "libcurl-devel openssl-devel leveldb-devel zeromq"
echo "zeromq3 zeromq-devel libconfig libconfig-devel"
echo "ncurses-devel"
echo "and a package group called 'Development Tools'."
echo
echo "Installing dependencies..."

mydistro=`cat /etc/*-release | egrep -i "Debian|Ubuntu" | wc -l`
if [ $mydistro -gt 0 ]; then 
    for pkg in $DEPENDENCIES; do
        # Workaround for Ubuntu 12.04 64bit
        # https://bitcointalk.org/index.php?topic=259999.msg3802342#msg3802342
        if [ "$pkg" == "libconfig++-dev" ]; then
            if [ $(is_ubuntu_precise) -eq 1 ]; then
                pkg="libconfig++8-dev"
            fi
        fi
        if [ "$pkg" == "libboost-all-dev" ]; then
            if [ $(is_ubuntu_precise) -eq 1 ]; then
                pkg="libboost1.48-all-dev"
            fi
        fi
    
        if [ $ROOT_INSTALL -eq 1 ]; then
            apt-get install $pkg
        fi
    
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
fi

mydistro=`cat /etc/*-release | egrep -i "Fedora|Redhat" | wc -l`
if [ $mydistro -gt 0 ]; then 
    sudo yum groupinstall "Development Tools"
    sudo yum install gcc-c++ git autoconf libtool boost-devel pkgconfig libcurl-devel openssl-devel leveldb-devel zeromq zeromq3 zeromq-devel libconfig libconfig-devel ncurses-devel
    echo
    echo "You may have some issues regarding the file"
    echo "/usr/include/openssl/ec.h and may need to use the"
    echo "openssl tarball as it is removed by redhat for legal reasons."
    echo
    echo "To compile this software into a local directory before"
    echo "copying it into your root filesystem, run the following commands"
    echo "cd sx"
    echo "mkdir target"
    echo "sudo env PKG_CONFIG_PATH='./target/' ./install-sx.sh target"
    echo
fi

echo "Installation commencing NOW ($INSTALL_PREFIX)."

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
if [ -d "libwallet-git" ]; then
    echo "Updating libwallet..."
    cd libwallet-git
    git pull --rebase
else
    echo "Downloading libwallet..."
    git clone https://github.com/spesmilo/libwallet.git libwallet-git
    cd libwallet-git
fi
echo "Beginning build process now..."
autoreconf -i
./configure --prefix $INSTALL_PREFIX
make
make install
$RUN_LDCONFIG
echo "libwallet now installed."

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
echo "Config files are in $CONF_DIR/"
echo "  obelisk cfg:    $CONF_DIR/obelisk/*.cfg"
echo "  sx cfg:         ~/.sx.cfg (see $INSTALL_PREFIX/share/sx/sx.cfg for an"
echo "                  example config file."
echo
echo "Documentation is available /usr/local/doc/"
echo "  libbitcoin doc: $INSTALL_PREFIX/share/doc/libbitcoin/"
echo "  obelisk doc:    $INSTALL_PREFIX/share/doc/obelisk/"
echo "  sx doc:         $INSTALL_PREFIX/share/doc/sx/"
echo
if [ $ROOT_INSTALL -eq 0 ]; then
    echo "Add these lines to your ~/.bashrc"
    echo
    echo "  export LD_LIBRARY_PATH=$INSTALL_PREFIX/lib/"
    echo "  export PKG_CONFIG_PATH=$INSTALL_PREFIX/lib/pkgconfig/"
    echo "  export PATH=\$PATH:$INSTALL_PREFIX/bin/"
    echo
fi

