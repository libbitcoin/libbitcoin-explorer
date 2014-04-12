#!bin/sh

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
	zenity --info --height=150 --text="Open the 'qrcode-DATE.png' to view your QR code."
}

#Create a Multisignature Rawscript

function mofn {
	sx rawscript 2 [ $(zenity --entry --title="Multisignature Transaction (2-3): Address 1." --text="Enter the uncompressed public key for address 1.") ] [ $(zenity --entry --title="Multisignature Transaction (2-3): Address 2." --text="Enter the uncompressed public key for address 2.") ] [$(zenity --entry --title="Multisignature Transaction (2-3): Address 3." --text="Enter the uncompressed public key for address 3.") ] 3 checkmultisig > msig-$(date +%y-%m-%d-%s).script
	cat msig-$(date +%y-%m-%d-%s).script | sx scripthash > msig-address-$(date +%y-%m-%d-%s).txt
	zenity --info --height=150 --title="Multisignature (2-3) Bitcoin Address" --text=$(cat msig-$(date +%y-%m-%d-%s).script | sx scripthash)
	zenity --info --height=150 --text="A copy of the rawscript and public Bitcoin address for your multisignature address can be found in 'msig-address-DATE.txt'."
}

#Create a Deterministic Wallet Seed and Master Public Key

function dw-seed {
	sx newseed > dw-seed-$(date +%y-%m-%d-%s).seed
	cat dw-seed-$(date +%y-%m-%d-%s).seed | sx mpk > master_public-$(date +%y-%m-%d-%s).key
	zenity --info --height=150 --title="Deterministic Wallet" --text="Deterministic wallet created! Open the 'dwallet-DATE.key' file to obtain your seed. Open the 'master_public-DATE.key' file to obtain your master public key."
}

#Select a File

function selectkeys {
	FILE=`zenity --file-selection --title="Select a deterministic wallet seed or master public key"`

	case $? in
	         0)
	                echo "\"$FILE\" selected.";;
	         1)
	                echo "No file selected.";;
	        -1)
	                echo "An unexpected error has occurred.";;
	esac
}

#Create a Private Key from a Deterministic Wallet Seed

function dw-privkey {
	selectkeys
	cat "$FILE" | sx genpriv $(zenity --entry --title="Deterministic Wallet Private Key from wallet seed" --text="Enter the private key number.") > DW-privkey-$(date +%y-%m-%d-%s).txt
	zenity --info --height=150 --title="Deterministic Wallet" --text="You have successfully generated a Bitcoin private key from a deterministic wallet seed. Open the 'DW-privkey-DATE.txt' file to obtain it."
}

#Create a Public Key from a Deterministic Wallet Seed

function dw-pubkey {
	selectkeys
	cat "$FILE" | sx genaddr $(zenity --entry --title="Deterministic Wallet Public Key from wallet seed" --text="Enter the public key number.") > DW-pubkey-$(date +%y-%m-%d-%s).txt
	zenity --info --height=150 --title="Deterministic Wallet" --text="You have successfully generated a Bitcoin public key from a deterministic wallet seed. Open the 'DW-pubkey-DATE.txt' file to obtain it."
}

#Create a Public Key from a Master Public Key

function masterpublickey {
	selectkeys
	cat "$FILE" | sx genaddr $(zenity --entry --title="Deterministic Wallet Public Key from master public key" --text="Enter the public key number.") > DW-pubkey-$(date +%y-%m-%d-%s).txt
	zenity --info --height=150 --title="Deterministic Wallet" --text="You have successfully generated a Bitcoin public key from a master public key. Open the 'DW-pubkey-DATE.txt' file to obtain it."

}

#Convert Deterministic Wallet Seed into an Electrum Compatible 12 Word Seed

function mnemonicthis {
	selectkeys 
	cat "$FILE" | sx mnemonic > Electrum-"$(basename $FILE)".txt
	zenity --info --height=150 --title="Deterministic Wallet" --text="You have successfully generated an Electrum-style 12 word seed from a deterministic wallet seed. Open the 'Electrum.txt' file to obtain it."
}

#Convert an Electrum 12 Word Seed into a Deterministic Wallet Seed

function demnemonicthis {
	echo $(zenity --entry --title="Deterministic Wallet Public Key from 12 Word Seed" --text="Enter the 12 word seed.") | sx mnemonic > dw-wallet-$(date +%y-%m-%d-%s).txt
	zenity --info --height=150 --title="Deterministic Wallet" --text="You have successfully converted a 12 word seed to the original seed. Open the 'dw-wallet-DATE.txt' file to obtain it."

}

#Create a variable that is the output of the user's selection in the list dialog box.

Menu=$(zenity --list --radiolist --width=1100 --height=400 \
--text="Select an action from the list below" --title="SX Tools Menu" \
--column="Select" --column="Action" --column="Description" \
FALSE "New Address" "Generate a new Bitcoin address" \
FALSE "Stealth Address" "Generate a new stealth key pair: address (public) and secret (private)." \
FALSE "Send Stealth Transaction" "Generate a stealth ephemeral key and Bitcoin public key to send a stealth transaction." \
FALSE "Receive Stealth Transaction" "Attempt to generate a Bitcoin keypair from a stealth ephemeral key" \
FALSE "Create QR Code" "Generate a QR code from a Bitcoin public key" \
FALSE "Create Multisignature Address" "Generate rawscript and address for a 2-3 multisignature address" \
FALSE "Create Deterministic Wallet Seed" "Create a deterministic wallet seed and master public key" \
FALSE "Create Private Key from a DW Seed" "Create private keys from a deterministic wallet seed" \
FALSE "Create Public Key from DW Seed" "Create public keys from a deterministic wallet seed" \
FALSE "Create Public key from a DW Master Public Key" "Create public keys from a deterministic wallet master public key. You can't generate private keys from this file." \
FALSE "Generate Electrum-style Word Seed for a Deterministic Wallet Seed" "Create an Electrum compatible 12 word seed from a deterministic wallet seed using the mnemonic tool." \
FALSE "Derive Deterministic Wallet Seed from Electrum-style Word Seed" "Derive the original deterministic wallet seed from the Electrum-style 12 word seed.")

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
elif [ "$Menu" == "Create Multisignature Address" ]; then
	mofn
elif [ "$Menu" == "Create Deterministic Wallet Seed" ]; then
	dw-seed
elif [ "$Menu" == "Create Private Key from a DW Seed" ]; then
	dw-privkey
elif [ "$Menu" == "Create Public Key from DW Seed" ]; then
	dw-pubkey
elif [ "$Menu" == "Create Public key from a DW Master Public Key" ]; then
	masterpublickey
elif [ "$Menu" == "Generate Electrum-style Word Seed for a Deterministic Wallet Seed" ]; then
	mnemonicthis
elif [ "$Menu" == "Derive Deterministic Wallet Seed from Electrum-style Word Seed" ]; then
	demnemonicthis
else
	zenity --info --text="Thanks for using SX\!"
fi
