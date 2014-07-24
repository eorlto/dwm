#!/bin/bash
setxkbmap -layout es
while true; do
	#BATTERYSTATE=$( acpi -b | awk '{ split($5,a,":"); print substr($3,0,2), $4, "["a[1]":"a[2]"]" }' | tr -d ',' )
	#VOLUME=$( amixer sget Master | grep -e 'Mono:' | sed 's/[^\[]*\[\([0-9]\{1,3\}%\).*\(on\|off\).*/\2 \1/' | sed 's/off/M/' | sed 's/on //' )
	DATE=$( date +"%R" )
	xsetroot -name "${DATE}"
	#xsetroot -name "V: ${VOLUME} | ${BATTERYSTATE} | ${DATE}"
   sleep 5
done &

wmname LG3D
trayer --widthtype request --align right --height 16 --transparent true --alpha 0 --tint 0x0B0B0B &
nm-applet &
cbatticon -u 10 -i notification -c "systemctl poweroff" -l 15 -r 2 -i symbolic &
volumeicon &

startdwm
