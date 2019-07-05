#ifndef PLAYER_INCLUDE
#define PLAYER_INCLUDE

typedef struct Player
{
    int x;
    int y;
    int hp;
} Player;

int move_player(int y, int x, Player *p);
int check_pos(int new_y, int new_x, Player *p);

#endif /* PLAYER_INCLUDE */
