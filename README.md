# DoorLockCode
The arduino sketch to control the RFID door lock

# IDE

* [Download Energia Arduino IDE](http://energia.nu/download/) - Download a compiled application for Linux, Mac OS X, or Windows.

# Configuration

* Set the Board to Launchpad w/ msp430g2553 (16 mhz)  
* Copy the rules file for the programmer
```
sudo cp 71-ti-permissions.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo service udev restart
```
# Hardware

The Jumper from the programmer to the MSP430 labled RST needs to be connected during programming, then removed after programming. The system also needs to be power cycled after programming. 
