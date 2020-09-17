#!/bin/bash

# Install X11 XShm extension
sudo apt-get install --assume-yes libxext-dev 

# Setup your OS
sudo mkdir /usr/X11 2>/dev/null
sudo mkdir /usr/X11/include 2>/dev/null
sudo mkdir /usr/X11/lib 2>/dev/null
sudo mkdir /usr/local/lib 2>/dev/null
cd minilibx 2>/dev/null
make 2>/dev/null
sudo cp mlx.h /usr/X11/include 2>/dev/null
sudo cp mlx.h /usr/local/include 2>/dev/null
sudo cp libmlx.a /usr/X11/lib 2>/dev/null
sudo cp libmlx.a /usr/local/lib 2>/dev/null
echo "\n# Finished"