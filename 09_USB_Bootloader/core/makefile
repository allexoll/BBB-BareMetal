OBJ=obj/
PARENTOBJ=../obj/

all: dir $(OBJ)startup_ARMCA8.o1 $(OBJ)core_handlers.o $(OBJ)llma.o $(OBJ)core_init.o $(OBJ)__aeabi.o
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

$(OBJ)__aeabi.o: __aeabi.s
	$(CHAIN)as $(AFLAGS) -c __aeabi.s -o $(OBJ)__aeabi.o




clean:
	rm -rf $(OBJ)*.o

