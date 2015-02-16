CHAINPATH=/usr/local/gcc_arm/gcc-arm-none-eabi-4_8-2014q3/bin/
CHAIN=$(CHAINPATH)arm-none-eabi
CFLAGS=-std=c99 -Wall
OBJ=obj/
BIN=bin/

all: start.o main.o GPIO.o pad.o control_module.o clock_module.o
	$(CHAIN)-ld $(OBJ)start.o $(OBJ)main.o $(OBJ)GPIO.o $(OBJ)pad.o $(OBJ)control_module.o $(OBJ)clock_module.o -T memmap.ld -o $(OBJ)main.elf
	$(CHAIN)-objcopy $(OBJ)main.elf $(BIN)spl.boot -O binary
	cp $(BIN)spl.boot ../boot

start.o: start.s
	$(CHAIN)-as start.s -o $(OBJ)start.o

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

copy:
	cp $(BIN)spl.boot ../boot

clean:
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)*.elf
	rm -rf $(BIN)*.boot
	rm -rf ../boot/*.boot


dump:
	$(CHAIN)-objdump -D $(OBJ)main.elf