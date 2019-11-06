#! /bin/bash

xterm -e "roslaunch robot robot_world.launch &
sleep 4
xterm -e "roslaunch robot amcl.launch "
