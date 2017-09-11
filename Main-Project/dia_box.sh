#!/bin/sh
if zenity --question --text="USB has been detected, would you like to mount?"; then notify-send 'USB Detected'; 
	echo 0
else 
notify-send 'Failed to detect USB' ; 
	echo -1
fi
