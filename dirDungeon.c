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

typedef struct Player
{
    int x;
    int y;
    int hp;
} Player;

int setup_screen(void);
int setup_map(void);
int handle_input(int input, Player *p);
Player *setup_player(void);
int move_player(int y, int x, Player *p);

int main (void)
{
    Player *player;
    int input;
    setup_screen();
    setup_map();
    player = setup_player();
    while((input = getch()) != 'q')   // move the character
    {
        handle_input(input, player);
    }
    endwin(); // stop ncurses from running

    return 1;
}

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

    new_player->x = 14;
    new_player->y = 14;
    new_player->hp = 20;

    mvprintw(new_player->y, new_player->x, "@");
    move(new_player->y, new_player->x);

    return new_player;
}

int handle_input(int input, Player *p)
{
    switch(input)
    {
        case 'k':
            /* go up */
            move_player(p->y-1,p->x,p);  
            break;
        case 'j':
            /* go down */
            move_player(p->y+1,p->x,p);  
            break;
        case 'l':
            /* go left */
            move_player(p->y,p->x+1,p);
            break;
        case 'h':
            /* go right */
            move_player(p->y,p->x-1,p);
            break;
        default:
            /* do nothing */
            break;
    }

    return 1;
}

int move_player(int y, int x, Player *p)
{
    mvprintw(p->y,p->x,".");
    p->y = y;
    p->x = x;
    mvprintw(p->y,p->x,"@");
    move(p->y, p->x);

    return 1;
}
