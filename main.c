/**
 * 
 * DirDungeon Game
 * Using ncurses library
 * 
 * Jacob Fisher and Cullen Drissell
 * 
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
char *get_dirs(void);

int main (void)
{
    getmaxyx(stdscr, MAX_Y, MAX_X);
    Player *player;
    int input;
    setup_screen();
    setup_map();
    player = setup_player();

    while((input = getch()) != 'q')   // move the character
        handle_input(input, player);

    endwin(); // stop ncurses from running*/

    return 1;
}

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

    return 1;
}

/**
 * Extract directory names.
 */
char *get_dirs(void)
{
    DIR *d;
    struct dirent *dir;
    char dirs[1000];
    d = opendir(".");
    if(d)
    {
        while((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
            strcat(dirs, dir->d_name);
            strcat(dirs, "\n");
        }
        closedir(d);
        printf("dirs: %s\n", dirs);
    }

    return dirs; 
}
