# Set color temperature
redshift -x
redshift -O 4000

# use ARandR to generate a xrandr script
. ~/.xrandr

# set a background photo
feh --bg-fill ~/bg.jpg

# statusbar loop
bash ~/.statusbar &

# to dwm
exec dwm
