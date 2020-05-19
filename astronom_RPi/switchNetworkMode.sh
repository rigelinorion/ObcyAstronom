#!/bin/bash
echo zmiana ustawień sieci
if [ -n "$(grep '#interface wlan0' '/etc/dhcpcd.conf')" ]
then
sudo sed -i 's/#interface wlan0/interface wlan0/;s/#static ip/static ip/;s/#nohook/nohook/' /etc/dhcpcd.conf
else
sudo sed -i 's/interface wlan0/#interface wlan0/;s/static ip/#static ip/;s/nohook/#nohook/' /etc/dhcpcd.conf
fi
echo restart serwera
sudo service dhcpcd restart
echo restart maszyny
sudo reboot
