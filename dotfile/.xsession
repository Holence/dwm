#!/bin/bash

export QT_QPA_PLATFORMTHEME=gtk3

# Set color temperature
redshift -x -O 4000

close_DP_if_has_HDMI () {
    s=$(xrandr)
    has_HDMI=$(echo "$s" | grep -oP '.*HDMI.*? connected')
    if [[ $has_HDMI ]]; then
        DP=$(echo "$s" | grep -oP '.*DP.*?(?= connected)')
        xrandr --output "$DP" --off
    fi
}
close_DP_if_has_HDMI
xrandr --dpi 100

# start polikit agent
lxpolkit &

# set a background photo
hsetroot -cover ~/bg.jpg

# statusbar loop
bash ~/.statusbar &

# to dwm
ln -sf /dev/null ~/.xsession-errors # dont write .xsession-errors
exec dwm
