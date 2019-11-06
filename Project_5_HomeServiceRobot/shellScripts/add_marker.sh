#! /bin/bash

xterm -e "roslaunch robot homebot_world.launch" &
sleep 4
xterm -e "roslaunch robot amcl.launch" &
sleep 4
xterm -e " rosrun add_marker add_marker_beta "

