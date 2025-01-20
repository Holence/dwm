#!/bin/bash
sudo apt install libx11-dev libxft-dev libxinerama-dev libxrandr-dev xorg
sudo apt install alsa-utils xbacklight
sudo apt install x11-xserver-utils feh redshift

sudo make && sudo make install

cp dotfile/.xsession ~/.xsession
cp dotfile/.Xresources ~/.Xresources
cp dotfile/.statusbar ~/.statusbar
sudo cp dotfile/30-touchpad.conf /etc/X11/xorg.conf.d/30-touchpad.conf
