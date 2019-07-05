#include "setup.h"

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

/**
 * Set up the screen. 
 */
int setup_screen(void)
{
    initscr();
    noecho();
    refresh(); //?

    return 1;
}

/**
 * Set up the map.
 */
int setup_map(void)
{
    mvprintw(13,13,"--------");
    mvprintw(14,13,"|......|");
    mvprintw(15,13,"|......|");
    mvprintw(16,13,"|......|");
    mvprintw(17,13,"|......|");
    mvprintw(18,13,"--------");
}

/**
 * Set up the player,
 * and draw them.
 */

Player *setup_player(void)
{
    Player *new_player;
    new_player = malloc(sizeof(Player));

    new_player->y = MAX_Y/2;
    new_player->x = MAX_X/2;
    new_player->hp = 20; // may not be necessary

    mvprintw(new_player->y, new_player->x, "@");
    move(new_player->y, new_player->x);

    return new_player;
}
