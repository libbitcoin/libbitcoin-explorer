#!bin/bash

#Create a new keypair

function keypair {
	sx newkey > privatekey-$(date +%y-%m-%d-%s).txt
	cat privatekey-$(date +%y-%m-%d-%s).txt | sx addr > publickey-$(date +%y-%m-%d-%s).txt
}

#Create a new stealth address

function stealth {
	sx stealth-new > stealthkeys-$(date +%y-%m-%d-%s).txt
}

#Create a variable that is the output
# of the user's selection in the list
# dialog box.

OUT=$(zenity --list --checklist --text="Select an action from the list below" --title="SX Tools Menu" --column="Select" --column="Create" TRUE "New Address" FALSE "Stealth Address")

#Pseudo-menu based on Zenity's list dialog box

if [ "$OUT" == "New Address" ]; then
	keypair
elif [ "$OUT" == "Stealth Address" ]; then
	stealth
elif [ "$OUT" == "New Address|Stealth Address" ]; then
	keypair
	stealth
else
	zenity --info --text="Thanks for using SX\!"
fi
