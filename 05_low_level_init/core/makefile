CHAINPATH=@/usr/local/gcc_arm/gcc-arm-none-eabi-4_8-2014q3/bin/
CHAIN=$(CHAINPATH)arm-none-eabi-
CFLAGS=-std=gnu99 -Wall -mfpu=neon -mhard-float -mcpu=cortex-a8 -O0
AFLAGS=-mfpu=neon
OBJ=obj/
PARENTOBJ=../obj/

all: dir $(OBJ)startup_ARMCA8.o1 $(OBJ)core_handlers.o $(OBJ)llma.o $(OBJ)core_init.o
	$(CHAIN)ld -r $(OBJ)startup_ARMCA8.o1 $(OBJ)*.o -o $(PARENTOBJ)core.o



dir:
	@mkdir -p $(OBJ)

$(OBJ)startup_ARMCA8.o1: startup_ARMCA8.s
	$(CHAIN)as $(AFLAGS) -c startup_ARMCA8.s -o $(OBJ)startup_ARMCA8.o1

$(OBJ)core_init.o: core_init.c
	$(CHAIN)gcc $(CFLAGS) -c core_init.c -o $(OBJ)core_init.o

$(OBJ)core_handlers.o: core_handlers.s
	$(CHAIN)as $(AFLAGS) -c core_handlers.s -o $(OBJ)core_handlers.o

$(OBJ)llma.o: llma.s
	$(CHAIN)as $(AFLAGS) -c llma.s -o $(OBJ)llma.o



clean:
	rm -rf $(OBJ)*.o

