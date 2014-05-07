#!bin/sh

###################
###################
#### FUNCTIONS ####
###################
###################

###################
## Select a File ##
###################

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

##########################
## Create a new keypair ##
##########################

function keypair {
	sx newkey > privatekey-$(date +%y-%m-%d-%s).txt
	cat privatekey-$(date +%y-%m-%d-%s).txt | sx addr > publickey-$(date +%y-%m-%d-%s).txt
	zenity --info --text="Open the publickey-DATE.txt and privatekey.txt files to obtain Bitcoin keys."
}
##################################
## Create a new stealth address ##
##################################

function stealth {
	sx stealth-new > stealthkeys-$(date +%y-%m-%d-%s).txt
	zenity --info --text="Open the stealthkeys-DATE.txt file to obtain your stealth key pairs."
}

########################################
## Obtain stealth transaction details ##
########################################

function sendstealth {
	sx stealth-send $(zenity --entry --title="Stealth Transaction Details" --text="Enter the stealth public address of the recipient.") > stealthrecipientaddr-$(date +%y-%m-%d-%s).txt
	zenity --info --text="Open the stealthrecipient-DATE.txt file to obtain the ephemeral (shared secret) and the recipient's Bitcoin public key."	
}

#######################################
## Check stealth transaction details ##
#######################################

function receivestealth {
	yourstealthpriv=$(zenity --entry --title="Stealth Transaction Details" --text="Enter the stealth transaction ephemeral key.")
	ephem=$(zenity --entry --title="Stealth Transaction Details" --text="Enter your stealth private key.")
	sx stealth-recv $yourstealthpriv $ephem > stealthbitcoins-$(date +%y-%m-%d-%s).txt
	zenity --info --height=150 --text="Open the stealthbitcoins-DATE.txt file to obtain the Bitcoin key pairs from the stealth transaction. If your ephemeral and/or stealth keys were incorrect, this text file will be blank."
}

####################
## Create QR code ##
####################

function qrcodegen {
	sx qrcode $(zenity --entry --title="Input Bitcoin Address" --text="Enter the public key for your Bitcoin address. Make sure 'qrencode' is installed (see README.md") qrcode-$(date +%y-%m-%d-%s).png
	zenity --info --height=150 --text="Open the 'qrcode-DATE.png' to view your QR code."
}

##############################################
## Create a 2 of 3 Multisignature Rawscript ##
##############################################

function twoofthreemultisig {
	oneofthree=$(zenity --entry --title="Multisignature Transaction (2-3): Address 1." --text="Enter the uncompressed public key for address 1.")
	twoofthree=$(zenity --entry --title="Multisignature Transaction (2-3): Address 2." --text="Enter the uncompressed public key for address 2.")
	threeofthree=$(zenity --entry --title="Multisignature Transaction (2-3): Address 3." --text="Enter the uncompressed public key for address 3.")
	addroneofthree="$(echo $oneofthree | sx addr)"
	addrtwoofthree="$(echo $twoofthree | sx addr)"
	addrthreeofthree="$(echo $threeofthree | sx addr)"
	validaddroneofthree=$(sx validaddr $addroneofthree)
	validaddrtwoofthree=$(sx validaddr $addrtwoofthree)
	validaddrthreeofthree=$(sx validaddr $addrthreeofthree)
	if [[ -z "$oneofthree" || -z "$twoofthree" || -z "$threeofthree" ]]; then
		zenity --info --title="Multisignature Fail" --text="One of the addresses is empty, so this isn't going to work"
	elif [[ "$validaddroneofthree" == "Status: Success" || "$validaddrtwoofthree" == "Status: Success" ||  "$validaddrthreeofthree" == "Status: Success" ]]; then
		sx rawscript 2 [ $oneofthree ] [ $twoofthree ] [ $threeofthree ] 3 checkmultisig > msig-two-of-three-$(date +%y-%m-%d-%s).script
		cat msig-two-of-three-$(date +%y-%m-%d-%s).script | sx scripthash > msig-two-of-three-$(date +%y-%m-%d-%s).txt
		zenity --info --height=150 --title="Multisignature (2-3) Bitcoin Address" --text=$(cat msig-two-of-three-$(date +%y-%m-%d-%s).script | sx scripthash)
		zenity --info --height=150 --text="A copy of the rawscript and public Bitcoin address for your multisignature address can be found in 'msig-address-DATE.txt'."
	else
		zenity --info --title="Multisignature Fail" --text="The pubkeys you entered were not valid. Remember this is the uncompressed version of your address."
	fi
}

