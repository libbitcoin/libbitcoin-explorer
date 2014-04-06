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

#Obtain stealth transaction details

function sendstealth {
	sx stealth-send $(zenity --entry --title="Stealth Transaction Details" --text="Enter the stealth public address of the recipient.") > stealthrecipientaddr-$(date +%y-%m-%d-%s).txt	
}

#Check stealth transaction details

function receivestealth {
	yourstealthpriv=$(zenity --entry --title="Stealth Transaction Details" --text="Enter the stealth transaction ephemeral key.")
	ephem=$(zenity --entry --title="Stealth Transaction Details" --text="Enter your stealth private key.")
	sx stealth-recv $yourstealthpriv $ephem > stealthbitcoins-$(date +%y-%m-%d-%s).txt
	zenity --info --height=150 --text="Open the stealthbitcoins.txt file to obtain the Bitcoin key pairs from the stealth transaction. If your ephemeral and/or stealth keys were incorrect, this text file will be blank."
}

#Create a variable that is the output
# of the user's selection in the list
# dialog box.

Menu=$(zenity --list --radiolist --width=800 --height=250 \
--text="Select an action from the list below" --title="SX Tools Menu" \
--column="Select" --column="Action" --column="Description" \
FALSE "New Address" "Generate a new Bitcoin address" \
FALSE "Stealth Address" "Generate a new stealth key pair: address (public) and secret (private)." \
FALSE "Send Stealth Transaction" "Generate a stealth ephemeral key and Bitcoin public key to send a stealth transaction." \
FALSE "Receive Stealth Transaction" "Attempt to generate a Bitcoin keypair from a stealth ephemeral key")

#Pseudo-menu based on Zenity's list dialog box

if [ "$Menu" == "New Address" ]; then
	keypair
	zenity --info --text="Open the publickey.txt and privatekey.txt files to obtain Bitcoin keys."
elif [ "$Menu" == "Stealth Address" ]; then
	stealth
	zenity --info --text="Open the stealthkeys.txt file to obtain your stealth key pairs."
elif [ "$Menu" == "Send Stealth Transaction" ]; then
	sendstealth
	zenity --info --text="Open the stealthrecipient.txt file to obtain the ephemeral (shared secret) and the recipient's Bitcoin public key."
elif [ "$Menu" == "Receive Stealth Transaction" ]; then
	receivestealth
else
	zenity --info --text="Thanks for using SX\!"
fi
