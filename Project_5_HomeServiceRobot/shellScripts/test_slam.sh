#! /bin/bash

xterm -e "roslaunch robot robot_world.launch" &
sleep 4
xterm -e "roslaunch robot gmapping_demo.launch" &
sleep 4
xterm -e "roslaunch robot view_navigation.launch" &
sleep 4
xterm -e "roslaunch robot keyboard_teleop.launch"