##############################################################
## Create a Deterministic Wallet Seed and Master Public Key ##
##############################################################

function dw-seed {
	sx newseed > dw-seed-$(date +%y-%m-%d-%s).seed
	cat dw-seed-$(date +%y-%m-%d-%s).seed | sx mpk > master_public-$(date +%y-%m-%d-%s).key
	zenity --info --height=150 --title="Deterministic Wallet" --text="Deterministic wallet created! Open the 'dwallet-DATE.key' file to obtain your seed. Open the 'master_public-DATE.key' file to obtain your master public key."
}

###########################################################
## Create a Private Key from a Deterministic Wallet Seed ##
###########################################################

function dw-privkey {
	selectkeys
	cat "$FILE" | sx genpriv $(zenity --entry --title="Deterministic Wallet Private Key from wallet seed" --text="Enter the private key number.") > DW-privkey-$(date +%y-%m-%d-%s).txt
	zenity --info --height=150 --title="Deterministic Wallet" --text="You have successfully generated a Bitcoin private key from a deterministic wallet seed. Open the 'DW-privkey-DATE.txt' file to obtain it."
}

##########################################################
## Create a Public Key from a Deterministic Wallet Seed ##
##########################################################

function dw-pubkey {
	selectkeys
	cat "$FILE" | sx genaddr $(zenity --entry --title="Deterministic Wallet Public Key from wallet seed" --text="Enter the public key number.") > DW-pubkey-$(date +%y-%m-%d-%s).txt
	zenity --info --height=150 --title="Deterministic Wallet" --text="You have successfully generated a Bitcoin public key from a deterministic wallet seed. Open the 'DW-pubkey-DATE.txt' file to obtain it."
}

##################################################
## Create a Public Key from a Master Public Key ##
##################################################

function masterpublickey {
	selectkeys
	cat "$FILE" | sx genaddr $(zenity --entry --title="Deterministic Wallet Public Key from master public key" --text="Enter the public key number.") > DW-pubkey-$(date +%y-%m-%d-%s).txt
	zenity --info --height=150 --title="Deterministic Wallet" --text="You have successfully generated a Bitcoin public key from a master public key. Open the 'DW-pubkey-DATE.txt' file to obtain it."
}

################################################################################
## Convert Deterministic Wallet Seed into an Electrum Compatible 12 Word Seed ##
################################################################################

function mnemonicthis {
	selectkeys 
	cat "$FILE" | sx mnemonic > Electrum-"$(basename $FILE)".txt
	zenity --info --height=150 --title="Deterministic Wallet" --text="You have successfully generated an Electrum-style 12 word seed from a deterministic wallet seed. Open the 'Electrum.txt' file to obtain it."
}

#######################################################################
## Convert an Electrum 12 Word Seed into a Deterministic Wallet Seed ##
#######################################################################

function demnemonicthis {
	echo $(zenity --entry --title="Deterministic Wallet Public Key from 12 Word Seed" --text="Enter the 12 word seed.") | sx mnemonic > dw-wallet-$(date +%y-%m-%d-%s).txt
	zenity --info --height=150 --title="Deterministic Wallet" --text="You have successfully converted a 12 word seed to the original seed. Open the 'dw-wallet-DATE.txt' file to obtain it."
}

########################################
## Check Balance of a Bitcoin Address ##
########################################

function checkbalance {
	balanceaddress=$(sx balance $(zenity --entry --title="Bitcoin Address" --text="Enter the Bitcoin Address"))
	zenity --info --title="Balance of Bitcoin Address" --text="$balanceaddress"
}

########################################
## Check History of a Bitcoin Address ##
########################################

function checkhistory {
	historyaddress=$(sx history $(zenity --entry --title="Bitcoin History" --text="Enter the Bitcoin Address"))
	zenity --info --title="History of Bitcoin Address" --text="$historyaddress"
}

###########################################################
## Create an unsigned offline transaction for one output ##
###########################################################

