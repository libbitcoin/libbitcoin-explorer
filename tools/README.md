These tools are designed to create a bootstrapped version of [Sx](https://sx.dyne.org/) for folks without much Linux or command line experience to start using Sx. The way we do this is by writing shell scripts that are executable for the user to run certain functions in Sx. 

Ultimately, the reason for doing this is to allow users to start using [Stealth addresses](https://wiki.unsystem.net/index.php/DarkWallet/Stealth) via Sx asap. No doubt this project will be redundant as wallet software starts to make stealth wallets an easy experience.

## Instructions

1) Install SX [here](https://github.com/spesmilo/sx). Open the root terminal (you should at least know how to do that), and type in:

```$ wget http://sx.dyne.org/install-sx.sh```

Navitage (either with the Terminal, or using Nautilus [equivalent to Finder or Windows Explorer]) to 'usr/loca/src/sx-git'. Double click './install-sx.sh' to install Sx, or [open the Terminal from Nautilus](http://askubuntu.com/questions/207442/how-to-add-open-terminal-here-to-nautilus-context-menu) and type the folllowing:

```$ sudo bash ./install-sx.sh```

Basic SX functionality will work, but for more sophisticated features (i.e. stealth addresses), **certain dependencies are required**. They may already be installed, but if they are you not will typically need to install the following:

1. ```sudo apt-get install python-setuptools```  
2. ```sudo easy_install pip```  
3. ```sudo pip install ecdsa```  
4. ```sudo pip install pyzmq```
5. ```sudo apt-get install qrencode```

Afer these steps, generating things like stealth addresses will work perfectly.

2) Download the scripts from 'sx/tools' to a directory of your choice. You can either run the scripts from the terminal or make the scripts executable upon clicking by first opening the terminal and typing:

```chmod +x ./<filename>```

E.g.

```chmod +x ./sx-gui.sh```

Have fun from there.

## Script

**sx-gui.sh**

There is one pseudo-menu created from Zenity's list dialog boxe that allow you to create a new private key and stealth address pubkey and ephemeral key. **Text files with the keys will be created in the location of the script!**

![alt text](http://s9.postimg.org/h1ic5t98v/GUI4.png "Pseudo-Menu")

## Charity Donations

For transactions made through SX, you now have the option to include a donation (e.g. 10000 Satoshis, equivalent to a transaction fee) to any charity, organisation, or individual, either as a background component of any transaction you choose.

![alt text](http://s10.postimg.org/hg4sl7d4p/Charity.png "Donations")

## Contribute

If you'd like to contribute, please commit: 

1. Write shell scripts for any remaining commands for [SX](https://sx.dyne.org/) (WIP) // Please test first
2. Implement [Zenity](http://www.howtogeek.com/107537/how-to-make-simple-graphical-shell-scripts-with-zenity-on-linux/) wraps for the shell scripts
3. Open an issue for [ABIS](https://github.com/ABISprotocol/ABIS) -- see also [http://abis.io](http://abis.io)
