/**
 * 
 * DirDungeon Game
 * Using ncurses library
 * 
 * Jacob Fisher and Cullen Drissell
 * 
 */

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DELAY 50000

//movement macros
#define STILL 0
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

//creates a player struct to keep track of position and movement
typedef struct{ int x, y, dir; bool alive;} player_object;

int max_x = 0, max_y = 0;
bool walk_flag = true;

void gameOver(void){
	clear();
	endwin();
	exit(1);
}

int main(int argc, char *argv[]) {

    initscr();                              //initializes screen
    if (has_colors() == TRUE) start_color();//enables color
    cbreak();                               //disables character buffering
    noecho();                               //does not print user input to screen
    curs_set(FALSE);                        //does not display cursor
    keypad(stdscr, TRUE);                   //enables all keyboard to be used
    nodelay(stdscr, TRUE);                  //wont wait for input when getch() is used
    getmaxyx(stdscr, max_y, max_x);         //retrieves dimensions of terminal screen

    player_object player;

    player.x = max_x / 2;
    player.y = max_y / 2;
    player.alive = TRUE;


    //loop for game
    for (nodelay(stdscr, TRUE); TRUE; usleep(DELAY)) {

        int num_dirs = 0;
        FILE *file1;
        char dirs1[1035];
        int MAX = sizeof(dirs1);
        file1 = popen("/bin/ls", "r");
        while(fgets(dirs1, MAX-1, file1) != NULL) num_dirs++;
        pclose(file1);

        FILE *file2;
        char dirs2[1035];
        file2 = popen("/bin/ls", "r");
        char dir_names[num_dirs][1035];
        int idx = 0;
        while(fgets(dirs2, MAX-1, file2) != NULL){
            strcpy(dir_names[idx], dirs2);
            idx++;
        }
        pclose(file2);

        int x_diff = max_x/(num_dirs+1);
        int x_pos = x_diff;
        for(int i = 0; i < num_dirs; i++) {
            mvprintw(max_y/4, x_pos, "%s", dir_names[i]);
            x_pos += x_diff;
        }

/*
        // extracts current directory 
        FILE *file1, *file2;
        char dirs1[1035], dirs2[1035];
        int num_dirs = 0;
        int MAX = sizeof(dirs1);

        file1 = popen("/bin/ls", "r");
        while(fgets(dirs1, MAX-1, file1) != NULL) num_dirs++;
        mvprintw(max_y/2, max_x/2, "%s", num_dirs);
        pclose(file1);
        file2 = popen("/bin/ls", "r");
        char dir_names[num_dirs][1035];
        int idx = 0;
        while(fgets(dirs2, MAX-1, file2) != NULL){
            strcpy(dir_names[idx], dirs2);
            idx++;
        }
        pclose(file2);
        

        int y_diff = max_y/(num_dirs-1);
        int y_pos = y_diff;
        for(int i = 0; i < num_dirs; i++){
            //mvprintw(y_pos, max_x-30, "%s", dir_names[i]);
            y_pos += y_diff;
            //printf("%s", dir_names[i]);
        }
*/


        // Get user input to change game state
        int c;
        if ((c = getch()) != ERR) {

            switch (c) {
            case 0x1B: case 127: case KEY_BACKSPACE:
                gameOver();

            case KEY_LEFT: case 'a': case 'A':
                if(player.x > 2) player.x-=2;
                player.dir=LEFT;
                walk_flag=!walk_flag;
                break;

            case KEY_RIGHT: case 'd': case 'D':
                if(player.x < max_x-4) player.x+=2;
                player.dir=RIGHT;
                walk_flag=!walk_flag;
                break;

            case KEY_UP: case 'w': case 'W':
                if(player.y > 2) player.y-=1;
                player.dir=UP;
                walk_flag=!walk_flag;
                break;

            case KEY_DOWN: case 's': case 'S':
                if(player.y < max_y-3) player.y+=1;
                player.dir=DOWN;
                walk_flag=!walk_flag;
                break;
            }
        }



        // Draw player
        mvprintw(player.y-1, player.x, "O");
        mvprintw(player.y, player.x, "|");
        if(walk_flag == true){
            //arms
            mvprintw(player.y, player.x+1, "\\");
            mvprintw(player.y, player.x-1, "/");
            //legs
            mvprintw(player.y+1, player.x+1, "\\");
            mvprintw(player.y+1, player.x-1, "/");
        } else {
            // walking animation
            mvprintw(player.y+1, player.x, "|");
        }

        // draws wall borders
        for(int x = 0; x < max_x; x++){
            mvprintw(0, x, "-");
            mvprintw(max_y-1, x, "-");
        }
        for(int y = 0; y < max_y; y++){
            mvprintw(y, 0, "|");
            mvprintw(y, max_x-1, "|");
        }



        // clears the screen for next frame
        refresh();
        clear();
    }
}
