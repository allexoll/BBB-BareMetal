OBJ=obj/
PARENTOBJ=../obj/

all: dir $(OBJ)main.o
	$(CHAIN)ld -r $(OBJ)*.o -o $(PARENTOBJ)kernel.o

dir:
	@mkdir -p $(OBJ)

$(OBJ)main.o: main.cpp
	$(CHAIN)g++ $(CPPFLAGS) -c main.cpp -o $(OBJ)main.o

clean:
	rm -rf $(OBJ)*.o
