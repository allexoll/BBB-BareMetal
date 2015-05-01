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
