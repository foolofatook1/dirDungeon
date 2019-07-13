CC = cc 

INCLUDE = player.o setup.o 

BIN = dirDungeon

all: $(BIN)

clean:
	rm -f *.o dirDungeon .*.swp

$(INCLUDE):%.o:%.c
	$(CC) -c -o $@ $< -lncurses

dirDungeon: main.o $(INCLUDE)
	$(CC) -o $@ main.o $(INCLUDE) -lncurses

play:
	make clean; make; ./dirDungeon

test:
	make clean; make; valgrind --leak-check=full --show-leak-kinds=all ./dirDungeon
