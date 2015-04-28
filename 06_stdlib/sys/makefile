CHAINPATH=@/usr/local/gcc_arm/gcc-arm-none-eabi-4_8-2014q3/bin/
CHAIN=$(CHAINPATH)arm-none-eabi-
CFLAGS=-std=gnu99 -Wall -mfpu=neon -mhard-float -mcpu=cortex-a8 -O0 -ggdb
AFLAGS=-mfpu=neon
OBJ=obj/
PARENTOBJ=../obj/

all: dir $(OBJ)types.o $(OBJ)syscalls.o
	$(CHAIN)ld -r $(OBJ)*.o -o $(PARENTOBJ)sys.o

dir:
	@mkdir -p $(OBJ)

$(OBJ)types.o: types.c
	$(CHAIN)gcc $(CFLAGS) -c types.c -o $(OBJ)types.o

$(OBJ)syscalls.o: syscalls.c
	$(CHAIN)gcc $(CFLAGS) -c syscalls.c -o $(OBJ)syscalls.o

clean:
	rm -rf $(OBJ)*.o
