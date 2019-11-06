#! /bin/bash

xterm -e "roslaunch robot robot_world.launch" &
sleep 4
xterm -e "roslaunch homebot amcl.launch" &
sleep 4
xterm -e "rosrun pick_objects pick_objects_beta"