function unsignedtx {
	OUTPUT=$(zenity --forms --title="Unsigned Offline Transaction" --text="Please enter the following field carefully." \
	--separator="," \
	--add-entry="What is the input hash (not the address)?" \
	--add-entry="What is the destination address?" \
	--add-entry="How much to send to destination address (in Satoshis)?" \
	--add-entry="What is the change address?" \
	--add-entry="How much to send to change address (in Satoshis)?"\ )

	accepted=$?

	if ((accepted != 0)); then
    		echo "something went wrong"
    		exit 1
	fi

	inputhash=$(awk -F, '{print $1}' <<<$OUTPUT)
	destinationaddr=$(awk -F, '{print $2}' <<<$OUTPUT)
	outputquantity=$(awk -F, '{print $3}' <<<$OUTPUT)
	changeaddr=$(awk -F, '{print $4}' <<<$OUTPUT)
	changequantity=$(awk -F, '{print $5}' <<<$OUTPUT)

	sx mktx txfile-unsignedtx-$(date +%y-%m-%d-%s).txt --input $inputhash:1 --output $destinationaddr:$outputquantity --output $changeaddr:$changequantity
	zenity --info --text="$(sx showtx txfile-unsignedtx-$(date +%y-%m-%d-%s).txt)"
	zenity --info --title="Unsigned Offline Transaction" --text="You have successfully created an unsigned offline transaction. No bitcoins have been sent, you still need to sign the 'tx-file-unsignedtx-DATE.txt file with your private key and broadcast it before anything is sent to the network. Review the values carefully... seriously, I mean it!"
}

##################################
## Backend for multiple outputs ##
##################################

function daoutputs {

	START=1
	END=$(zenity --entry --title="Offline Transaction" --text="How many outputs in this transaction?")

	for (( c=$START; c<=$END; c++ ))
	do
		echo -n "--output $(zenity --entry --title="Offline Transaction" --text="What is the destination address?"):$(zenity --entry --title="Offline Transaction" --text="What is the quantity of Satoshis to send")" ""
	done
}

##################################################################
## Create an unsigned offline transaction with multiple outputs ##
##################################################################

# Menu

