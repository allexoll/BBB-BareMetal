OBJ=obj/
PARENTOBJ=../obj/

all: dir  $(OBJ)proc_init.o $(OBJ)UART.o $(OBJ)GPIO.o $(OBJ)control_module.o $(OBJ)clock_module.o $(OBJ)pad.o $(OBJ)proc_Handlers.o $(OBJ)PLL.o $(OBJ)EMIF.o $(OBJ)DDR.o $(OBJ)USB.o
	$(CHAIN)ld -r $(OBJ)*.o -o $(PARENTOBJ)proc.o

dir:
	@mkdir -p $(OBJ)

$(OBJ)proc_init.o: proc_init.c
	$(CHAIN)gcc $(CFLAGS) -c proc_init.c -o $(OBJ)proc_init.o

$(OBJ)proc_Handlers.o: proc_Handlers.c
	$(CHAIN)gcc $(CFLAGS) -c proc_Handlers.c -o $(OBJ)proc_Handlers.o

$(OBJ)GPIO.o: GPIO.c
	$(CHAIN)gcc $(CFLAGS) -c GPIO.c -o $(OBJ)GPIO.o

$(OBJ)pad.o: pad.c
	$(CHAIN)gcc $(CFLAGS) -c pad.c -o $(OBJ)pad.o

$(OBJ)control_module.o: control_module.c
	$(CHAIN)gcc $(CFLAGS) -c control_module.c -o $(OBJ)control_module.o

$(OBJ)clock_module.o: clock_module.c
	$(CHAIN)gcc $(CFLAGS) -c clock_module.c -o $(OBJ)clock_module.o

$(OBJ)UART.o: UART.c
	$(CHAIN)gcc $(CFLAGS) -c UART.c -o $(OBJ)UART.o

$(OBJ)PLL.o: PLL.c
	$(CHAIN)gcc $(CFLAGS) -c PLL.c -o $(OBJ)PLL.o

$(OBJ)EMIF.o: EMIF.c
	$(CHAIN)gcc $(CFLAGS) -c EMIF.c -o $(OBJ)EMIF.o

$(OBJ)DDR.o: DDR.c
	$(CHAIN)gcc $(CFLAGS) -c DDR.c -o $(OBJ)DDR.o

$(OBJ)USB.o: USB.c
	$(CHAIN)gcc $(CFLAGS) -c USB.c -o $(OBJ)USB.o

clean:
	rm -rf $(OBJ)*.o
