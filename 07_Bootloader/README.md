07_Bootloader

===============

This sample implements a bootloader. after initializing the board, including the DDR chip.
it it then prints the code destination (0x80000000) and waits for a file to be sent.
The structure of the executable is as follows:
| 4 bytes | variable | 8 bytes |
| length  | data     | checksum|
The checksum is just  a sum on the complete file, byte by byte. not the best integrity check, but good enough.
after the file is recieved, the bootloader compares both checksums (the one received, and the one computed)
and if they match, it branches to the entry point.
The \005 character is because i programmed my terminal to automatically send the file when this character
is encountered.
If you want to send the file via xmodem, there's plenty of information on the web, including example, on
how to implement that.


The DDR init is from https://github.com/auselen/down-to-the-bone/tree/master/baremetal_runtime, cheers to him.

