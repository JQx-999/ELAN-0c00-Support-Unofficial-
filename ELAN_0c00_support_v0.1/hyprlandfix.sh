#!/bin/bash
xhost +local:root
sudo ./launch.sh
xhost -local:root

#use sudo pacman -S xorg-xhost for Arch/Hyprland
