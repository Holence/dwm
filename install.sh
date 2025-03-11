#!/bin/bash
echo "${COLOR_GREEN}install libx11-dev libxft-dev libxinerama-dev libxrandr-dev xorg...${COLOR_END}"
sudo apt install libx11-dev libxft-dev libxinerama-dev libxrandr-dev xorg

# terminal and file manager
echo "${COLOR_GREEN}install xfce4-terminal...${COLOR_END}"
sudo apt install xfce4-terminal
echo "${COLOR_GREEN}install thunar...${COLOR_END}"
sudo apt install thunar
# amixer
echo "${COLOR_GREEN}install alsa-utils...${COLOR_END}"
sudo apt install alsa-utils
# change backlight
echo "${COLOR_GREEN}install xbacklight...${COLOR_END}"
sudo apt install xbacklight
# screenshot
echo "${COLOR_GREEN}install flameshot...${COLOR_END}"
sudo apt install flameshot
# for .xsession
echo "${COLOR_GREEN}install x11-xserver-utils...${COLOR_END}"
sudo apt install x11-xserver-utils
echo "${COLOR_GREEN}install feh...${COLOR_END}"
sudo apt install feh
echo "${COLOR_GREEN}install redshift...${COLOR_END}"
sudo apt install redshift
echo "${COLOR_GREEN}install policykit-1-gnome...${COLOR_END}"
sudo apt install policykit-1-gnome

sudo make && sudo make install

cp dotfile/.xsession ~/.xsession
chmod +x ~/.xsession

cp dotfile/.statusbar ~/.statusbar
sudo cp dotfile/30-touchpad.conf /etc/X11/xorg.conf.d/30-touchpad.conf
