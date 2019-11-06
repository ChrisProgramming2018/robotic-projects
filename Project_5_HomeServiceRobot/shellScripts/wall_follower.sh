#! /bin/bash

xterm -e "roslaunchroebot root_world.launch "&
sleep 4
xterm -e " roslaunch robot gmapping_demo.launch" &
sleep 4
xterm -e "roslaunch robot view_navigation.launch" &
sleep 4
xterm -e "rosrun wall_follower wall_follower"
