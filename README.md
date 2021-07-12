# Yuancon now has bright LEDs!!*
### *after a lot of modification and using an Arduino Leonardo instead of Yuan's STM32 based board

Current version: v1.1.2

As most people know, the Yuancon's LEDs are pretty dim. The aim of this project was to solve that and add a Dao-type secondary USB port to power the LEDs externally (using another USB port). This was achieved by drilling a hole in the Yuancon's casing next to the existing USB port, and mounting a Neutrik USB socket to act as an external port to the internal Arduino. The existing USB-C port was repurposed to provide a 5v power source to the LEDs.

The code is stripped out and modified version of LizardBean's code (https://github.com/lizardbeans/iidxsdvx). It has been tweaked to work as well as possible with the encoder used in Yuan's controllers - at the moment it works flawlessly, but is very sensitive. In the future I may try and implement some code to be able to adjust this sensitivity, or how much you have to turn the turntable before it fires.

There are also now two boot modes for either analogue turntable, or digital for use with LR2. Default boot of Arduino puts the turntable in analogue mode. This is perfect for IIDX Infinitas, or any other application that has true analogue turntable support. Hold key 7 while plugging in controller to enable Digital TT mode - turntable will report xAxis left/right, then return to 0 position. Ideal for LR2, but could do with some further tweaking to prevent misfires.

Finally, here is a crude MS paint diagram demonstrating the concept of powering arcade LEDs externally. 

![alt text](lighting_diagram.png "Arcade lighting diagram")

Only four buttons are shown - this would obviously be the 7 keys, and however many more buttons you want to add to the controller. I'm currently using the 7 keys and 4 option buttons (plus the turntable LED ring), and there is no dimming at all when all buttons are pressed.
 