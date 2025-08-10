#!/bin/bash

# for compiling dwm
echo "${COLOR_GREEN}install libx11-dev libxft-dev libxinerama-dev...${COLOR_END}"
sudo apt install libx11-dev libxft-dev libxinerama-dev

# for changing volume
echo "${COLOR_GREEN}install alsa-utils...${COLOR_END}"
sudo apt install alsa-utils

# for changing backlight (laptop)
# echo "${COLOR_GREEN}install xbacklight...${COLOR_END}"
# sudo apt install xbacklight

# for screenshot
echo "${COLOR_GREEN}install flameshot...${COLOR_END}"
sudo apt install flameshot

# for startx
echo "${COLOR_GREEN}install xinit...${COLOR_END}"
sudo apt install xinit

# for xrandr (in .xsession) and xsetroot (in .statusbar)
echo "${COLOR_GREEN}install x11-xserver-utils...${COLOR_END}"
sudo apt install x11-xserver-utils

# for background image
echo "${COLOR_GREEN}install feh...${COLOR_END}"
sudo apt install feh

# for warmer screen color
echo "${COLOR_GREEN}install redshift...${COLOR_END}"
sudo apt install redshift

sudo make && sudo make install

cp dotfile/.xsession ~/.xsession
chmod +x ~/.xsession

cp dotfile/.statusbar ~/.statusbar
sudo cp dotfile/30-touchpad.conf /etc/X11/xorg.conf.d/30-touchpad.conf
