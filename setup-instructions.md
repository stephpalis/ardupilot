Instructions Adopted From: https://ardupilot.org/dev/docs/building-setup-linux.html

1. Clone Repo ```git clone git@github.com:stephpalis/ardupilot.git```
2. Download gcc compiler ```https://firmware.ardupilot.org/Tools/STM32-tools/```
3. `sudo apt install cmake`
4. `sudo apt install genromfs`
5. `git checkout -b Copter-4.0 origin/Copter-4.0`
6. `Tools/environment_install/install-prereqs-ubuntu.sh` --> Fix any errors
7. ` git submodule update --init --recursive`
8. `./waf configure --board=skyviper-journey`
9. `./waf build --target=bin/arducopter -v` 


In order to make this build work, I had to comment out the last function in ArduCopter/toy_mode.cpp