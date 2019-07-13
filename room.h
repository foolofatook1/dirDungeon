#ifndef ROOM_INCLUDE
#define ROOM_INCLUDE

/* A room is your current directory (i.e.: "./") */
typedef struct Room
{
    int h;       /* height of room */
    int w;       /* widht of room */
    int y;       /* right corner y */
    int x;       /* right corner x */
    int **doors; /* [x][y] of doors */
    char **rooms;/* list of rooms maybe? */
} Room;

#endif /* ROOM_INCLUDE */
