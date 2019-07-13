#ifndef SETUP_INCLUDE
#define SETUP_INCLUDE

#include "player.h"
#include "room.h"

/* functions */
int setup_screen(void);
Room *setup_map(char **dirs);
Player *setup_player(void);

int get_dirs(void);
int is_file(const char *path);


#endif /* SETUP_INCLUDE */
