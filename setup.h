#ifndef SETUP_INCLUDE
#define SETUP_INCLUDE

#include "player.h"

/* functions */
int setup_screen(void);
int setup_map(char **dirs);
Player *setup_player(void);

int get_dirs(void);
int is_file(const char *path);


/* variables */
int MAX_Y;
int MAX_X;
int i;
int j;
char **dirs; // a line for each directory or file name

#endif /* SETUP_INCLUDE */
