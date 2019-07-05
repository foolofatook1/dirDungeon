CC = cc 

INCLUDE = player.o setup.o

BIN = dirDungeon

all: $(BIN)

clean:
	rm -f *.o dirDungeon

$(INCLUDE):%.o:%.c
	$(CC) -c -o $@ $< -lncurses

dirDungeon: main.o $(INCLUDE)
	$(CC) -o $@ main.o $(INCLUDE) -lncurses

play:
	./dirDungeon
