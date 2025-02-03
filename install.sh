#!/bin/bash
sudo apt install libx11-dev libxft-dev libxinerama-dev libxrandr-dev xorg

# terminal and file manager
sudo apt install xfce4-terminal
sudo apt install thunar
# amixer
sudo apt install alsa-utils
# change backlight
sudo apt install xbacklight
# screenshot
sudo apt install flameshot
# for .xsession
sudo apt install x11-xserver-utils feh redshift policykit-1-gnome

sudo make && sudo make install

cp dotfile/.xsession ~/.xsession
chmod +x ~/.xsession

cp dotfile/.statusbar ~/.statusbar
sudo cp dotfile/30-touchpad.conf /etc/X11/xorg.conf.d/30-touchpad.conf
