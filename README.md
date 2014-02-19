clinstructor
============

A cross-platform Instructor 50 emulator for the command line.


Development Documentation
-------------------------

Place CC updating code at the end of the emulation loop. This should decrease
code size a lot, since all instructions except `HALT`, `NOP`, `STRR`, `STRA`,
`LPSU`, `CPSU`, `PPSU`, `WRTD/C/E`, and all branch instructions affect the CC.
