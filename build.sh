#!/bin/sh

if [ "$1" = "--help" ] || [ "$1" = "-h" ]
then
	echo "Build ArduCopter for the SkyViper Journey.\n\t--help, -h\tDisplay this help information.\n\t--clean, -c\tPerform a clean build."
elif [ "$1" = "--clean" ] || [ "$1" = "-c" ]
then
	echo "Cleaning..."
	./waf distclean
	echo "Cleaning done."
fi


echo "Configuring..."
./waf configure --board=skyviper-journey
echo "Configuring done."
echo "Building..."
./waf build --target=bin/arducopter -v
echo "building done."
