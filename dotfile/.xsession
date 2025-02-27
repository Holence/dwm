#!/bin/bash

export QT_QPA_PLATFORMTHEME=gtk3

# Set color temperature
redshift -x
redshift -O 4000

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

# set a background photo
feh --no-fehbg --bg-fill ~/bg.jpg

# Start Polkit authentication agent
/usr/lib/policykit-1-gnome/polkit-gnome-authentication-agent-1 &

# statusbar loop
bash ~/.statusbar &

# to dwm
exec dwm
