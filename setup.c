/** 
 * setup.c 
 */

#include "setup.h"

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Set up the screen. 
 */
int setup_screen(void)
{
    initscr();
    noecho();
    getmaxyx(stdscr, h, w);
    refresh(); //?

    return 0;
}

/**
 * Set up the map.
 */
int setup_map(char **dirs)
{
    int file_cnt = 0;
    int dir_cnt = 0;
    int room_h = 0;
    int room_w = 0;
    int start_y = 0;
    int start_x = 0;
    char *c = "\0";
    if(dirs)
    {
        /**
         * This should be compartmentalized into 
         * two functions (get_fc & get_dc) in the future maybe.
         */
        for(i = 0; dirs[i] != NULL; ++i)
        {
            /* create a temporary location of the directory */
            char *tmp_file = malloc((strlen(dirs[i])+1)*
                                          sizeof(char));
            strcpy(tmp_file,"./");
            strcat(tmp_file,dirs[i]);
            /* find out the number of files */
            if(is_file(tmp_file))
            {
                ++file_cnt;
                if(DEBUG)
                    printw("%d) %s is a file.\n", i, tmp_file);
            }
            /* find out the amount of directories */
            else 
            {
                ++dir_cnt;
                if(DEBUG)
                    printw("%d) %s is a direcotry.\n", i, tmp_file);
            }
            /* free tmp_files memory */
            free(tmp_file);
        }
    }

     /****************************************************************
      * Directories up will be doors (+) that lead to stairs up (>). *
      * Directories down will be stairs down (<).                    *
      * Files will be indicated by a bold green F in the room.       *
      ****************************************************************/

    /* for now the rooms will be "square" */
    room_h = room_w = (file_cnt > dir_cnt)?((file_cnt*2)+1):((dir_cnt*2)+1); 
    if(DEBUG)
    {
        printw("fc: %d  dc: %d\n", file_cnt, dir_cnt);
        printw("room width: %d\n", room_w);
    }

    /* drawing the map */
    /* 1) find starting x and y pos */
    start_y = (h/2)-(room_h/2);
    start_x = (w/2)-(room_w/2);
    /* 2) draw the first */
    for(i = 0; i <= room_w; ++i)
    {
        c = ((i+1)%(room_w/dir_cnt)==0)?"+":"-"; /*draw doors */
        mvprintw(start_y, start_x+i, c); 
    }
    /* 3) draw the inside */
    for(j = 1; j < room_h; ++j)
    {
        mvprintw(start_y+j, start_x, "|");
        for(i = 1; i < room_w; ++i)
            mvprintw(start_y+j, start_x+i, ".");
        mvprintw(start_y+j, start_x+i, "|");
    }
    /* draw the last row */
    for(i = 0; i <= room_w; ++i)
    {
        mvprintw(start_y+j, start_x+i, "-");
    }
    
    return 0;
}

/**
 * Set up the player,
 * and draw them.
 */
Player *setup_player(void)
{
    Player *new_player;
    new_player = malloc(sizeof(Player));

    new_player->y = h/2;
    new_player->x = w/2;
    new_player->hp = 20; // may not be necessary

    mvprintw(new_player->y, new_player->x, "@");
    move(new_player->y, new_player->x);

    return new_player;
}

/********************************************
 * Helper functions for building map        *
 * by parsing current directory information.* 
 ********************************************/

/**
 * Shows if file is a file or 
 * NOT a directory.
 */
int is_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);

    return S_ISREG(path_stat.st_mode);
}

/**
 * Extract directory names.
 * And put into global dirs!
 */
int get_dirs(void)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if(d)
    {
        dirs = malloc(1000 * sizeof(char *));
        i = 0;
        while((dir = readdir(d)) != NULL)
        {
            dirs[i] = malloc((strlen(dir->d_name)+1)*sizeof(char));
            strcpy(dirs[i], dir->d_name);
            printf("%s", dirs[i]);
            ++i;
        }
        closedir(d);
        
        return 0;
    }

    return -1;
}
