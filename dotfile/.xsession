#!/bin/bash

# Set color temperature
redshift -x
redshift -O 4000

# use ARandR to generate a xrandr script
# . ~/.xrandr
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
feh --bg-fill ~/bg.jpg

# statusbar loop
~/.statusbar &

# to dwm
exec dwm
