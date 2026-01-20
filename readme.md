# TI83+/TI84+ zeeslag

> [!CAUTION]
> use 2nd + quit to exit the program, turning off your calculator may cause memory corruption

requriements:

- the [z88dk toolkit](https://z88dk.org/site/) to build the project
- [ti connect CE](https://education.ti.com/en/products/computer-software/ti-connect-ce-sw) to upload the programs to your calculator

to build:

`zcc +ti83p -pragma-need=ansiterminal -pragma-define:ansicolumns=24 -o build/zeeslag.bin -create-app main.c -subtype=asm`

to run:

`Asm(ZEESLAG)` on your calculator, or you can upload and use `execzslg.8xp`, this is a wrapper around the assembly program.

how to play:

use the arrow keys to move your boat or cursor. When placing your ships use `+` to turn the ship, use `-` to place a ship or launch a bomb. `-` shows places you missed and `X` shows places you hit a ship.
