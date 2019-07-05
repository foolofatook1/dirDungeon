#include "player.h"

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

/**
 * Check to see what is in next position.
 */
int check_pos(int new_y, int new_x, Player *p)
{
    switch(mvinch(new_y,new_x))
    {
        case '.':
            move_player(new_y, new_x, p);
            break;
        default:
            move(p->y,p->x);
            break;
    }
}

/**
 * Move the player.
 */
int move_player(int y, int x, Player *p)
{
    mvprintw(p->y,p->x,".");
    p->y = y;
    p->x = x;
    mvprintw(p->y,p->x,"@");
    move(p->y, p->x);

    return 1;
}
