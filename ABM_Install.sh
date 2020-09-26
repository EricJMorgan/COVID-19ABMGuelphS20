#!/bin/bash
# This script can be used to quickly install the required components for the project

read -p "Are you sure you want to setup and install all required components? [y/n]" -n 1 -r
echo  # move to new line

if [[ $REPLY =~ ^[Yy]$ ]]
then
    # compile the CPP files
    make library

    # install items through available pip command, if both pip alias' are available it will run twice
    # but only install packages the first time
    pip3 install -r requirements.txt
    pip install -r requirements.txt

    # install boost
    sudo apt-get install libboost-all-dev

    echo "Setup Complete!"
    echo 
fi
