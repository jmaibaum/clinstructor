clinstructor
============

A free Instructor 50 emulator for the command line.


Compiling
---------

clinstructor should so far work both under Mac OSX (tested on 10.8) and
GNU/Linux (tested on a recent Arch Linux installation) with the usual present C
compilers (Apple's clang or GNU's GCC) and the respective standard libraries.
Normally, nothing more than just invoking `make` in this directory should be
necessary to leave you with the executable. Microsoft Windows is so far not
supported, but you can use a far more mature emulation software for even more
2650-based hardware called
[WinArcadia](http://amigan.1emu.net/releases/#amiarcadia) by James Jacobs.

Running
-------

You can run the program from the command line with the following syntax:

    ./clinstructor <INPUT-FILE> [<MEMORY-START-ADDRESS>]

__INPUT-FILE__ is a usual text file with the Signetics 2650 machine instructions
in ASCII (or compatible) hex characters (0--9, A--F). Whitespace gets skipped
and, from every two characters one 8-bit instruction or data byte is formed. You
find some example code in the `examples/` folder.

__MEMORY-START-ADDRESS__ is an optional parameter that is only used for the
command line debugging interface that currently shows the contents of 255 bytes
(one "page") from the emulated memory. With this parameter you can specify the
start address of the displayed page.


Usage Note
----------

Currently, this is pure alpha software---or even less. There is nothing more
inside than a basic Signetics 2650 emulation loop with 32 kB of emulated memory.
No interrupts, no other I/O operations. And don't expect correct timing. It will
just run as fast as your machine is able to execute my non-optimized first
attempt to program in C. It will, however, show you how fast this was compared
to a real 2650 running at a clock speed of ~895 kHz.

Nevertheless, I welcome any feedback on this code. Test it and send me bug
reports or fork it, improve it, and send me pull requests! Perhaps/hopefully,
this will once become a useful emulation software for this old system...
