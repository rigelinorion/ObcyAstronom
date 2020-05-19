#!/bin/bash
sudo cp ./smb.conf /etc/samba/smb.conf & 
sudo cp ./config.txt /boot/config.txt &
sudo cp ./obcyastronom.service /etc/systemd/system/obcyastronom.service &
sudo cp ./indi.service /etc/systemd/system/indi.service &
sudo systemctl enable obcyastronom &
sudo systemctl start obcyastronom 