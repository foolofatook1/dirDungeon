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
    if(dirs)
    {
        
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
                printw("%d) %s is a file\n", i, tmp_file);
                ++file_cnt;
            }
            /* find out the amount of directories */
            else if(!is_file(tmp_file))
            {
                ++dir_cnt;
                printw("%d) %s is a directory\n", i, tmp_file);
            }
            /* free the memory */
            free(tmp_file);
        }
        printw("there are %d files and %d directories\n", 
                file_cnt, dir_cnt);
    /* build the map based on the amount of directories */
    }
    

    //printw("Number of files: %d\n", cnt);
    /*mvprintw(13,13,"--------");
    mvprintw(14,13,"|......|");
    mvprintw(15,13,"|......|");
    mvprintw(16,13,"|......|");
    mvprintw(17,13,"|......|");
    mvprintw(18,13,"--------");*/
    
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

    new_player->y = MAX_Y/2;
    new_player->x = MAX_X/2;
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
