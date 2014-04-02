#!/bin/bash

function keypair {
	sx newkey > privatekey-$(date +%y-%m-%d-%s).txt
	cat privatekey-$(date +%y-%m-%d-%s).txt | sx addr > publickey-$(date +%y-%m-%d-%s).txt
}

function stealth {
	sx stealth-new > stealthkeys-$(date +%y-%m-%d-%s).txt
}

if zenity --question --text="Do you want to create a new keypair?"; then
	keypair
	if zenity --question --text="Do you want to generate a stealth address?"; then
		stealth
	else
		zenity --info --text="No problem."
	fi
	zenity --info --text="Done\!"
elif zenity --question --text="Do you want to generate a stealth address?"; then
	stealth
	zenity --info --text="Done. Enjoy your privacy\!"
else
	zenity --info --text="Thanks for using SX\!"
fi
