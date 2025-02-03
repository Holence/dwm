#!/bin/bash

# Set color temperature
redshift -x
redshift -O 4000

# use ARandR to generate a xrandr script
# . ~/.xrandr

# doesn't work after installing nvidia driver!
close_DP_if_has_two_monitor () {
    s=$(grep "^connected" /sys/class/drm/card*/status)
    n=$(echo "$s" | wc -l)
    if [[ $n == 2  ]]; then
        DP=$(echo "$s" | grep -oP '(?<=-).*DP.*(?=/)')
        xrandr --output "$DP" --off
    fi
}
close_DP_if_has_two_monitor
xrandr --dpi 100

# set a background photo
feh --no-fehbg --bg-fill ~/bg.jpg

# Start Polkit authentication agent
/usr/lib/policykit-1-gnome/polkit-gnome-authentication-agent-1 &

# statusbar loop
bash ~/.statusbar &

# to dwm
exec dwm
