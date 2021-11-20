# stc15f-controller-chigo-zhjt03
CHIGO air condition remote controller

## Features
* Logic "0" and Logic "1" are up to the NEC standard. 

## Wires
```
STC15F104W         5V                          5V
+--------+         |                           |
|        |         |                           | 
|    P3.3|--|KEY|--+       ---|IR|----|100R|---+
|        |               |/
|    P3.5|--|4K7|--------|  NPN
|        |               |\
|     GND|                 |
|        |                 |         
+--------+                GND
```
