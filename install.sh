#!/bin/bash
sudo apt install libx11-dev libxft-dev libxinerama-dev libxrandr-dev xorg
sudo apt install alsa-utils xbacklight
sudo apt install thunar xfce4-terminal gnome-keyring
sudo apt install x11-xserver-utils feh redshift
sudo apt install make build-essential

sudo make && sudo make install

cp dotfile/.xsession ~/.xsession
cp dotfile/.Xresources ~/.Xresources
cp dotfile/.statusbar ~/.statusbar
sudo cp dotfile/30-touchpad.conf /etc/X11/xorg.conf.d/30-touchpad.conf
