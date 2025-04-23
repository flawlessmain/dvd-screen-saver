#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>

#define ESC "\033"
#define home()                      printf(ESC "[H");
#define clrscr()                    printf(ESC "[2J");
#define gotoxy(x,y)                 printf(ESC "[%d;%dH", y, x);
#define hide_cursor()               printf(ESC "[?25l");
#define resetcolor()                printf(ESC "[0m");
#define set_display_atrib(color)    printf(ESC "[%dm", color);

enum DIRECTION {
    UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT
};

int HEIGHT = 0;
int WIDTH = 0;

void move(enum DIRECTION*, int*, int*);

void check_collision(int*, int*, enum DIRECTION*);

int main(void){
    
    //pulling terminal size
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    HEIGHT = w.ws_row;
    WIDTH = w.ws_col;
    
    //frame delay
    struct timespec delay;
    delay.tv_sec = 0;
    delay.tv_nsec = 50000000;

    //setup
    int x, y;
    x = rand() % (WIDTH - 4);
    y = rand() % (HEIGHT - 2);
    enum DIRECTION direction = rand() % 5;
    hide_cursor();

    //main loop
    while(1){
        system("clear");
        gotoxy(x,y);
        printf("DVD\n");
        move(&direction, &x, &y);
        check_collision(&x, &y, &direction);
        nanosleep(&delay, NULL);
    }

    return 0;
}


void move(enum DIRECTION *direction, int *x, int *y){
    switch (*direction){
        case UP_RIGHT:
            ++(*x); --(*y);
            break;
        case UP_LEFT:
            --(*x); --(*y);
            break;
        case DOWN_LEFT:
            --(*x); ++(*y);
            break;
        case DOWN_RIGHT:
            ++(*x); ++(*y);
            break;
    }
}

void check_collision(int *x, int *y, enum DIRECTION *direction){
    if (*y > HEIGHT - 2){
        if (*direction == DOWN_RIGHT) *direction = UP_RIGHT;
        else *direction = UP_LEFT; 
    }
    if (*y < 2){
        if (*direction == UP_LEFT) *direction = DOWN_LEFT;
        else *direction = DOWN_RIGHT;
    }
    if (*x > WIDTH - 3){
        if (*direction == DOWN_RIGHT) *direction = DOWN_LEFT;
        else *direction = UP_LEFT;
    }
    if (*x < 2){
        if (*direction == DOWN_LEFT) *direction = DOWN_RIGHT;
        else *direction = UP_RIGHT;
    }
}