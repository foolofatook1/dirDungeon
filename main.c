/**
 * 
 * The Dungeons of Dir!
 * Using ncurses library
 * 
 * By: Jacob Fisher and Cullen Drissell
 * main.c
 */

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include "main.h"

/**
 * Global Functions 
 */
int handle_input(int input, Player *p);

int main (void)
{
    Player *player;
    int input;

    setup_screen();         /* initscr, get dimensions, refresh, & noecho */
    get_dirs();             /* get the list of current directories */
    setup_map(dirs);        /* utilizing the gathered list of dirs */
    player = setup_player();

    while((input = getch()) != 'q')   // move the character
        handle_input(input, player);

    endwin(); // stop ncurses from running*/

    /* free all of dirs */
    for (i = 0; i < 1000; ++i)
        free(dirs[i]);
    free(dirs);

    return 0;
}

/**
 * Basic movement input handler at the moment. 
 * Will later handle more keys.
 */
int handle_input(int input, Player *p)
{
    int new_y;
    int new_x;
    switch(input)
    {
        case 'k':
            /* go up */
            new_y = p->y-1;
            new_x = p->x;
            break;
        case 'j':
            /* go down */
            new_y = p->y+1;
            new_x = p->x;
            break;
        case 'l':
            /* go left */
            new_y = p->y; 
            new_x = p->x+1;
            break;
        case 'h':
            /* go right */
            new_y = p->y;
            new_x = p->x-1;
            break;
        default:
            /* do nothing */
            break;
    }

    check_pos(new_y, new_x, p);

    return 0;
}
