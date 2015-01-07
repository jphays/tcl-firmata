tcl-firmata
===========

Arduino Firmata implementation for TCL (Total Control Lighting RGB LED) light control.

Currently implements a single sysex handler that receives RGB values for the entire strand and updates the lights. 
The sysex implementation in the Firmata library supplied with Arduino only supports up to 32 bytes per message, 
which is a bit restrictive. I modified the library to handle up to 255 bytes in the current implementation.

__TODO:__
- add support for sending developer sheild input values
- add protocol support for packing color values into 7-bit bytes
- possible support for multi-message blocks of color and a separate message for rendering
