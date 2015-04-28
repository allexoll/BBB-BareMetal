CHAINPATH=@/usr/local/gcc_arm/gcc-arm-none-eabi-4_8-2014q3/bin/
CHAIN=$(CHAINPATH)arm-none-eabi-
CFLAGS=-std=gnu99 -Wall -mfpu=neon -mhard-float -mcpu=cortex-a8 -O0 -ggdb
AFLAGS=-mfpu=neon
OBJ=obj/
PARENTOBJ=../obj/

all: dir $(OBJ)main.o
	$(CHAIN)ld -r $(OBJ)*.o -o $(PARENTOBJ)kernel.o

dir:
	@mkdir -p $(OBJ)

$(OBJ)main.o: main.c
	$(CHAIN)gcc $(CFLAGS) -c main.c -o $(OBJ)main.o

clean:
	rm -rf $(OBJ)*.o
