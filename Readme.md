Its a very basic virtual 4001 cpu that i made in 4 days using c++
with zero knowledge of cpu`s before.

It can multiply, add, substract, divide two numbers.

It can print from reg0. Beep and it can write or read from/to file.

It has its own pseudo asm(basicaly binary code).

Also it has checks for overflow and underflow(very basic).

in main.cpp you can run it and edit memory then load it to cpu.

Feel free to use it or upgrade it :)

------------------------------------------------------------------------
Here is the list of instructions:

MOV_R0 ;moves val to r0

MOV_R1 ;moves val to r1

ADD ; r0 = r0 + r1

MUL ; r0 = r0 * r1

SUB ; r0 = r0 - r1

DIV ; r0 = r0 / r1

JE ; jumps to specified memory location if r0 equals r1

JNE ; jumps to specified memory location if r0 != r1

JM ; jumps to specified memory location

PRINT ; prints r0 from specified memory location

BEEP ; beeps (\a)

STORE ; stores r0 to specified memory location

CLEAR_R0 ; sets r0 to 0

CLEAR_R1 ; sets r1 to 0

HALT ; end of the program

NOP ; for readability
------------------------------------------------------------------------

Very basic program in Add.txt.

Also it starts from second memory address cuz cpu reserves 1 byte for jump address and the other one for extra halt!

to open a file you have to do this in menu(main.cpp)

select 5
press enter
select r
press enter
type filename
press enter
boom magic.

same goes with writing to file.

load instructions in memory
select 4
press enter
select r
press enter
type filename to make
press enter
boom magic

TODO: 
Add a printing func to symbols.

