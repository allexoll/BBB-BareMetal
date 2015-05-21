# makefile
# Alexis Marquet


#CHAINPATH specifies the path to your toolchain/bin/ directory
CHAINPATH=@/usr/local/gcc_arm/gcc-arm-none-eabi-4_9-2014q4/bin/
#CHAIN specifies the name of your toolchain (arm-elf-linux, arm-none-eabi, etc...)
CHAIN=$(CHAINPATH)arm-none-eabi-

#Warning flags:
WFLAGS= -Wall

#MCPU is the core we are building for
MCPU=-mcpu=cortex-a8

#CFLAGS are the flags passed to gcc
CFLAGS= $(WFLAGS) -std=gnu99 -mfpu=neon -mfloat-abi=softfp $(MCPU) -O2

#CPP FLAGS are the flags passed to g++
CPPFLAGS= $(WFLAGS) -std=c++11 -fno-exceptions -fno-unwind-tables -fno-rtti -mfpu=neon $(MCPU) -O2 -mfloat-abi=softfp

#Asm Flags are the flags passed to as
AFLAGS=-mfpu=neon

#build directories
OBJ=obj/
BIN=bin/


LIBPATH=/usr/local/gcc_arm/gcc-arm-none-eabi-4_9-2014q4/arm-none-eabi/lib/
LIBS=
MMAP= memmap.ld
OBJLIST= $(OBJ)core.o $(OBJ)proc.o $(OBJ)board.o $(OBJ)sys.o $(OBJ)kernel.o

COPYARG=CHAIN="$(CHAIN)" CFLAGS="$(CFLAGS)" AFLAGS="$(AFLAGS)" CPPFLAGS="$(CPPFLAGS)"

all: dir $(OBJ)core.o $(OBJ)proc.o $(OBJ)board.o $(OBJ)sys.o $(OBJ)kernel.o
	@rm -rf $(BIN)*.boot
	@echo "assembling output file..."
	$(CHAIN)g++ -L $(LIBPATH) -T $(MMAP) $(OBJLIST)  $(LIBS) -o $(OBJ)main.elf
	$(CHAIN)objcopy $(OBJ)main.elf $(BIN)spl.boot -O binary
	@echo "done!"
	$(CHAIN)size $(OBJ)main.elf

dir:
	@mkdir -p $(OBJ) $(BIN)

$(OBJ)core.o: force_look
	@echo "building core/"
	@cd core/ ; $(MAKE) $(MFLAGS) $(COPYARG)

$(OBJ)proc.o: force_look
	@echo "building proc/"
	@cd proc/ ; $(MAKE) $(MFLAGS) $(COPYARG)

$(OBJ)board.o: force_look
	@echo "building board/"
	@cd board/ ; $(MAKE) $(MFLAGS) $(COPYARG)

$(OBJ)sys.o: force_look
	@echo "building sys/"
	@cd sys/ ; $(MAKE) $(MFLAGS) $(COPYARG)

$(OBJ)kernel.o: force_look
	@echo "building kernel/"
	@cd kernel/ ; $(MAKE) $(MFLAGS) $(COPYARG)

force_look:
	@true


clean:
	@echo "cleaning up..."
	@rm -rf $(OBJ)*.o
	@rm -rf $(OBJ)*.elf
	@rm -rf $(BIN)*.boot
	@rm -rf core/obj/*
	@rm -rf proc/obj/*
	@rm -rf board/obj/*
	@rm -rf sys/obj/*
	@rm -rf kernel/obj/*
	@echo "done!"


dump:
	$(CHAIN)objdump -D $(OBJ)main.elf