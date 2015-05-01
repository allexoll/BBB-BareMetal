08_test_CXX
===============

in this one, I tried to get cxx linkage to work. proof with vector, string, and ostream.
first you should see the cout << output, then the led_class ctor, and the value "seconds" from the RTC should print. and after 16 seconds, the dtor, and ctor again.
the executable size of this example is huge, i dont know why it is THAT huge.

note that this is the first example to have a very different linker script: first of all, we boot from 0x80000000, as this code is loaded by 07_Bootloader. secondly, there is a lot of subtilities regarding the static/global ctor/dtor for c++, and the lib is waiting for some symbols.