function multioutputmenu {
	donationamt=$(zenity --entry --title="Charity Output" --text="What is the amount of bitcoin you would like to donate (in Satoshis)?")
	multioutputmenu=$(zenity --list --radiolist --width=1100 --height=400\
	--text="Select an option from below. An additional output will be created for your transaction to donate $donationamt Satoshis to your selected charity or organisation." --title="Charity Output Donation" \
	--column="Select" --column="Charity" --column="Description" \
	FALSE "None" "Do not make any donations." \
	FALSE "Sean's Outpost" "Sean's Outpost provides both food and shelter for the homeless in Pensacola, Florida." \
	FALSE "Wikileaks" "Secrets are their business." \
	FALSE "unSYSTEM" "Creators of libbitcoin, SX, DarkWallet, DarkMarket and many more projects to come." \
	FALSE "Satoshi Nakamoto Institute" "An organisation dedicated to the legacy of Satoshi Nakamoto." \
	FALSE "TOR Project" "Essential software dedicated to maintaing privacy and anonymity." \
	FALSE "Free Software Foundation" "The Free Software Foundation (FSF) is a nonprofit with a worldwide mission to promote computer user freedom and to defend the rights of all free software users." )

# Selected Transactions

	if [ "$multioutputmenu" == "None" ]; then
		inputhash=$(zenity --entry --title="Unsigned Offline Transaction" --text="What is the input hash (note: not the address)?")
		sx mktx txfile-unsignedtx-$(date +%y-%m-%d-%s).txt --input $inputhash:1 $(daoutputs)
	elif [ "$multioutputmenu" == "Sean's Outpost" ]; then
		inputhash=$(zenity --entry --title="Unsigned Offline Transaction" --text="What is the input hash (note: not the address)?")
		sx mktx txfile-unsignedtx-$(date +%y-%m-%d-%s).txt --input $inputhash:1 $(daoutputs) --output 1M72Sfpbz1BPpXFHz9m3CdqATR44Jvaydd:$donationamt
	elif [ "$multioutputmenu" == "Wikileaks" ]; then
		inputhash=$(zenity --entry --title="Unsigned Offline Transaction" --text="What is the input hash (note: not the address)?")
		sx mktx txfile-unsignedtx-$(date +%y-%m-%d-%s).txt --input $inputhash:1 $(daoutputs) --output 1HB5XMLmzFVj8ALj6mfBsbifRoD4miY36v:$donationamt
	elif [ "$multioutputmenu" == "unSYSTEM" ]; then
		inputhash=$(zenity --entry --title="Unsigned Offline Transaction" --text="What is the input hash (note: not the address)?")
		sx mktx txfile-unsignedtx-$(date +%y-%m-%d-%s).txt --input $inputhash:1 $(daoutputs) --output 32wRDBezxnazSBxMrMqLWqD1ajwEqnDnMc:$donationamt
	elif [ "$multioutputmenu" == "Satoshi Nakamoto Institute" ]; then
		inputhash=$(zenity --entry --title="Unsigned Offline Transaction" --text="What is the input hash (note: not the address)?")
		sx mktx txfile-unsignedtx-$(date +%y-%m-%d-%s).txt --input $inputhash:1 $(daoutputs) --output 1QGEHm62AF674C46zWjbRXw5vH3aS5d63n:$donationamt
	elif [ "$multioutputmenu" == "TOR Project" ]; then
		inputhash=$(zenity --entry --title="Unsigned Offline Transaction" --text="What is the input hash (note: not the address)?")
		sx mktx txfile-unsignedtx-$(date +%y-%m-%d-%s).txt --input $inputhash:1 $(daoutputs) --output 15RT6H7YeP6ohxs43r9fVVakzFoQPcov9z:$donationamt
	elif [ "$multioutputmenu" == "Free Software Foundation" ]; then
		inputhash=$(zenity --entry --title="Unsigned Offline Transaction" --text="What is the input hash (note: not the address)?")
		sx mktx txfile-unsignedtx-$(date +%y-%m-%d-%s).txt --input $inputhash:1 $(daoutputs) --output 1PC9aZC4hNX2rmmrt7uHTfYAS3hRbph4UN:$donationamt
		elif [ "$multioutputmenu" == "Free Software Foundation" ]; then
		inputhash=$(zenity --entry --title="Unsigned Offline Transaction" --text="What is the input hash (note: not the address)?")
		sx mktx txfile-unsignedtx-$(date +%y-%m-%d-%s).txt --input $inputhash:1 $(daoutputs) --output $(zenity --entry --title="Charity Output" --text="What is the address you would like to donate to?"):$donationamt
	else
		zenity --info --text="No transaction made."
	fi
}

#############################################
## Display an unsigned offline transaction ##
#############################################

function showofflinetransaction {
	zenity --info --text="$(sx showtx < $(zenity --file-selection --title="Select Offline Transaction txt file"))"
}

##############################
##############################
#### MENU OUTPUTS TO VARS ####
##############################
##############################

##########################################################################################
## Create a variable that is the output of the user's selection in the list dialog box. ##
##########################################################################################

Menu=$(zenity --list --radiolist --width=1100 --height=400 \
--text="Select an action from the list below" --title="SX Tools Menu" \
--column="Select" --column="Action" --column="Description" \
FALSE "Check Balance" "Check the balance of a Bitcoin address" \
FALSE "Check History" "Check the history of a Bitcoin address" \
FALSE "New Address" "Generate a new Bitcoin address" \
FALSE "Create unsigned offline transaction for multiple outputs" "For creating transactions with more than one output. These transactions need to be signed with the private key before broadcasting to the network." \
FALSE "Display Offline Transaction" "Dislay the unsigned offline transaction" \
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


#######################
#######################
#### SX Tools Menu ####
#######################
#######################

if [ "$Menu" == "Check Balance" ]; then
	checkbalance
elif [ "$Menu" == "Check History" ]; then
	checkhistory
elif [ "$Menu" == "New Address" ]; then
	keypair
elif [ "$Menu" == "Create unsigned offline transaction for multiple outputs" ]; then
	multioutputmenu
elif [ "$Menu" == "Display Offline Transaction" ]; then
	showofflinetransaction
elif [ "$Menu" == "Stealth Address" ]; then
	stealth
elif [ "$Menu" == "Send Stealth Transaction" ]; then
	sendstealth
elif [ "$Menu" == "Receive Stealth Transaction" ]; then
	receivestealth
elif [ "$Menu" == "Create QR code" ]; then
	qrcodegen
elif [ "$Menu" == "Create Multisignature Address" ]; then
	twoofthreemultisig
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
