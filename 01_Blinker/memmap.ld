MEMORY
{
    ram : ORIGIN = 0x0, LENGTH = 0x1B400
}

SECTIONS
{
    .text : { *(.text*) } > ram
    .bss : { *(.bss*) } > ram
}
