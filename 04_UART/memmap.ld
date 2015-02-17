MEMORY
{
    ram : ORIGIN = 0x402f0400, LENGTH = 0x1B400
}

SECTIONS
{
    .text : { *(.text*) } > ram
    .data : { *(.data*) } > ram
    .bss : { *(.bss*) } > ram
}
