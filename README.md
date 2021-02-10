
![](/images/cacazi-a8.jpg)

Continuing the automation of the apartment, the idea came to make a doorbell button with ZigBee support. Sergey decided to use the factory model CACAZI A8 as a case with an acceptable cost - about 230 rubles at the time of original writing.

![](/images/cacazi-a8-zigbee_scheme.jpg)

The heart of the device is the popular E18-MS1-IPX module. You can also use the version with a built-in antenna, but Sergey thought that the signal quality behind the metal entrance door would not be very good.

The circuitry is designed in such a way that power is supplied from a 12V23A battery. In theory, its capacity should be sufficient for a fairly long operating time (the stabilizer has a very small voltage drop). However, this approach loses the ability to control the charge (the value will always be at 100%). How justified this approach is - time will tell.

When using an external antenna, it can be attached to the inside of the front of the case. Particular attention should be paid to the installation site of the U1-U4: depending on the selected model, a different seat is used (only one microcircuit can be installed at a time!). The main button and battery holders can be taken from the original board.

![](/images/ywtetx8fium.jpg)

![](/images/img_20200619_153949.jpg)


Initially, the printed board was developed for the well-known Jager_magnet firmware from @DJONvl, but during the tests it was revealed that it behaves incorrectly with wireless modules from Ebyte. Then, thanks to the efforts of @anonymass, a new one was written, which works great and is open source, for which many thanks to him! It can also be used with a universal ZigBee module to create your own devices based on it.

Sprint Layout 6.0 file: cacazi-a8-zigbee_1.2mm.lay6 (59.3 Kb)  
Gerber files: cacazi-a8-zigbee_1.2mm_gerber.zip (13.7 Kb)  

P.S. Additionally, Sergey drew a printed circuit board with a "classic" power system for CR2032. With it, the battery charge should be displayed correctly, but the capacity of such a battery will naturally be much lower. However, it is not yet known how the 12V23A version will behave in the long term, so for self-repetition Sergey recommend using the version below.

Sprint Layout 6.0 file: cacazi-a8-zigbee_cr2032_1.2mm.lay6 (36.7 Kb)  
Gerber files: cacazi-a8-zigbee_cr2032_1.2mm_gerber.zip (9.47 Kb)


### How to add device into zigbe2mqtt
Just try to join. If any errros - use [external converters](https://www.zigbee2mqtt.io/information/configuration.html#external-converters-configuration) feature

Converter file located [here](https://github.com/diyruz/reed/blob/master/z2m-converter/DIYRuZ_Reed.js)


### How to join
#### If device in FN (factory new) state:
1. Press and hold button (1) for 2-3 seconds, until device start flashing led
2. Wait, in case of successfully join, device will flash led 5 times
3. If join failed, device will flash led 3 times

#### If device in a network:
1. Hold button (1) for 10 seconds, this will reset device to FN (factory new) status
2. Go to step 1 for FN device


### Files to reproduce
* [Gerbers and lay6 files](https://github.com/diyruz/reed/tree/master/hardware) by [AvdeevSV](https://io-net.ru/author/avdeevsv/)  
* [Firmware](https://github.com/diyruz/reed/releases) by [@anonymass](https://t.me/anonymass)  


[Original post by AvdeevSV](https://io-net.ru/knopka-dvernogo-zvonka-zigbee)  
