05_low_level_init
===================

This example has a completely different structure than the previous. I separated what is core specific, what is SoC specific (the peripherals), what is board specific, ans so on... this way i was able to make things modular and tidy (kind of). this example sets the interrupt vector table (still in on chip ram), clears the .bss, inits the core, inits the UART, NVIC, Leds, and finaly in the main() it launches the RTC to have an interupt every second.

each time an interrupt is asserted, PC goes into the ROM vector table (0x20000 something), jump to the vector table at 0x4030CE00, which then send it to IRQ_Handler. there, the context is saved, and the active irq number is passed as first argument to procIrqHandler, which in turn, choses the right interrupt service routine. note: do not forget to clear the pending flag in the INTC register.


I don't think interrupt priority works yet.