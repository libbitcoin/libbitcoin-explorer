These tools are designed to create a bootstrapped version of [Sx](https://sx.dyne.org/) for folks without much Linux or command line experience to start using Sx. The way we do this is by writing shell scripts that are executable for the user to run certain functions in Sx. 

Ultimately, the reason for doing this is to allow users to start using [Stealth addresses](https://wiki.unsystem.net/index.php/DarkWallet/Stealth) via Sx asap. No doubt this project will be redundant as wallet software starts to make stealth wallets an easy experience.

## Instructions

1) Install Sx [here](https://github.com/spesmilo/sx). Open the root terminal (you should at least know how to do that), and type in:

```$ wget http://sx.dyne.org/install-sx.sh```

Navitage (either with the Terminal, or using Nautilus [equivalent to Finder or Windows Explorer]) to 'usr/loca/src/sx-git'. Double click './install-sx.sh' to install Sx, or [open the Terminal from Nautilus](http://askubuntu.com/questions/207442/how-to-add-open-terminal-here-to-nautilus-context-menu) and type the folllowing:

```$ sudo bash ./install-sx.sh```

2) Download the scripts from the 'n00b-Sx' repo to a directory of your choice. You can either execute the scripts from the Terminal or make the scripts executable upon clicking by first opening the Terminal and typing:

```chmod +x ./<filename>```

E.g.

```chmod +x ./Start.sh```

Have fun from there.

## Scripts

**Start.sh**

A number of dialog boxes that allow you to create a new private key and stealth address pubkey and ephemeral key. **Text files with the keys will be created in the location of the script!**

![alt text](http://s11.postimg.org/uug1bf3dv/Aggregate.png "Dialog Boxes")

## Contribute

If you'd like to contribute, please commit: 

1. Write shell scripts for any remaining commands for [Sx](https://sx.dyne.org/) (WIP) // Please test first
2. Implement [Zenity](http://www.howtogeek.com/107537/how-to-make-simple-graphical-shell-scripts-with-zenity-on-linux/) wraps for the shell scripts
