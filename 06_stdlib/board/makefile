CHAINPATH=@/usr/local/gcc_arm/gcc-arm-none-eabi-4_8-2014q3/bin/
CHAIN=$(CHAINPATH)arm-none-eabi-
CFLAGS=-std=gnu99 -Wall -mfpu=neon -mhard-float -mcpu=cortex-a8 -O0 -ggdb
AFLAGS=-mfpu=neon
OBJ=obj/
PARENTOBJ=../obj/

all: dir $(OBJ)board_init.o $(OBJ)LED.o
	$(CHAIN)ld -r $(OBJ)*.o -o $(PARENTOBJ)board.o

dir:
	@mkdir -p $(OBJ)

$(OBJ)LED.o: LED.c
	$(CHAIN)gcc $(CFLAGS) -c LED.c -o $(OBJ)LED.o

$(OBJ)board_init.o: board_init.c
	$(CHAIN)gcc $(CFLAGS) -c board_init.c -o $(OBJ)board_init.o

clean:
	rm -rf $(OBJ)*.o
