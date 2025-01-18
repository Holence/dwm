#!/bin/bash

# Set color temperature
redshift -x
redshift -O 4000

# use ARandR to generate a xrandr script
# . ~/.xrandr
xrandr --dpi 100

# set a background photo
feh --bg-fill ~/bg.jpg

# statusbar loop
~/.statusbar &

# to dwm
exec dwm
