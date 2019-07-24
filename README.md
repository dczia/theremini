# Theremini

What's better than a laser theremin?  How about a laser theremin SAO?!

This SAO unfortunately does not make any noise or produce lasers, but it does have:

 - Microchip AVR attiny1616 8-bit microcontroller
 - 5 touch-sensitive buttons
 - 6 red LEDs arranged about the tape spool holes
 - Reprogrammable via UPDI via the SAO connector!
 
 
![Theremini Front](https://github.com/dczia/theremini/blob/master/Images/theremini-front.png?raw=true)

![Theremini back](https://github.com/dczia/theremini/blob/master/Images/theremini-back.png?raw=true)

Use avr-gcc to compile the code - just run a 'make'

You'll need a UPDI programmer to program this guy.  I modded a 'ATTINY817 XPLAINED MINI' board to use as a programmer. See [this link](https://www.jsykora.info/2019/04/avr-updi-programmer-from-attiny817-xplained-mini/) for a howto.

Gerbers are included - the panel directory is the panel I actually ordered.
