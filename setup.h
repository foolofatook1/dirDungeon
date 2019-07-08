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
int h; /* width of screen */
int w; /* height of screen */
int i;
int j;
char **dirs; // a line for each directory or file name
#define DEBUG 0 /* debugging is off */

#endif /* SETUP_INCLUDE */
