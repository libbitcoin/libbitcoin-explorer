#!/bin/bash

#
# Script to generate offline Bitcoin addresses
#
# Requires libbitcoin and sx
# https://github.com/libbitcoin/libbitcoin/
# https://github.com/spesmilo/sx
#
# Console dialogs:
# http://invisible-island.net/dialog/
# >sudo apt-get install dialog
#
# Qrcode generation:
# http://fukuchi.org/works/qrencode/
# >sudo apt-get install qrencode


# Generate a new seed
new_seed(){
	m_seed=$(sx "newseed")
}

# Convert seed to 12 words
display_mnemonic(){
	mnemonic=$(echo $m_seed | sx "mnemonic")
	dialog --backtitle "Console Paper Wallet: Mnemonic Seed" \
			--title "Electrum compatible 12-word mnemonic" \
			--msgbox "\n$mnemonic" \
			9 50
}

# Convert 12 words to seed
mnemonic_to_seed(){
	cmd=(dialog --backtitle "Console Paper Wallet: Mnemonic Seed Entry"
				--title "Electrum compatible 12-word mnemonic"
				--inputbox "Enter 12-word mnemonic (separated by spaces):"
				8 75)

	while :
	do
		words=$("${cmd[@]}" 2>&1 >/dev/tty)
		word_count=$(echo $words | wc -w)

		if [ $word_count -eq 0 ]
		then
			break 2
		fi

		if [ $word_count -eq 12 ]
		then
			# Verify mnemonic
			tmp_seed=$(echo $words | sx "mnemonic" | tr -d '\n')
			mnemonic=$(echo $tmp_seed | sx "mnemonic")

			if [ "$words" == "$mnemonic" ]
			then
				m_seed=$tmp_seed
				break 2
			else
				dialog --backtitle "Console Paper Wallet: Error" \
						--title "mnemonic error" \
						--msgbox "Invalid mnemonic. Try again." \
						9 50
			fi
		else
			dialog --backtitle "Console Paper Wallet: Error" \
					--title "mnemonic error" \
					--msgbox "Mnemonic must be 12 words separated by spaces." \
					9 50
		fi

	done
}

