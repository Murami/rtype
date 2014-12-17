#!/bin/sh

if [ $1 == "clean" ]
then
    echo "Removing build directory..."
    rm -rf build
    echo "[SUCCESS]"
    echo "Removing client binary..."
    rm -f client
    echo "[SUCCESS]"
else
    echo "Making build directory..."
    mkdir build
    echo "[SUCCESS]"
    cd build
    echo "Building Makefile..."
    cmake ..
    if [ $? == 0 ]
    then
	echo "[SUCCESS]"
	echo "Building project..."
	make
	if [ $? == 0 ]
	then
	    echo "[PROJECT BUILT SUCCESFULLY]"
	else
	    echo "[FAILED TO BUILD PROJECT]"
	fi
    else
	echo "[FAILED]"
    fi
fi
