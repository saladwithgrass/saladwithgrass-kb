# Thank you 
This repo would not be possible without some other repos, like 
[RPi-Pico-Baremetal](https://github.com/carlosftm/RPi-Pico-Baremetal/) by carlosftm
and 
[raspberrypi-pico](https://github.com/dwelch67/raspberrypi-pico) by dwelch67

# About this repo 
This repo is my attempt at building my own keyboard and it's firmware.
To know more read the `README.txt` that was copied from [raspberrypi-pico](https://github.com/dwelch67/raspberrypi-pico) by dwelch67.

# Building
To build this repo just run `make`. Note, that arm GNU toolchain is required.
# Uploading
You can use `./upload.sh`.
```
./upload.sh /dev/sdb1 build/keyboard.uf2
```
/dev/sdb1 is RPi in BOOTSEL mode. This is an example, it may be different on your system.