# Display Public Address
pub_addr(){
	re='^[0-9]+$'
	cmd=(dialog --backtitle "Console Paper Wallet: Public Address Select"
				--keep-tite
				--title "Address Index"
				--default-item "0"
				--inputbox "Which public address number?"
				10 36)

	while :
	do
		index=$("${cmd[@]}" 2>&1 >/dev/tty)
		if  [[ $index =~ $re ]]
		then
			pub_key=$(echo $m_seed | sx "genaddr" $index)
			qr_code=$(qrencode -s 10 -m 1 -t ASCII "$pub_key")
			qr_unicode=${qr_code//"#"/$unicode_box_char}
			dialog --backtitle "Console Paper Wallet: Public Address" \
					--no-collapse \
					--keep-tite \
					--title "Address[$index]: $pub_key" \
					--msgbox "$qr_unicode" \
					36 66
		  	break
		else break
		fi
	done
}

# Display Private Key
priv_key(){
	re='^[0-9]+$'
	cmd=(dialog --backtitle "Console Paper Wallet: Private Key Select"
				--keep-tite
				--title "Key Index"
				--inputbox "Which private key number?"
				10 36)

	while :
	do
		index=$("${cmd[@]}" 2>&1 >/dev/tty)
		if  [[ $index =~ $re ]]
		then
			priv_key=$(echo $m_seed | sx "genpriv" $index)
			qr_code=$(qrencode -s 10 -m 1 -t ASCII "$priv_key")
			qr_unicode=${qr_code//"#"/$unicode_box_char}
			dialog --backtitle "Console Paper Wallet: Private Key" \
					--no-collapse \
					--keep-tite \
					--title "Key[$index]: $priv_key" \
					--msgbox "$qr_unicode" \
					36 66
		  	break
		else break
		fi
	done
}

# Convert dice rolls 1-6 (base 6) to a 120-bit hexidecimal seed.
dice_to_seed(){
	seed=""
	prompt="Enter at least 50 dice rolls (numbers 1 through 6):"
	while [ ${#seed} -lt 32 ]; do
		cmd=(dialog --backtitle "Console Paper Wallet: Dice Roll Entry"
				--title "Dice Roll Seed:"$seed
				--inputbox "$prompt"
				8 75)
		roll=$("${cmd[@]}" 2>&1 >/dev/tty | tr -dc "1-6" )
		
		if [ $(echo $roll | wc -w) -eq 0 ]
		then
			break 2
		fi

		hex_roll=""
		for ((ii=0; ii<${#roll}; ii++)); do
			hex_roll=${hex_roll}$((${roll:ii:1}-1))		
		done
		hex_roll=$(echo "obase=16;ibase=6;"$roll | bc | tr '[:upper:]' '[:lower:]')
		seed=${seed}$hex_roll
		prompt="Enter more dice rolls (numbers 1 through 6):"
	done
	m_seed=$(echo ${seed:0:32})

	mnemonic=$(echo $m_seed | sx "mnemonic")
	dialog --backtitle "Console Paper Wallet: Mnemonic Seed" \
			--title "Electrum compatible 12-word mnemonic" \
			--msgbox "\n$mnemonic" \
			9 50
}

# Show Help Dialog
show_help(){
	prompt="\nConsole Paper Wallet uses an Electrum compatible, 128-bit random seed       \n"
	prompt=$prompt"to generate private keys. A random seed is created every time you run  \n"
	prompt=$prompt"the program. Create a new seed at any time and/or roll physical dice to\n"
	prompt=$prompt"ensure the software is not manipulating the random seed. Once you've   \n"
	prompt=$prompt"created a seed, it will be displayed above the main menu.              \n\n"
	prompt=$prompt"   *****************************************************************   \n"
	prompt=$prompt"      Show the mnemonic and record the 12 WORDS on paper or other      \n"
	prompt=$prompt"      long lasting material. If you lose the mnemonic, your            \n"
	prompt=$prompt"      bitcoins will be lost \Z1FOREVER\Zn.                             \n\n"
	prompt=$prompt"      Note that words in the mnemonic are all lowercase and are        \n"
	prompt=$prompt"      separated by a single <space> character. This mnemonic can       \n"
	prompt=$prompt"      be used to re-create a spending wallet in Electrum. See:         \n"
	prompt=$prompt"                          http://electrum.org                          \n"
	prompt=$prompt"   *****************************************************************   \n\n"
	prompt=$prompt"To recreate a seed from a prior session, select the                    \n"
	prompt=$prompt"\Z4\ZbCreate seed from mnemonic\Zn option and type in the 12 word mnemonic. \n\n"
	prompt=$prompt"All public addresses and private keys are pre-determined based on the  \n"
	prompt=$prompt"seed value. Enter an integer number to display the corresponding       \n"
	prompt=$prompt"deterministic, public address and private key.                          \n\n"
	prompt=$prompt"Record or scan the QR-Code of a public address to deposit funds. It is \n"
	prompt=$prompt"safe to share any public address unless you wish to remain anonymous.  \n\n"
	prompt=$prompt"Take care when recording or scanning any private Key. The only time    \n"
	prompt=$prompt"a private key should be used is immediately before spending all        \n"
	prompt=$prompt"the bitcoins in a specific public address.\n"
	dialog --backtitle "Console Paper Wallet: Help" \
				--title "How To Use" \
				--colors \
				--msgbox "$prompt" \
				36 75 
}

# Main Menu
main_menu(){

	while :
	do
		cmd=(dialog --backtitle "Console Paper Wallet: Main Menu"
					--keep-tite
					--no-cancel
					--help-button
					--menu "Current Seed: $m_seed"
					15 55 22)

		options=(1 "Show mnemonic"
					2 "Show public address"
					3 "Show private key"
					4 "Create new random seed"
					5 "Create seed from mnemonic"
					6 "Create seed from dice rolls"
					7 "Quit")

		choices=$("${cmd[@]}" "${options[@]}" 2>&1 >/dev/tty)

		for choice in $choices
		do
			case $choice in
				HELP)
					show_help
					break
					;;
				1)
					display_mnemonic
					break
					;;
				2)
					pub_addr
					break
					;;
				3)
					priv_key
					break
					;;
				4)
					new_seed
					break
					;;
				5)
					mnemonic_to_seed
					break
					;;
				6)
					dice_to_seed
					break
					;;
				7)
					(clear)
					break 2
					;;
			esac
		done
	done
}

unicode_box_char=$(echo -e "\xE2\x96\x88")
new_seed
main_menu
