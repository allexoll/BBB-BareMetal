CHAINPATH=/usr/local/gcc_arm/gcc-arm-none-eabi-4_8-2014q3/bin/
CHAIN=$(CHAINPATH)arm-none-eabi
CFLAGS=-std=gnu99 -Wall -mfpu=neon -mhard-float -mcpu=cortex-a8
AFLAGS=-mfpu=neon
OBJ=obj/
BIN=bin/

all: start.o1 main.o GPIO.o pad.o control_module.o clock_module.o LED.o UART.o
	$(CHAIN)-ld -T memmap.ld $(OBJ)start.o1 $(OBJ)*.o -o $(OBJ)main.elf
	$(CHAIN)-objcopy $(OBJ)main.elf $(BIN)spl.boot -O binary

start.o1: start.s
	$(CHAIN)-as $(AFLAGS) start.s -o $(OBJ)start.o1

main.o: main.c
	$(CHAIN)-gcc $(CFLAGS) -c main.c -o $(OBJ)main.o

GPIO.o: GPIO.c
	$(CHAIN)-gcc $(CFLAGS) -c GPIO.c -o $(OBJ)GPIO.o

pad.o: pad.c
	$(CHAIN)-gcc $(CFLAGS) -c pad.c -o $(OBJ)pad.o

control_module.o: control_module.c
	$(CHAIN)-gcc $(CFLAGS) -c control_module.c -o $(OBJ)control_module.o

clock_module.o: clock_module.c
	$(CHAIN)-gcc $(CFLAGS) -c clock_module.c -o $(OBJ)clock_module.o

LED.o: LED.c
	$(CHAIN)-gcc $(CFLAGS) -c LED.c -o $(OBJ)LED.o

UART.o:UART.c
	$(CHAIN)-gcc $(CFLAGS) -c UART.c -o $(OBJ)UART.o

copy:
	cp $(BIN)spl.boot ../boot

clean:
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)*.objstart
	rm -rf $(OBJ)*.elf
	rm -rf $(BIN)*.boot
	rm -rf ../boot/*.boot


dump:
	$(CHAIN)-objdump -D $(OBJ)main.elf