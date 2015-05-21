CHAINPATH=@/usr/local/gcc_arm/gcc-arm-none-eabi-4_8-2014q3/bin/
CHAIN=$(CHAINPATH)arm-none-eabi-
CFLAGS=-std=gnu99 -Wall -mfpu=neon -mhard-float -mcpu=cortex-a8 -O0 -fstack-usage
AFLAGS=-mfpu=neon
OBJ=obj/
BIN=bin/
LIBPATH=/usr/local/gcc_arm/gcc-arm-none-eabi-4_8-2014q3/arm-none-eabi/lib/fpu/

COPYARG=CHAIN="$(CHAIN)" CFLAGS="$(CFLAGS)" AFLAGS="$(AFLAGS)"

all: dir $(OBJ)core.o $(OBJ)proc.o $(OBJ)board.o $(OBJ)sys.o $(OBJ)kernel.o
	@rm -rf $(BIN)*.boot
	@echo "assembling output file..."
	$(CHAIN)ld -T memmap.ld $(OBJ)core.o $(OBJ)proc.o $(OBJ)board.o $(OBJ)sys.o $(OBJ)kernel.o -L $(LIBPATH) -l"c" -l"m" -o $(OBJ)main.elf
	$(CHAIN)objcopy $(OBJ)main.elf $(BIN)spl.boot -O binary
	@echo "done!"

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

copy:
	@echo "copying boot file..."
	@cp $(BIN)spl.boot ../boot
	@echo "done"

clean:
	@echo "cleaning up..."
	@rm -rf $(OBJ)*.o
	@rm -rf $(OBJ)*.elf
	@rm -rf $(BIN)*.boot
	@rm -rf ../boot/*.boot
	@rm -rf core/obj/*
	@rm -rf proc/obj/*
	@rm -rf board/obj/*
	@rm -rf sys/obj/*
	@rm -rf kernel/obj/*
	@echo "done!"

dump:
	$(CHAIN)objdump -D $(OBJ)main.elf