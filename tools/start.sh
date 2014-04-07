#!bin/bash

#Create a new keypair

function keypair {
	sx newkey > privatekey-$(date +%y-%m-%d-%s).txt
	cat privatekey-$(date +%y-%m-%d-%s).txt | sx addr > publickey-$(date +%y-%m-%d-%s).txt
	zenity --info --text="Open the publickey-DATE.txt and privatekey.txt files to obtain Bitcoin keys."
}

#Create a new stealth address

function stealth {
	sx stealth-new > stealthkeys-$(date +%y-%m-%d-%s).txt
	zenity --info --text="Open the stealthkeys-DATE.txt file to obtain your stealth key pairs."
}

#Obtain stealth transaction details

function sendstealth {
	sx stealth-send $(zenity --entry --title="Stealth Transaction Details" --text="Enter the stealth public address of the recipient.") > stealthrecipientaddr-$(date +%y-%m-%d-%s).txt
	zenity --info --text="Open the stealthrecipient-DATE.txt file to obtain the ephemeral (shared secret) and the recipient's Bitcoin public key."	
}

#Check stealth transaction details

function receivestealth {
	yourstealthpriv=$(zenity --entry --title="Stealth Transaction Details" --text="Enter the stealth transaction ephemeral key.")
	ephem=$(zenity --entry --title="Stealth Transaction Details" --text="Enter your stealth private key.")
	sx stealth-recv $yourstealthpriv $ephem > stealthbitcoins-$(date +%y-%m-%d-%s).txt
	zenity --info --height=150 --text="Open the stealthbitcoins-DATE.txt file to obtain the Bitcoin key pairs from the stealth transaction. If your ephemeral and/or stealth keys were incorrect, this text file will be blank."
}

#Create QR code

function qrcodegen {
	sx qrcode $(zenity --entry --title="Input Bitcoin Address" --text="Enter the public key for your Bitcoin address. Make sure 'qrencode' is installed (see README.md") qrcode-$(date +%y-%m-%d-%s).png
	zenity --info --height=150 --text="Open the qrcode-DATE.png to view your QR code."
}

#Multisignature

function mofn {
	sx rawscript 2 [ $(zenity --entry --title="Multisignature Transaction (2-3): Address 1." --text="Enter the uncompressed public key for address 1.") ] [ $(zenity --entry --title="Multisignature Transaction (2-3): Address 2." --text="Enter the uncompressed public key for address 2.") ] [$(zenity --entry --title="Multisignature Transaction (2-3): Address 3." --text="Enter the uncompressed public key for address 3.") ] 3 checkmultisig > msig-$(date +%y-%m-%d-%s).script
	cat msig-$(date +%y-%m-%d-%s).script | sx scripthash > msig-address-$(date +%y-%m-%d-%s).txt
	zenity --info --height=150 --title="Multisignature (2-3) Bitcoin Address" --text=$(cat msig-$(date +%y-%m-%d-%s).script | sx scripthash)
	zenity --info --height=150 --text="A copy of the rawscript and public Bitcoin address for your multisignature address can be found in msig-address-DATE.txt"
}

#Create a variable that is the output
# of the user's selection in the list
# dialog box.

Menu=$(zenity --list --radiolist --width=800 --height=300 \
--text="Select an action from the list below" --title="SX Tools Menu" \
--column="Select" --column="Action" --column="Description" \
FALSE "New Address" "Generate a new Bitcoin address" \
FALSE "Stealth Address" "Generate a new stealth key pair: address (public) and secret (private)." \
FALSE "Send Stealth Transaction" "Generate a stealth ephemeral key and Bitcoin public key to send a stealth transaction." \
FALSE "Receive Stealth Transaction" "Attempt to generate a Bitcoin keypair from a stealth ephemeral key" \
FALSE "Create QR Code" "Generate a QR code from a Bitcoin public key" \
FALSE "Create Multisignature Transaction" "Generate rawscript and address for a 2-3 multisignature transaction")

#Pseudo-menu based on Zenity's list dialog box

if [ "$Menu" == "New Address" ]; then
	keypair
elif [ "$Menu" == "Stealth Address" ]; then
	stealth
elif [ "$Menu" == "Send Stealth Transaction" ]; then
	sendstealth
elif [ "$Menu" == "Receive Stealth Transaction" ]; then
	receivestealth
elif [ "$Menu" == "Create QR code" ]; then
	qrcodegen
elif [ "$Menu" == "Create Multisignature Transaction" ]; then
	mofn
else
	zenity --info --text="Thanks for using SX\!"
fi
